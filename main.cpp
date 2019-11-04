#include <iostream>

#include <Eigen/Geometry>

using namespace Eigen;

int main() {
  Vector3f vec1(1, 2, 3);
  Vector3f vec2(2, 3, 4);
  std::cout << vec1 + vec2 << std::endl;
  return 0;
}