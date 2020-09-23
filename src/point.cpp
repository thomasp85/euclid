#include "point.h"
#include "exact_numeric.h"
#include "vector.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
cpp11::external_pointer<point2> create_point_2_x_y(cpp11::external_pointer<exact_numeric> x,
                                                   cpp11::external_pointer<exact_numeric> y) {
  std::vector<Point_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    vec.emplace_back((*x)[i], (*y)[i]);
  }
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point2> create_point_2_vec(cpp11::external_pointer<vector2> p) {
  std::vector<Point_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    vec.emplace_back((*p)[i].x(), (*p)[i].y());
  }
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point2> point_2_add_vector(cpp11::external_pointer<point2> x, cpp11::external_pointer<vector2> y) {
  std::vector<Point_2> vec = (*x) + y->get_storage();
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point2> point_2_sub_vector(cpp11::external_pointer<point2> x, cpp11::external_pointer<vector2> y) {
  std::vector<Point_2> vec = (*x) - y->get_storage();
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<vector2> point_2_sub_point(cpp11::external_pointer<point2> x, cpp11::external_pointer<point2> y) {
  std::vector<Vector_2> vec = (*x) - y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals point_2_less(cpp11::external_pointer<point2> x, cpp11::external_pointer<point2> y) {
  return (*x) < y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_2_less_equal(cpp11::external_pointer<point2> x, cpp11::external_pointer<point2> y) {
  return (*x) <= y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_2_greater(cpp11::external_pointer<point2> x, cpp11::external_pointer<point2> y) {
  return (*x) > y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_2_greater_equal(cpp11::external_pointer<point2> x, cpp11::external_pointer<point2> y) {
  return (*x) >= y->get_storage();
}

[[cpp11::register]]
cpp11::external_pointer<exact_numeric> point_2_coord(cpp11::external_pointer<point2> x, int i) {
  std::vector<Exact_number> vec = x->coord(i);
  exact_numeric *result(new exact_numeric(vec));
  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point2> point_2_sort(cpp11::external_pointer<point2> x, bool decreasing) {
  std::vector<Point_2> vec = x->sort(decreasing);
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
cpp11::writable::integers point_2_rank(cpp11::external_pointer<point2> x) {
  return x->rank();
}

[[cpp11::register]]
cpp11::external_pointer<point3> create_point_3_x_y_z(cpp11::external_pointer<exact_numeric> x,
                                                     cpp11::external_pointer<exact_numeric> y,
                                                     cpp11::external_pointer<exact_numeric> z) {
  std::vector<Point_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    vec.emplace_back((*x)[i], (*y)[i], (*z)[i]);
  }
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point3> create_point_3_vec(cpp11::external_pointer<vector3> p) {
  std::vector<Point_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    vec.emplace_back((*p)[i].x(), (*p)[i].y(), (*p)[i].z());
  }
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point3> point_3_add_vector(cpp11::external_pointer<point3> x, cpp11::external_pointer<vector3> y) {
  std::vector<Point_3> vec = (*x) + y->get_storage();
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point3> point_3_sub_vector(cpp11::external_pointer<point3> x, cpp11::external_pointer<vector3> y) {
  std::vector<Point_3> vec = (*x) - y->get_storage();
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<vector3> point_3_sub_point(cpp11::external_pointer<point3> x, cpp11::external_pointer<point3> y) {
  std::vector<Vector_3> vec = (*x) - y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals point_3_less(cpp11::external_pointer<point3> x, cpp11::external_pointer<point3> y) {
  return (*x) < y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_3_less_equal(cpp11::external_pointer<point3> x, cpp11::external_pointer<point3> y) {
  return (*x) <= y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_3_greater(cpp11::external_pointer<point3> x, cpp11::external_pointer<point3> y) {
  return (*x) > y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_3_greater_equal(cpp11::external_pointer<point3> x, cpp11::external_pointer<point3> y) {
  return (*x) >= y->get_storage();
}

[[cpp11::register]]
cpp11::external_pointer<exact_numeric> point_3_coord(cpp11::external_pointer<point3> x, int i) {
  std::vector<Exact_number> vec = x->coord(i);
  exact_numeric *result(new exact_numeric(vec));
  return {result};
}

[[cpp11::register]]
cpp11::external_pointer<point3> point_3_sort(cpp11::external_pointer<point3> x, bool decreasing) {
  std::vector<Point_3> vec = x->sort(decreasing);
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
cpp11::writable::integers point_3_rank(cpp11::external_pointer<point3> x) {
  return x->rank();
}
