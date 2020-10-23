#include "direction.h"
#include "vector.h"
#include "line.h"
#include "ray.h"
#include "segment.h"
#include "exact_numeric.h"

#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>

[[cpp11::register]]
direction2_p create_direction_2_empty() {
  std::vector<Direction_2> vec;
  direction2 *result(new direction2(vec));
  return {result};
}

[[cpp11::register]]
direction2_p create_direction_2_vec(vector2_p v) {
  std::vector<Direction_2> vec;
  vec.reserve(v->size());
  for (size_t i = 0; i < v->size(); ++i) {
    if (!(*v)[i]) {
      vec.push_back(Direction_2::NA_value());
      continue;
    }
    vec.emplace_back((*v)[i]);
  }
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p create_direction_2_line(line2_p l) {
  std::vector<Direction_2> vec;
  vec.reserve(l->size());
  for (size_t i = 0; i < l->size(); ++i) {
    if (!(*l)[i]) {
      vec.push_back(Direction_2::NA_value());
      continue;
    }
    vec.emplace_back((*l)[i]);
  }
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p create_direction_2_ray(ray2_p r) {
  std::vector<Direction_2> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Direction_2::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p create_direction_2_segment(segment2_p s) {
  std::vector<Direction_2> vec;
  vec.reserve(s->size());
  for (size_t i = 0; i < s->size(); ++i) {
    if (!(*s)[i]) {
      vec.push_back(Direction_2::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i]);
  }
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p create_direction_2_xy(exact_numeric_p x, exact_numeric_p y) {
  std::vector<Direction_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i]) {
      vec.push_back(Direction_2::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i]);
  }
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p direction_2_negate(direction2_p x) {
  std::vector<Direction_2> vec = -(*x);
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals direction_2_less(direction2_p x, direction2_p y) {
  return (*x) < y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals direction_2_greater(direction2_p x, direction2_p y) {
  return (*x) > y->get_storage();
}

[[cpp11::register]]
direction2_p direction_2_sort(direction2_p x, bool decreasing, cpp11::logicals na_last) {
  std::vector<Direction_2> vec = x->sort(decreasing, na_last);
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::integers direction_2_rank(direction2_p x) {
  return x->rank();
}

[[cpp11::register]]
direction2_p direction_2_min(direction2_p x, bool na_rm) {
  std::vector<Direction_2> vec = x->min(na_rm);
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p direction_2_max(direction2_p x, bool na_rm) {
  std::vector<Direction_2> vec = x->max(na_rm);
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p direction_2_cummin(direction2_p x) {
  std::vector<Direction_2> vec = x->cummin();
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
direction2_p direction_2_cummax(direction2_p x) {
  std::vector<Direction_2> vec = x->cummax();
  direction2 *result(new direction2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals direction_2_between(direction2_p x, direction2_p d1, direction2_p d2) {
  return x->between(*d1, *d2);
}

[[cpp11::register]]
direction3_p create_direction_3_empty() {
  std::vector<Direction_3> vec;
  direction3 *result(new direction3(vec));
  return {result};
}

[[cpp11::register]]
direction3_p create_direction_3_vec(vector3_p v) {
  std::vector<Direction_3> vec;
  vec.reserve(v->size());
  for (size_t i = 0; i < v->size(); ++i) {
    if (!(*v)[i]) {
      vec.push_back(Direction_3::NA_value());
      continue;
    }
    vec.emplace_back((*v)[i]);
  }
  direction3 *result(new direction3(vec));

  return {result};
}

[[cpp11::register]]
direction3_p create_direction_3_line(line3_p l) {
  std::vector<Direction_3> vec;
  vec.reserve(l->size());
  for (size_t i = 0; i < l->size(); ++i) {
    if (!(*l)[i]) {
      vec.push_back(Direction_3::NA_value());
      continue;
    }
    vec.emplace_back((*l)[i]);
  }
  direction3 *result(new direction3(vec));

  return {result};
}

[[cpp11::register]]
direction3_p create_direction_3_ray(ray3_p r) {
  std::vector<Direction_3> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Direction_3::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  direction3 *result(new direction3(vec));

  return {result};
}

[[cpp11::register]]
direction3_p create_direction_3_segment(segment3_p s) {
  std::vector<Direction_3> vec;
  vec.reserve(s->size());
  for (size_t i = 0; i < s->size(); ++i) {
    if (!(*s)[i]) {
      vec.push_back(Direction_3::NA_value());
      continue;
    }
    vec.emplace_back((*s)[i]);
  }
  direction3 *result(new direction3(vec));

  return {result};
}

[[cpp11::register]]
direction3_p create_direction_3_xyz(exact_numeric_p x, exact_numeric_p y, exact_numeric_p z) {
  std::vector<Direction_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i]) {
      vec.push_back(Direction_3::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i], (*z)[i]);
  }
  direction3 *result(new direction3(vec));

  return {result};
}

[[cpp11::register]]
direction3_p direction_3_negate(direction3_p x) {
  std::vector<Direction_3> vec = -(*x);
  direction3 *result(new direction3(vec));

  return {result};
}
