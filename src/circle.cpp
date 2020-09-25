#include "circle.h"
#include "point.h"
#include "exact_numeric.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
circle2_p create_circle_2_center_radius(point2_p center, exact_numeric_p r) {
  std::vector<Circle_2> vec;
  vec.reserve(center->size());
  for (size_t i = 0; i < center->size(); ++i) {
    if (!(*center)[i] || !(*r)[i]) {
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    vec.emplace_back((*center)[i], (*r)[i] * (*r)[i]);
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
      cpp11::warning("circle cannot be constructed from 3 colliniar points");
      vec.push_back(Circle_2::NA_value());
      continue;
    }
    if (CGAL::collinear((*p)[i], (*q)[i], (*r)[i])) {
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

//cpp11::writable::doubles_matrix circle3::as_numeric() const {
//  cpp11::writable::doubles_matrix result(size(), 4);
//
//  for (size_t i = 0; i < size(); ++i) {
//    Circle_3 circ = _storage[i];
//    Point_3 center = circ.center();
//    result(i, 0) = CGAL::to_double(center.x());
//    result(i, 1) = CGAL::to_double(center.y());
//    result(i, 2) = CGAL::to_double(center.z());
//    result(i, 3) = CGAL::sqrt(CGAL::to_double(circ.squared_radius()));
//  }
//
//  result.attr("dimnames") = cpp11::writable::list({R_NilValue, dim_names()});
//  return result;
//}
//
//cpp11::writable::strings circle3::format() const {
//  cpp11::writable::strings result(size());
//
//  for (size_t i = 0; i < size(); ++i) {
//    Circle_3 circ = _storage[i];
//    Point_3 center = circ.center();
//    std::ostringstream f;
//    f << std::setprecision(3);
//    f << "<x:" << CGAL::to_double(center.x()) << ", y:" << CGAL::to_double(center.y()) << ", z:" << CGAL::to_double(center.z()) << ", r:" << CGAL::sqrt(CGAL::to_double(circ.squared_radius())) << ">";
//    result[i] = f.str();
//  }
//
//  return result;
//}
//
//[[cpp11::register]]
//cpp11::external_pointer<circle3> create_circle_3(cpp11::doubles x, cpp11::doubles y, cpp11::doubles z, cpp11::doubles r) {
//  circle3 *circles(new circle3(x, y, z, r));
//
//  return {circles};
//}
