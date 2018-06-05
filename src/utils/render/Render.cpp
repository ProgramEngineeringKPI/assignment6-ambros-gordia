#include "Render.h"

Tracer tr;
Camera main_camera;
Light light(Vector(10, 10, 10), 1);

void Render(const char *input_file, string output_file, Camera &main_camera)
{
  unsigned long cur_buffer = 0;
  unsigned long file_offset = 0;
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

  const unsigned long max_buffer = 65536 * colorBit;
  char *buf = new char[max_buffer];

  float dist = main_camera.size / (2 * tanf((to_rad(main_camera.FOV) / 2)));
  Vector plane_vec = main_camera.direction.normalize() * dist;
  Vector right = main_camera.direction.cross(main_camera.top).normalize();

  for (int y = 0; y < main_camera.resY; y++)
  {
    cout << "processed row..." << endl;
    for (int x = 0; x < main_camera.resX; x++)
    {
      float realX = (x - main_camera.resX / 2) / (float)main_camera.resX;
      float realY = (y - main_camera.resY / 2) / (float)main_camera.resY;

      Vector dx = right * realX;
      Vector dy = right.cross(main_camera.direction).normalize() * realY;

      Vector raydir = dx + dy + plane_vec;

      Ray ray = Ray(main_camera.position, raydir);
      float deg = 0;

      unsigned int index = (y * height + x) * colorBit - file_offset;
      // *(buf + index) = 0;
      // *(buf + index + 1) = 0;
      // *(buf + index + 2) = 0;
      unsigned int i = 0;
      for (; i < faces.size(); i++)
      {
        // pair<Vector, Vector> v = tr.intersectsTriangle(faces[i], Vector(-1, -1, -1), ray);
        pair<Vector, Vector> v = tr.intersectsTriangle(faces[i], ray);
        if (v.first && main_camera.direction.angle(v.second) > to_rad(90))
        {
          // float dist = (v.first - main_camera.position).length();
          float shade = sinf(v.second.angle(ray.direction));
          *(buf + index) = (char)(0xFF - shade * 0xFF);
          break;
        }
      }
      if (i >= faces.size())
      {
        *(buf + index + 1) = (char)0x4F;
      }
      cur_buffer = (y * height + x) * colorBit;
      if (cur_buffer - file_offset >= max_buffer)
      {
        out.write(buf, max_buffer);
        file_offset = cur_buffer;
        cur_buffer = 0;
        buf = new char[max_buffer];
      }
    }
  }
  if (cur_buffer - file_offset != 0)
  {
    out.write(buf, cur_buffer - file_offset);
  }
  // out.write(buf, sizeof(buf) * size);
  out.close();
}
