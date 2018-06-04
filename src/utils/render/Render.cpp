#include "Render.h"

Tracer tr;
Camera main_camera;

void Render(const char *input_file, string output_file, Camera &main_camera)
{
  vector<Vertex> vertices;
  vector<Facet> faces;
  tr.parseOBJ(input_file, vertices, faces);
  ofstream out(output_file, ios::binary);

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
  cout << dist << endl;
  Vector right = main_camera.direction.cross(main_camera.top).normalize();

  for (int y = main_camera.resY - 1; y >= 0; y--)
  {
    for (int x = 0; x < main_camera.resX; x++)
    {
      //          xNorm = (x - main_camera.resX / 2) / (float)main_camera.resX,
      //          yNorm = (y - main_camera.resY / 2) / (float)main_camera.resY,
      //          dist_to_plane = (main_camera.position - plane_origin).length(),
      //          FOVrad = main_camera.FOV / 180.f * M_PI,
      //          realH = (float)(dist_to_plane * tanf(FOVrad));
      //      Vector
      //          position_on_plane = Vector(xNorm * realH / 2, yNorm * realH / 2, 0) + plane_origin,
      //          rayDir = position_on_plane - main_camera.position;
      //    Ray ray = Ray(main_camera.position, rayDir);
      // Ray ray = Ray(main_camera.position, Vector(xx, main_camera.position.y + main_camera.FOVmm, zz));

      // float
      //     xNorm = (x - main_camera.resX / 2) / (float)main_camera.resX,
      //     yNorm = (y - main_camera.resY / 2) / (float)main_camera.resY,
      //     dist_to_plane = (main_camera.position - plane_origin).length(),
      //     FOVrad = main_camera.FOV / 180.f * M_PI,
      //     realH = (float)(dist_to_plane * tanf(FOVrad));
      // Vector
      //     position_on_plane = Vector(xNorm * realH / 2, yNorm * realH / 2, 0) + plane_origin,
      //     rayDir = position_on_plane - main_camera.position;

      float realX = (x - main_camera.resX / 2) / (float)main_camera.resX;
      float realY = (y - main_camera.resY / 2) / (float)main_camera.resY;

      Vector dx = right * realX;
      Vector dy = right.cross(main_camera.direction).normalize() * realY;

      Vector raydir = dx + dy + main_camera.direction;

      Ray ray = Ray(main_camera.position, raydir);
      float deg = 0;

      int i = 0;
      for (; i < faces.size(); i++)
      {
        // pair<Vector, Vector> v = tr.intersectsRectangle(Vector(1, 1, 1), Vector(-1, -1, -1), ray);
        pair<Vector, Vector> v = tr.intersectsTriangle(faces[i], ray);
        if (v.first && main_camera.direction.angle(v.second) > to_rad(90))
        {
          // float dist = (v.first - main_camera.position).length();
          float shade = sinf(v.second.angle(ray.direction));
          *(buf + (y * height + x) * colorBit + 0) = (char)(0xFF - shade * 0xFF);
          *(buf + (y * height + x) * colorBit + 1) = (char)(0xFF - shade * 0xFF);
          *(buf + (y * height + x) * colorBit + 2) = (char)(0xFF - shade * 0xFF);
          break;
        }
      }
      if (i >= faces.size())
      {
        *(buf + (y * height + x) * colorBit) = (char)0x4F;
      }
    }
  }
  out.write(buf, sizeof(buf) * 512 * 512);
  out.close();
}
