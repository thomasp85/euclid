#include "point.h"
#include "point_w.h"
#include "exact_numeric.h"
#include "vector.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
point2_p create_point_2_empty() {
  std::vector<Point_2> vec;
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
point2_p create_point_2_x_y(exact_numeric_p x, exact_numeric_p y) {
  std::vector<Point_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i]) {
      vec.push_back(Point_2::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i]);
  }
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
point2_p create_point_2_vec(vector2_p p) {
  std::vector<Point_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Point_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i].x(), (*p)[i].y());
  }
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
point2_p create_point_2_wp(point_w2_p p) {
  std::vector<Point_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Point_2::NA_value());
      continue;
    }
    vec.push_back((*p)[i].point());
  }
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
point2_p point_2_add_vector(point2_p x, vector2_p y) {
  std::vector<Point_2> vec = (*x) + y->get_storage();
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
point2_p point_2_sub_vector(point2_p x, vector2_p y) {
  std::vector<Point_2> vec = (*x) - y->get_storage();
  point2 *result(new point2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p point_2_sub_point(point2_p x, point2_p y) {
  std::vector<Vector_2> vec = (*x) - y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals point_2_less(point2_p x, point2_p y) {
  return (*x) < y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_2_greater(point2_p x, point2_p y) {
  return (*x) > y->get_storage();
}

[[cpp11::register]]
point2_p point_2_sort(point2_p x, bool decreasing, cpp11::logicals na_last) {
  std::vector<Point_2> vec = x->sort(decreasing, na_last);
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
cpp11::writable::integers point_2_rank(point2_p x) {
  return x->rank();
}

[[cpp11::register]]
point2_p point_2_min(point2_p x, bool na_rm) {
  std::vector<Point_2> vec = x->min(na_rm);
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
point2_p point_2_max(point2_p x, bool na_rm) {
  std::vector<Point_2> vec = x->max(na_rm);
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
point2_p point_2_cummin(point2_p x) {
  std::vector<Point_2> vec = x->cummin();
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
point2_p point_2_cummax(point2_p x) {
  std::vector<Point_2> vec = x->cummax();
  point2 *result(new point2(vec));
  return {result};
}

[[cpp11::register]]
point3_p create_point_3_empty() {
  std::vector<Point_3> vec;
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
point3_p create_point_3_x_y_z(exact_numeric_p x, exact_numeric_p y, exact_numeric_p z) {
  std::vector<Point_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i] || !(*z)[i]) {
      vec.push_back(Point_3::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i], (*z)[i]);
  }
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
point3_p create_point_3_vec(vector3_p p) {
  std::vector<Point_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Point_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i].x(), (*p)[i].y(), (*p)[i].z());
  }
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
point3_p create_point_3_wp(point_w3_p p) {
  std::vector<Point_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Point_3::NA_value());
      continue;
    }
    vec.push_back((*p)[i].point());
  }
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
point3_p point_3_add_vector(point3_p x, vector3_p y) {
  std::vector<Point_3> vec = (*x) + y->get_storage();
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
point3_p point_3_sub_vector(point3_p x, vector3_p y) {
  std::vector<Point_3> vec = (*x) - y->get_storage();
  point3 *result(new point3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p point_3_sub_point(point3_p x, point3_p y) {
  std::vector<Vector_3> vec = (*x) - y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
cpp11::writable::logicals point_3_less(point3_p x, point3_p y) {
  return (*x) < y->get_storage();
}

[[cpp11::register]]
cpp11::writable::logicals point_3_greater(point3_p x, point3_p y) {
  return (*x) > y->get_storage();
}

[[cpp11::register]]
point3_p point_3_sort(point3_p x, bool decreasing, cpp11::logicals na_last) {
  std::vector<Point_3> vec = x->sort(decreasing, na_last);
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
cpp11::writable::integers point_3_rank(point3_p x) {
  return x->rank();
}

[[cpp11::register]]
point3_p point_3_min(point3_p x, bool na_rm) {
  std::vector<Point_3> vec = x->min(na_rm);
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
point3_p point_3_max(point3_p x, bool na_rm) {
  std::vector<Point_3> vec = x->max(na_rm);
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
point3_p point_3_cummin(point3_p x) {
  std::vector<Point_3> vec = x->cummin();
  point3 *result(new point3(vec));
  return {result};
}

[[cpp11::register]]
point3_p point_3_cummax(point3_p x) {
  std::vector<Point_3> vec = x->cummax();
  point3 *result(new point3(vec));
  return {result};
}
