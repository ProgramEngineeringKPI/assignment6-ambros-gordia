#include "Render.hpp"

Tracer tr;
Camera main_camera;

void Render(const char *input_file, string output_file, Camera &main_camera)
{
    cout<<"RENDER (ambros & gordia)"<<endl<<endl;
    cout<<"Image : "<<main_camera.resX<<"x"<<main_camera.resY<<endl;
    long start = clock();
    vector<Vertex> vertices;
    vector<Facet> faces;
    tr.parseOBJ(input_file, vertices, faces);
    ofstream out(output_file, ios::binary);
    
    RTree tree(tr);
    tree.build(vertices);
    
    // file header
    unsigned short width = main_camera.resX;
    unsigned short height = main_camera.resY;
    unsigned short colorBit = 3;
    unsigned int size = width * height * colorBit;
    unsigned int offset = 27;
    unsigned int shit = 12;
    unsigned short filehead[4] = {width, height, 1, (unsigned short)(colorBit * 8)};
    
    out << "BM";
    out.write((char *)&size, sizeof(size));
    out.seekp(4, ios::cur);
    out.write((char *)&offset, sizeof(offset));
    out.write((char *)&shit, sizeof(shit));
    out.write((char *)&filehead, 12);
    out.seekp(offset, ios::beg);
    
    char *buf = new char[size];
    
    float dist = main_camera.size / (2 * tanf((to_rad(main_camera.FOV) / 2)));
    Vector plane_vec = main_camera.direction.normalize() * dist;
    Vector right = main_camera.direction.cross(main_camera.top).normalize();
    
    cout<<"O("<<main_camera.resX<<" * "<<main_camera.resY<<" * "<<faces.size()<<") = "<<(1LL * main_camera.resX * main_camera.resY * faces.size())<<endl;
    
    for (int y = main_camera.resY - 1; y >= 0; y--)
    {
        for (int x = 0; x < main_camera.resX; x++)
        {
            
            float realX = (x - main_camera.resX / 2) / (float)main_camera.resX;
            float realY = (y - main_camera.resY / 2) / (float)main_camera.resY;
            
            Vector dx = right * realX;
            Vector dy = right.cross(main_camera.direction).normalize() * realY;
            
            Vector raydir = dx + dy + main_camera.direction;
            
            Ray ray = Ray(main_camera.position, raydir);
            float deg = 0;
            
            pair<Vector, Vector> v = tree.find(ray);
            
            if (v.first && main_camera.direction.angle(v.second) > to_rad(90)) {
                float shade = sinf(v.second.angle(ray.direction));
                *(buf + (y * height + x) * colorBit + 0) = (char)(0xFF - shade * 0xFF);
                *(buf + (y * height + x) * colorBit + 1) = (char)(0xFF - shade * 0xFF);
                *(buf + (y * height + x) * colorBit + 2) = (char)(0xFF - shade * 0xFF);
            } else {
                *(buf + (y * height + x) * colorBit) = (char)0x4F;
            }
            
            //            int i = 0;
            //            for (; i < faces.size(); i++)
            //            {
            //                pair<Vector, Vector> v = tr.intersectsTriangle(faces[i], ray);
            //
            //                if (v.first && main_camera.direction.angle(v.second) > to_rad(90))
            //                {
            //                    float shade = sinf(v.second.angle(ray.direction));
            //                    *(buf + (y * height + x) * colorBit + 0) = (char)(0xFF - shade * 0xFF);
            //                    *(buf + (y * height + x) * colorBit + 1) = (char)(0xFF - shade * 0xFF);
            //                    *(buf + (y * height + x) * colorBit + 2) = (char)(0xFF - shade * 0xFF);
            //                    break;
            //                }
            //            }
            //            if (i >= faces.size())
            //            {
            //                *(buf + (y * height + x) * colorBit) = (char)0x4F;
            //            }
        }
    }
    out.write(buf, sizeof(char) * size);
    out.close();
    cout<<endl<<"Rendering over in : "<<((clock() - start) / (CLOCKS_PER_SEC / 1000))<<" ms."<<endl<<endl;
}

