/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#include <iostream>
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
#include <min/math/math.h>

void test_eigen() {
  std::cout << "=============Eigen===============" << std::endl;
  Eigen::Vector3f eye(0.0f, 0.0f, 1.0f);
  Eigen::Vector3f center(0.0f, 0.0f, 0.0f);
  Eigen::Vector3f up(0.0f, 1.0f, 0.0f);

  Eigen::Matrix4f proj = min::math::Perspective(min::math::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
  Eigen::Matrix4f view = min::math::LookAt(eye, center, up);

  Eigen::Matrix4f MVP = view*proj;
  std::cout << proj << std::endl;
  std::cout << view << std::endl;
  std::cout << MVP << std::endl;
  std::cout << "============Eigen================" << std::endl;
}

void test_glm() {
  std::cout << "============GLM==================" << std::endl;
  glm::vec3 eye(0.0f, 0.0f, 1.0f);
  glm::vec3 center(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f,1.0f, 0.0f);
  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
  glm::mat4 view = glm::lookAt(eye, center, up );

  glm::mat4 mvp = view*proj;
  std::cout << glm::to_string(proj) << std::endl;
  std::cout << glm::to_string(view) << std::endl;
  std::cout << glm::to_string(mvp) << std::endl;
  std::cout << "============GLM==================" << std::endl;
}
int main() {
  test_glm();
  test_eigen();
}
