#include <iostream>
#include <vector>
#include <string>

#include "core/common.h"
#include "core/image.h"
#include "core/vector3.h"
#include "core/ray.h"
#include "core/sphere.h"
#include "core/hitable_list.h"
#include "core/camera.h"

using namespace chihaya;
Vector3f color(const Ray &r, Hitable *world) {
  HitRecord rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return Vector3f(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1) * 0.5;
  } else {
    Vector3f unit = Normalize(r.d);
    Float t = 0.5 * (unit.y + 1.0);
    return Vector3f(1, 1, 1) * (1.0 - t) + Vector3f(0.5, 0.7, 1.0) * t;
  }

}

int main(int argc, char *argv[]) {
  int nx = 200;
  int ny = 100;
  int ns = 100;
  chihaya::Image image(nx, ny, 3);
  Vector3f lower_left_corner(-2.0, -1.0, -1.0);
  Vector3f horizontal(4.0, 0.0, 0.0);
  Vector3f vertical(0.0, 2.0, 0.0);
  Vector3f origin(0.0, 0.0, 0.0);
  Hitable *list[2];
  list[0] = new Sphere(Vector3f(0, 0, -1), 0.5);
  list[1] = new Sphere(Vector3f(0, -100.5, -1), 100);
  Hitable *world = new HitableList(list, 2);
  Camera camera;
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      Vector3f col(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        Float u = Float(i + drand48()) / Float(nx);
        Float v = Float(j + drand48()) / Float(ny);
        Ray r = camera.GetRay(u, v);
        Vector3f p = r(2);
        col += color(r, world);
      }
      col /= ns;
      int ir = int(255.99 * col.x);
      int ig = int(255.99 * col.y);
      int ib = int(255.99 * col.z);
      image.SetPixel(i, j, ir, ig, ib);
    }
  }
  image.Save("out.png", true);
  return 0;
}