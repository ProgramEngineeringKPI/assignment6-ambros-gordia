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
  unsigned short width = 512;
  unsigned short height = 512;
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

  Vector plane_origin = Vector(main_camera.direction.normalize() + main_camera.position);

  char *buf = new char[size];

  for (int y = 0; y < main_camera.resY; y++)
  {
    for (int x = 0; x < main_camera.resX; x++)
    {
      float
          xNorm = (x - main_camera.resX / 2) / (float)main_camera.resX,
          yNorm = (y - main_camera.resY / 2) / (float)main_camera.resY,
          dist_to_plane = (main_camera.position - plane_origin).length(),
          FOVrad = main_camera.FOV / 180.f * M_PI,
          realH = (float)(dist_to_plane * tanf(FOVrad));
      Vector
          position_on_plane = Vector(xNorm * realH / 2, yNorm * realH / 2, 0) + plane_origin,
          rayDir = position_on_plane - main_camera.position;

      Ray ray = Ray(main_camera.position, rayDir);
      int i = 0;
      for (; i < faces.size(); i++)
      {
        pair<Vector, Vector> v = tr.intersectsTriangle(faces[i], ray);
        if (v.first)
        {
          float dist = (v.first - main_camera.position).length();
          *(buf + (y * height + x) * colorBit + 1) = (char)(dist * 0xFF);
          break;
        }
      }
      if (i >= faces.size())
      {
        *(buf + (y * height + x) * colorBit) = (char)0x0F;
      }
    }
  }
  out.write(buf, sizeof(buf) * 512 * 512);
  out.close();
}
