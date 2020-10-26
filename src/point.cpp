#include "point.h"
#include "point_w.h"
#include "exact_numeric.h"
#include "vector.h"

#include <cpp11/external_pointer.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>

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

[[cpp11::register]]
cpp11::writable::logicals point_collinear(geometry_vector_base_p x, geometry_vector_base_p y, geometry_vector_base_p z) {
  size_t output_size = std::max(std::max(x->size(), y->size()), z->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  if (x->dimensions() == 2) {
    auto p1 = get_vector_of_geo<Point_2>(*x);
    auto p2 = get_vector_of_geo<Point_2>(*y);
    auto p3 = get_vector_of_geo<Point_2>(*z);
    for (size_t i = 0; i < output_size; ++i) {
      if (!p1[i % p1.size()] || !p2[i % p2.size()] || !p3[i % p3.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::collinear(p1[i % p1.size()], p2[i % p2.size()], p3[i % p3.size()]));
    }
  } else {
    auto p1 = get_vector_of_geo<Point_3>(*x);
    auto p2 = get_vector_of_geo<Point_3>(*y);
    auto p3 = get_vector_of_geo<Point_3>(*z);
    for (size_t i = 0; i < output_size; ++i) {
      if (!p1[i % p1.size()] || !p2[i % p2.size()] || !p3[i % p3.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::collinear(p1[i % p1.size()], p2[i % p2.size()], p3[i % p3.size()]));
    }
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::logicals point_coplanar(point3_p x, point3_p y, point3_p z, point3_p t) {
  size_t output_size = std::max(std::max(std::max(x->size(), y->size()), z->size()), t->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (!(*x)[i % x->size()] || !(*y)[i % y->size()] || !(*z)[i % z->size()] || !(*t)[i % t->size()]) {
      result.push_back(NA_LOGICAL);
      continue;
    }
    result.push_back((Rboolean) CGAL::coplanar((*x)[i % x->size()], (*y)[i % y->size()], (*z)[i % z->size()], (*t)[i % t->size()]));
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::logicals point_ordered(geometry_vector_base_p x, geometry_vector_base_p y, geometry_vector_base_p z) {
  size_t output_size = std::max(std::max(x->size(), y->size()), z->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  if (x->dimensions() == 2) {
    auto p1 = get_vector_of_geo<Point_2>(*x);
    auto p2 = get_vector_of_geo<Point_2>(*y);
    auto p3 = get_vector_of_geo<Point_2>(*z);
    for (size_t i = 0; i < output_size; ++i) {
      if (!p1[i % p1.size()] || !p2[i % p2.size()] || !p3[i % p3.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::are_ordered_along_line(p1[i % p1.size()], p2[i % p2.size()], p3[i % p3.size()]));
    }
  } else {
    auto p1 = get_vector_of_geo<Point_3>(*x);
    auto p2 = get_vector_of_geo<Point_3>(*y);
    auto p3 = get_vector_of_geo<Point_3>(*z);
    for (size_t i = 0; i < output_size; ++i) {
      if (!p1[i % p1.size()] || !p2[i % p2.size()] || !p3[i % p3.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::are_ordered_along_line(p1[i % p1.size()], p2[i % p2.size()], p3[i % p3.size()]));
    }
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::logicals point_ordered_along(geometry_vector_base_p x) {
  cpp11::writable::logicals result;
  result.reserve(x->size() - 2);
  if (x->dimensions() == 2) {
    auto vec = get_vector_of_geo<Point_2>(*x);
    for (size_t i = 0; i < x->size() - 2; ++i) {
      Point_2 p1 = vec[i];
      Point_2 p2 = vec[i + 1];
      Point_2 p3 = vec[i + 2];
      if (!p1 || !p2 || !p3) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::are_ordered_along_line(p1, p2, p3));
    }
  } else {
    auto vec = get_vector_of_geo<Point_3>(*x);
    for (size_t i = 0; i < x->size() - 2; ++i) {
      Point_3 p1 = vec[i];
      Point_3 p2 = vec[i + 1];
      Point_3 p3 = vec[i + 2];
      if (!p1 || !p2 || !p3) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) CGAL::are_ordered_along_line(p1, p2, p3));
    }
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::logicals point_turns_left(point2_p x, point2_p y, point2_p z) {
  size_t output_size = std::max(std::max(x->size(), y->size()), z->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (!(*x)[i % x->size()] || !(*y)[i % y->size()] || !(*z)[i % z->size()]) {
      result.push_back(NA_LOGICAL);
      continue;
    }
    result.push_back((Rboolean) CGAL::left_turn((*x)[i % x->size()], (*y)[i % y->size()], (*z)[i % z->size()]));
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::logicals point_turns_right(point2_p x, point2_p y, point2_p z) {
  size_t output_size = std::max(std::max(x->size(), y->size()), z->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (!(*x)[i % x->size()] || !(*y)[i % y->size()] || !(*z)[i % z->size()]) {
      result.push_back(NA_LOGICAL);
      continue;
    }
    result.push_back((Rboolean) CGAL::right_turn((*x)[i % x->size()], (*y)[i % y->size()], (*z)[i % z->size()]));
  }
  return result;
}

[[cpp11::register]]
cpp11::writable::integers point_turns(point2_p x) {
  cpp11::writable::integers result;
  result.reserve(x->size() - 2);
  for (size_t i = 0; i < x->size() - 2; ++i) {
    Point_2 p1 = (*x)[i];
    Point_2 p2 = (*x)[i + 1];
    Point_2 p3 = (*x)[i + 2];
    if (!p1 || !p2 || !p3) {
      result.push_back(R_NaInt);
      continue;
    }
    if (CGAL::left_turn(p1, p2, p3)) {
      result.push_back(1);
      continue;
    }
    if (CGAL::right_turn(p1, p2, p3)) {
      result.push_back(-1);
      continue;
    }
    result.push_back(0);
  }
  return result;
}
