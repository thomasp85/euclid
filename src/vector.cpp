#include "vector.h"
#include "point.h"
#include "exact_numeric.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
cpp11::external_pointer<vector2> create_vector_2_point(cpp11::external_pointer<point2> p) {
  std::vector<Vector_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    vec.emplace_back((*p)[i].x(), (*p)[i].y());
  }
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<vector2> create_vector_2_x_y(cpp11::external_pointer<exact_numeric> x, cpp11::external_pointer<exact_numeric> y) {
  std::vector<Vector_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    vec.emplace_back((*x)[i], (*y)[i]);
  }
  vector2 *result(new vector2(vec));

  return {result};
}

//[[cpp11::register]]
//cpp11::external_pointer<vector2> vector_2_add_vector(cpp11::external_pointer<vector2> x) {
//
//  std::vector<Vector_2> vec;
//  vec.reserve(x->size());
//  for (size_t i = 0; i < x->size(); ++i) {
//    vec.emplace_back((*x)[i], (*y)[i]);
//  }
//  vector2 *result(new vector2(vec));
//
//  return {result};
//}

[[cpp11::register]]
cpp11::external_pointer<vector3> create_vector_3_point(cpp11::external_pointer<point3> p) {
  std::vector<Vector_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    vec.emplace_back((*p)[i].x(), (*p)[i].y(), (*p)[i].z());
  }
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<vector3> create_vector_3_x_y_z(cpp11::external_pointer<exact_numeric> x, cpp11::external_pointer<exact_numeric> y, cpp11::external_pointer<exact_numeric> z) {
  std::vector<Vector_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    vec.emplace_back((*x)[i], (*y)[i], (*z)[i]);
  }
  vector3 *result(new vector3(vec));

  return {result};
}
