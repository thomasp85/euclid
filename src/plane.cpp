#include "plane.h"
#include "point.h"
#include "vector.h"
#include "direction.h"
#include "line.h"
#include "ray.h"
#include "segment.h"
#include "circle.h"
#include "triangle.h"
#include "exact_numeric.h"

[[cpp11::register]]
plane_p create_plane_empty() {
  std::vector<Plane> vec;
  plane *result(new plane(vec));
  return {result};
}

[[cpp11::register]]
plane_p create_plane_abcd(exact_numeric_p a, exact_numeric_p b, exact_numeric_p c, exact_numeric_p d) {
  std::vector<Plane> vec;
  vec.reserve(a->size());
  for (size_t i = 0; i < a->size(); ++i) {
    if (!(*a)[i] || !(*b)[i] || !(*c)[i] || !(*d)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*a)[i], (*b)[i], (*c)[i], (*d)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_pqr(point3_p p, point3_p q, point3_p r) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_pv(point3_p p, vector3_p v) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*v)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_pd(point3_p p, direction3_p d) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*d)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*d)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_pl(point3_p p, line3_p l) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*l)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*l)[i], (*p)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_pr(point3_p p, ray3_p r) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*r)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i], (*p)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_ps(point3_p p, segment3_p s) {
  std::vector<Plane> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*s)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i], (*p)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_circle(circle3_p circle) {
  std::vector<Plane> vec;
  vec.reserve(circle->size());
  for (size_t i = 0; i < circle->size(); ++i) {
    if (!(*circle)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.emplace_back((*circle)[i]);
  }
  plane *result(new plane(vec));

  return {result};
}

[[cpp11::register]]
plane_p create_plane_triangle(triangle3_p triangle) {
  std::vector<Plane> vec;
  vec.reserve(triangle->size());
  for (size_t i = 0; i < triangle->size(); ++i) {
    if (!(*triangle)[i]) {
      vec.push_back(Plane::NA_value());
      continue;
    }
    vec.push_back((*triangle)[i].supporting_plane());
  }
  plane *result(new plane(vec));

  return {result};
}
