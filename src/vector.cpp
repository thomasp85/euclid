#include "vector.h"
#include "point.h"
#include "ray.h"
#include "exact_numeric.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
vector2_p create_vector_2_empty() {
  std::vector<Vector_2> vec;
  vector2 *result(new vector2(vec));
  return {result};
}

[[cpp11::register]]
vector2_p create_vector_2_point(point2_p p) {
  std::vector<Vector_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Vector_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i].x(), (*p)[i].y());
  }
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p create_vector_2_ray(ray2_p r) {
  std::vector<Vector_2> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Vector_2::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p create_vector_2_x_y(exact_numeric_p x, exact_numeric_p y) {
  std::vector<Vector_2> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i] || !(*y)[i]) {
      vec.push_back(Vector_2::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i]);
  }
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_add_vector(vector2_p x, vector2_p y) {
  std::vector<Vector_2> vec = (*x) + y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_minus_vector(vector2_p x, vector2_p y) {
  std::vector<Vector_2> vec = (*x) - y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_negate(vector2_p x) {
  std::vector<Vector_2> vec = -(*x);
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
exact_numeric_p vector_2_dot_vector(vector2_p x, vector2_p y) {
  std::vector<Exact_number> vec = (*x) * y->get_storage();
  exact_numeric *result(new exact_numeric(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_times_numeric(vector2_p x, exact_numeric_p y) {
  std::vector<Vector_2> vec = (*x) * y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_divide_numeric(vector2_p x, exact_numeric_p y) {
  std::vector<Vector_2> vec = (*x) / y->get_storage();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_sum(vector2_p x, bool na_rm) {
  std::vector<Vector_2> vec = x->sum(na_rm);
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector2_p vector_2_cumsum(vector2_p x) {
  std::vector<Vector_2> vec = x->cumsum();
  vector2 *result(new vector2(vec));

  return {result};
}

[[cpp11::register]]
vector3_p create_vector_3_empty() {
  std::vector<Vector_3> vec;
  vector3 *result(new vector3(vec));
  return {result};
}

[[cpp11::register]]
vector3_p create_vector_3_point(point3_p p) {
  std::vector<Vector_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i]) {
      vec.push_back(Vector_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i].x(), (*p)[i].y(), (*p)[i].z());
  }
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p create_vector_3_ray(ray3_p r) {
  std::vector<Vector_3> vec;
  vec.reserve(r->size());
  for (size_t i = 0; i < r->size(); ++i) {
    if (!(*r)[i]) {
      vec.push_back(Vector_3::NA_value());
      continue;
    }
    vec.emplace_back((*r)[i]);
  }
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p create_vector_3_x_y_z(exact_numeric_p x, exact_numeric_p y, exact_numeric_p z) {
  std::vector<Vector_3> vec;
  vec.reserve(x->size());
  for (size_t i = 0; i < x->size(); ++i) {
    if (!(*x)[i]|| !(*y)[i] || !(*z)[i]) {
      vec.push_back(Vector_3::NA_value());
      continue;
    }
    vec.emplace_back((*x)[i], (*y)[i], (*z)[i]);
  }
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_add_vector(vector3_p x, vector3_p y) {
  std::vector<Vector_3> vec = (*x) + y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_minus_vector(vector3_p x, vector3_p y) {
  std::vector<Vector_3> vec = (*x) - y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_negate(vector3_p x) {
  std::vector<Vector_3> vec = -(*x);
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
exact_numeric_p vector_3_dot_vector(vector3_p x, vector3_p y) {
  std::vector<Exact_number> vec = (*x) * y->get_storage();
  exact_numeric *result(new exact_numeric(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_times_numeric(vector3_p x, exact_numeric_p y) {
  std::vector<Vector_3> vec = (*x) * y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_divide_numeric(vector3_p x, exact_numeric_p y) {
  std::vector<Vector_3> vec = (*x) / y->get_storage();
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_sum(vector3_p x, bool na_rm) {
  std::vector<Vector_3> vec = x->sum(na_rm);
  vector3 *result(new vector3(vec));

  return {result};
}

[[cpp11::register]]
vector3_p vector_3_cumsum(vector3_p x) {
  std::vector<Vector_3> vec = x->cumsum();
  vector3 *result(new vector3(vec));

  return {result};
}
