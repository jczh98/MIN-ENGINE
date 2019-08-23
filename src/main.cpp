#include <iostream>
#include <vector>
#include <string>

#include "core/common.h"
#include "core/image.h"
#include "core/vector3.h"
#include "core/ray.h"

using namespace chihaya;
Vector3f color(const Ray &r) {
  Vector3f unit = Normalize(r.d);
  Float t = 0.5 * (unit.y + 1.0);
  return Vector3f(1, 1, 1) * (1.0 - t) + Vector3f(0.5, 0.7, 1.0) * t;
}

int main(int argc, char *argv[]) {
  int nx = 200;
  int ny = 100;
  chihaya::Image image(nx, ny, 3);
  Vector3f lower_left_corner(-2.0, -1.0, -1.0);
  Vector3f horizontal(4.0, 0.0, 0.0);
  Vector3f vertical(0.0, 2.0, 0.0);
  Vector3f origin(0.0, 0.0, 0.0);
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      Ray ray(origin, lower_left_corner + horizontal * u + vertical * v);
      Vector3f col = color(ray);
      float b = 0.2;
      int ir = int(255.99 * col.x);
      int ig = int(255.99 * col.y);
      int ib = int(255.99 * col.z);
      image.SetPixel(i, j, ir, ig, ib);
    }
  }
  image.Save("out.png", true);
  return 0;
}