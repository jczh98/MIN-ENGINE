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

Hitable *RandomScene() {
  int n = 500;
  Hitable **list = new Hitable *[n + 1];
  list[0] = new Sphere(Vector3f(0, -1000, 0), 1000, new Lambertian(Vector3f(0.5, 0.5, 0.5)));
  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose_mat = drand48();
      Vector3f center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
      if ((center - Vector3f(4, 0.2, 0)).Length() > 0.9) {
        if (choose_mat < 0.8) {  // diffuse
          list[i++] = new Sphere(
              center, 0.2,
              new Lambertian(Vector3f(drand48() * drand48(),
                                      drand48() * drand48(),
                                      drand48() * drand48()))
          );
        } else if (choose_mat < 0.95) { // metal
          list[i++] = new Sphere(
              center, 0.2,
              new Metal(Vector3f(0.5 * (1 + drand48()),
                                 0.5 * (1 + drand48()),
                                 0.5 * (1 + drand48())),
                        0.5 * drand48())
          );
        } else {  // glass
          list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
        }
      }
    }
  }

  list[i++] = new Sphere(Vector3f(0, 1, 0), 1.0, new Dielectric(1.5));
  list[i++] = new Sphere(Vector3f(-4, 1, 0), 1.0, new Lambertian(Vector3f(0.4, 0.2, 0.1)));
  list[i++] = new Sphere(Vector3f(4, 1, 0), 1.0, new Metal(Vector3f(0.7, 0.6, 0.5), 0.0));

  return new HitableList(list, i);
}

int main(int argc, char *argv[]) {
  int nx = 1200;
  int ny = 800;
  int ns = 10;
  chihaya::Image image(nx, ny, 3);
  Hitable *world = RandomScene();
  Vector3f lookfrom(13, 2, 3);
  Vector3f lookat(0, 0, 0);
  Float dist_to_focus = 10.0;
  Float aperture = 0.1;
  Camera camera(lookfrom, lookat, Vector3f(0, 1, 0), 20, Float(nx) / Float(ny), aperture, dist_to_focus);
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
      std::cout << i << " " << j << std::endl;
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