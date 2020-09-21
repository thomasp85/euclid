#include "circle.h"

#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>

#include <ostream>
#include <iomanip>

cpp11::writable::doubles_matrix circle2::as_numeric() const {
  cpp11::writable::doubles_matrix result(size(), 3);

  for (size_t i = 0; i < size(); ++i) {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    result(i, 0) = CGAL::to_double(center.x());
    result(i, 1) = CGAL::to_double(center.y());
    result(i, 2) = CGAL::sqrt(CGAL::to_double(circ.squared_radius()));
  }

  result.attr("dimnames") = cpp11::writable::list({R_NilValue, dim_names()});
  return result;
}

cpp11::writable::strings circle2::format() const {
  cpp11::writable::strings result(size());

  for (size_t i = 0; i < size(); ++i) {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    std::ostringstream f;
    f << std::setprecision(3);
    f << "<x:" << CGAL::to_double(center.x()) << ", y:" << CGAL::to_double(center.y()) << ", r:" << CGAL::sqrt(CGAL::to_double(circ.squared_radius())) << ">";
    result[i] = f.str();
  }

  return result;
}

[[cpp11::register]]
cpp11::external_pointer<circle2> create_circle_2_center_radius(cpp11::external_pointer<point2> center, cpp11::external_pointer<exact_numeric> r) {
  std::vector<Circle_2> circle_vec;
  circle_vec.reserve(center->size());
  for (size_t i = 0; i < center->size(); ++i) {
    circle_vec.emplace_back((*center)[i], (*r)[i] * (*r)[i]);
  }
  circle2 *circles(new circle2(circle_vec));

  return {circles};
}
[[cpp11::register]]
cpp11::external_pointer<circle2> create_circle_2_3_point(cpp11::external_pointer<point2> p, cpp11::external_pointer<point2> q, cpp11::external_pointer<point2> r) {
  std::vector<Circle_2> circle_vec;
  circle_vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    circle_vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  circle2 *circles(new circle2(circle_vec));

  return {circles};
}
[[cpp11::register]]
cpp11::external_pointer<circle2> create_circle_2_2_point(cpp11::external_pointer<point2> p, cpp11::external_pointer<point2> q) {
  std::vector<Circle_2> circle_vec;
  circle_vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    circle_vec.emplace_back((*p)[i], (*q)[i]);
  }
  circle2 *circles(new circle2(circle_vec));

  return {circles};
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
