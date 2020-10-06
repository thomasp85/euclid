#include "circle.h"
#include "point.h"
#include "plane.h"
#include "vector.h"
#include "sphere.h"
#include "exact_numeric.h"
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
circle2_p create_circle_2_empty() {
  std::vector<Circle_2> vec;
  circle2 *result(new circle2(vec));
  return {result};
}

[[cpp11::register]]
circle2_p create_circle_2_center_radius(point2_p center, exact_numeric_p r2) {
  std::vector<Circle_2> vec;
  vec.reserve(center->size());
  for (size_t i = 0; i < center->size(); ++i) {
    if (!(*center)[i] || !(*r2)[i] || (*r2)[i] < 0.0) {
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    vec.emplace_back((*center)[i], (*r2)[i]);
  }
  circle2 *result(new circle2(vec));

  return {result};
}
[[cpp11::register]]
circle2_p create_circle_2_3_point(point2_p p, point2_p q, point2_p r) {
  std::vector<Circle_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i]) {
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    if (CGAL::collinear((*p)[i], (*q)[i], (*r)[i])) {
      cpp11::warning("circle cannot be constructed from 3 colliniar points");
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  circle2 *result(new circle2(vec));

  return {result};
}
[[cpp11::register]]
circle2_p create_circle_2_2_point(point2_p p, point2_p q) {
  std::vector<Circle_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  circle2 *result(new circle2(vec));

  return {result};
}

[[cpp11::register]]
circle3_p create_circle_3_empty() {
  std::vector<Circle_3> vec;
  circle3 *result(new circle3(vec));
  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<circle3> create_circle_3_center_radius_plane(point3_p center, exact_numeric_p r2, plane_p p) {
  std::vector<Circle_3> vec;
  vec.reserve(center->size());
  for (size_t i = 0; i < center->size(); ++i) {
    if (!(*center)[i] || !(*r2)[i] || (*r2)[i] < 0.0 || !(*p)[i]) {
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    if (!(*p)[i].has_on((*center)[i])) {
      cpp11::warning("Center must lie on the plane");
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    vec.emplace_back((*center)[i], (*r2)[i], (*p)[i]);
  }
  circle3 *result(new circle3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<circle3> create_circle_3_center_radius_vec(point3_p center, exact_numeric_p r2, vector3_p v) {
  std::vector<Circle_3> vec;
  vec.reserve(center->size());
  for (size_t i = 0; i < center->size(); ++i) {
    if (!(*center)[i] || !(*r2)[i] || (*r2)[i] < 0.0 || !(*v)[i]) {
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    vec.emplace_back((*center)[i], (*r2)[i], (*v)[i]);
  }
  circle3 *result(new circle3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<circle3> create_circle_3_3_point(point3_p p, point3_p q, point3_p r) {
  std::vector<Circle_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i]) {
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    if (CGAL::collinear((*p)[i], (*q)[i], (*r)[i])) {
      cpp11::warning("circle cannot be constructed from 3 colliniar points");
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  circle3 *result(new circle3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<circle3> create_circle_3_sphere_sphere(sphere_p s1, sphere_p s2) {
  std::vector<Circle_3> vec;
  vec.reserve(s1->size());
  for (size_t i = 0; i < s1->size(); ++i) {
    if (!(*s1)[i] || !(*s2)[i]) {
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    if (!CGAL::do_intersect((*s1)[i], (*s2)[i])) {
      cpp11::warning("Spheres must intersect to form a circle");
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    vec.emplace_back((*s1)[i], (*s2)[i]);
  }
  circle3 *result(new circle3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<circle3> create_circle_3_sphere_plane(sphere_p s, plane_p p) {
  std::vector<Circle_3> vec;
  vec.reserve(s->size());
  for (size_t i = 0; i < s->size(); ++i) {
    if (!(*s)[i] || !(*p)[i]) {
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    if (!CGAL::do_intersect((*s)[i], (*p)[i])) {
      cpp11::warning("Sphere must intersect with plane to form a circle");
      vec.push_back(Circle_3::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i], (*p)[i]);
  }
  circle3 *result(new circle3(vec));

  return {result};
}
