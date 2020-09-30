#include "point_w.h"
#include "point.h"
#include "exact_numeric.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
point_w2_p create_point_w_2_empty() {
  std::vector<Weighted_point_2> vec;
  point_w2 *result(new point_w2(vec));
  return {result};
}

[[cpp11::register]]
point_w2_p create_point_w_2_x_y_w(exact_numeric_p x, exact_numeric_p y, exact_numeric_p w) {
  std::vector<Weighted_point_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i] || !(*w)[i]) {
      vec.push_back(Weighted_point_2::NA_value());
      continue;
    }
    vec.emplace_back(Point_2((*x)[i], (*y)[i]), (*w)[i]);
  }
  point_w2 *result(new point_w2(vec));

  return {result};
}

[[cpp11::register]]
point_w2_p create_point_w_2_p_w(point2_p p, exact_numeric_p w) {
  std::vector<Weighted_point_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*w)[i]) {
      vec.push_back(Weighted_point_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*w)[i]);
  }
  point_w2 *result(new point_w2(vec));

  return {result};
}

[[cpp11::register]]
point_w3_p create_point_w_3_empty() {
  std::vector<Weighted_point_3> vec;
  point_w3 *result(new point_w3(vec));
  return {result};
}

[[cpp11::register]]
point_w3_p create_point_w_3_x_y_z_w(exact_numeric_p x, exact_numeric_p y, exact_numeric_p z, exact_numeric_p w) {
  std::vector<Weighted_point_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i] || !(*z)[i] || !(*w)[i]) {
      vec.push_back(Weighted_point_3::NA_value());
      continue;
    }
    vec.emplace_back(Point_3((*x)[i], (*y)[i], (*z)[i]), (*w)[i]);
  }
  point_w3 *result(new point_w3(vec));

  return {result};
}

[[cpp11::register]]
point_w3_p create_point_w_3_p_w(point3_p p, exact_numeric_p w) {
  std::vector<Weighted_point_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*w)[i]) {
      vec.push_back(Weighted_point_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*w)[i]);
  }
  point_w3 *result(new point_w3(vec));

  return {result};
}
