#include "ray.h"
#include "point.h"
#include "direction.h"
#include "vector.h"
#include "line.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
ray2_p create_ray_2_empty() {
  std::vector<Ray_2> vec;
  ray2 *result(new ray2(vec));
  return {result};
}

[[cpp11::register]]
ray2_p create_ray_2_p_q(point2_p p, point2_p q) {
  std::vector<Ray_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Ray_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  ray2 *result(new ray2(vec));

  return {result};
}

[[cpp11::register]]
ray2_p create_ray_2_p_d(point2_p p, direction2_p d) {
  std::vector<Ray_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*d)[i]) {
      vec.push_back(Ray_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*d)[i]);
  }
  ray2 *result(new ray2(vec));

  return {result};
}

[[cpp11::register]]
ray2_p create_ray_2_p_v(point2_p p, vector2_p v) {
  std::vector<Ray_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Ray_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*v)[i]);
  }
  ray2 *result(new ray2(vec));

  return {result};
}

[[cpp11::register]]
ray2_p create_ray_2_p_l(point2_p p, line2_p l) {
  std::vector<Ray_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*l)[i]) {
      vec.push_back(Ray_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*l)[i]);
  }
  ray2 *result(new ray2(vec));

  return {result};
}

[[cpp11::register]]
ray2_p ray_2_negate(ray2_p x) {
  std::vector<Ray_2> vec = -(*x);
  ray2 *result(new ray2(vec));

  return {result};
}

[[cpp11::register]]
ray3_p create_ray_3_empty() {
  std::vector<Ray_3> vec;
  ray3 *result(new ray3(vec));
  return {result};
}

[[cpp11::register]]
ray3_p create_ray_3_p_q(point3_p p, point3_p q) {
  std::vector<Ray_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Ray_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  ray3 *result(new ray3(vec));

  return {result};
}

[[cpp11::register]]
ray3_p create_ray_3_p_d(point3_p p, direction3_p d) {
  std::vector<Ray_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*d)[i]) {
      vec.push_back(Ray_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*d)[i]);
  }
  ray3 *result(new ray3(vec));

  return {result};
}

[[cpp11::register]]
ray3_p create_ray_3_p_v(point3_p p, vector3_p v) {
  std::vector<Ray_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Ray_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*v)[i]);
  }
  ray3 *result(new ray3(vec));

  return {result};
}

[[cpp11::register]]
ray3_p create_ray_3_p_l(point3_p p, line3_p l) {
  std::vector<Ray_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*l)[i]) {
      vec.push_back(Ray_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*l)[i]);
  }
  ray3 *result(new ray3(vec));

  return {result};
}

[[cpp11::register]]
ray3_p ray_3_negate(ray3_p x) {
  std::vector<Ray_3> vec = -(*x);
  ray3 *result(new ray3(vec));

  return {result};
}
