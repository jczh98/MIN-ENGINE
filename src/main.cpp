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
#include "core/material.h"

using namespace chihaya;

Vector3f color(const Ray &r, Hitable *world, int depth) {
  HitRecord rec;
  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    Ray scattered;
    Vector3f attenuation;
    if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    } else {
      return Vector3f(0, 0, 0);
    }
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
  Hitable *list[5];
  list[0] = new Sphere(Vector3f(0, 0, -1), 0.5, new Lambertian(Vector3f(0.1, 0.2, 0.5)));
  list[1] = new Sphere(Vector3f(0, -100.5, -1), 100, new Lambertian(Vector3f(0.8, 0.8, 0.0)));
  list[2] = new Sphere(Vector3f(1, 0, -1), 0.5, new Metal(Vector3f(0.8, 0.6, 0.2), 0.3));
  list[3] = new Sphere(Vector3f(-1, 0, -1), 0.5, new Dielectric(1.5));
  list[4] = new Sphere(Vector3f(-1, 0, -1), -0.45, new Dielectric(1.5));
  Hitable *world = new HitableList(list, 5);
  Vector3f lookfrom(3, 3, 2);
  Vector3f lookat(0, 0, -1);
  Float dist_to_focus = (lookfrom - lookat).Length();
  Float aperture = 2.0;
  Camera camera(lookfrom, lookat, Vector3f(0, 1, 0), 20, Float(nx)/Float(ny), aperture, dist_to_focus);
  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      Vector3f col(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        Float u = Float(i + drand48()) / Float(nx);
        Float v = Float(j + drand48()) / Float(ny);
        Ray r = camera.GetRay(u, v);
        Vector3f p = r(2);
        col += color(r, world, 0);
      }
      col /= ns;
      col = Vector3f(sqrt(col.x), sqrt(col.y), sqrt(col.z));
      int ir = int(255.99 * col.x);
      int ig = int(255.99 * col.y);
      int ib = int(255.99 * col.z);
      image.SetPixel(i, j, ir, ig, ib);
    }
  }
  image.Save("out.png", true);
  return 0;
}