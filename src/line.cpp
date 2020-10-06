#include "line.h"
#include "point.h"
#include "direction.h"
#include "vector.h"
#include "segment.h"
#include "ray.h"
#include "exact_numeric.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
line2_p create_line_2_empty() {
  std::vector<Line_2> vec;
  line2 *result(new line2(vec));
  return {result};
}


[[cpp11::register]]
line2_p create_line_2_a_b_c(exact_numeric_p a, exact_numeric_p b, exact_numeric_p c) {
  std::vector<Line_2> vec;
  vec.reserve(a->size());
  for (size_t i = 0; i < a->size(); ++i) {
    if (!(*a)[i] || !(*b)[i] || !(*c)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*a)[i], (*b)[i], (*c)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line2_p create_line_2_p_q(point2_p p, point2_p q) {
  std::vector<Line_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line2_p create_line_2_p_d(point2_p p, direction2_p d) {
  std::vector<Line_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*d)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*d)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line2_p create_line_2_p_v(point2_p p, vector2_p v) {
  std::vector<Line_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*v)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line2_p create_line_2_seg(segment2_p s) {
  std::vector<Line_2> vec;
  vec.reserve(s->size());
  for (size_t i = 0; i < s->size(); ++i) {
    if (!(*s)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line2_p create_line_2_ray(ray2_p r) {
  std::vector<Line_2> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Line_2::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  line2 *result(new line2(vec));

  return {result};
}

[[cpp11::register]]
line3_p create_line_3_empty() {
  std::vector<Line_3> vec;
  line3 *result(new line3(vec));
  return {result};
}

[[cpp11::register]]
line3_p create_line_3_p_q(point3_p p, point3_p q) {
  std::vector<Line_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Line_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  line3 *result(new line3(vec));

  return {result};
}

[[cpp11::register]]
line3_p create_line_3_p_d(point3_p p, direction3_p d) {
  std::vector<Line_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*d)[i]) {
      vec.push_back(Line_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*d)[i]);
  }
  line3 *result(new line3(vec));

  return {result};
}

[[cpp11::register]]
line3_p create_line_3_p_v(point3_p p, vector3_p v) {
  std::vector<Line_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Line_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*v)[i]);
  }
  line3 *result(new line3(vec));

  return {result};
}

[[cpp11::register]]
line3_p create_line_3_seg(segment3_p s) {
  std::vector<Line_3> vec;
  vec.reserve(s->size());
  for (size_t i = 0; i < s->size(); ++i) {
    if (!(*s)[i]) {
      vec.push_back(Line_3::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i]);
  }
  line3 *result(new line3(vec));

  return {result};
}

[[cpp11::register]]
line3_p create_line_3_ray(ray3_p r) {
  std::vector<Line_3> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Line_3::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  line3 *result(new line3(vec));

  return {result};
}
