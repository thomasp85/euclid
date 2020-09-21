#include "point.h"

#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>

#include <ostream>
#include <iomanip>

cpp11::writable::doubles_matrix point2::as_numeric() const {
  cpp11::writable::doubles_matrix result(size(), 2);

  for (size_t i = 0; i < size(); ++i) {
    result(i, 0) = CGAL::to_double(_storage[i].x());
    result(i, 1) = CGAL::to_double(_storage[i].y());
  }

  result.attr("dimnames") = cpp11::writable::list({R_NilValue, dim_names()});
  return result;
}

cpp11::writable::strings point2::format() const {
  cpp11::writable::strings result(size());

  for (size_t i = 0; i < size(); ++i) {
    std::ostringstream f;
    f << std::setprecision(3);
    f << "<x:" << CGAL::to_double(_storage[i].x()) << ", y:" << CGAL::to_double(_storage[i].y()) << ">";
    result[i] = f.str();
  }

  return result;
}

[[cpp11::register]]
cpp11::external_pointer<point2> create_point_2(cpp11::external_pointer<exact_numeric> x,
                                               cpp11::external_pointer<exact_numeric> y) {
  point2 *points(new point2(*x, *y));

  return {points};
}

cpp11::writable::doubles_matrix point3::as_numeric() const {
  cpp11::writable::doubles_matrix result(size(), 3);

  for (size_t i = 0; i < size(); ++i) {
    result(i, 0) = CGAL::to_double(_storage[i].x());
    result(i, 1) = CGAL::to_double(_storage[i].y());
    result(i, 2) = CGAL::to_double(_storage[i].z());
  }

  result.attr("dimnames") = cpp11::writable::list({R_NilValue, dim_names()});
  return result;
}

cpp11::writable::strings point3::format() const {
  cpp11::writable::strings result(size());

  for (size_t i = 0; i < size(); ++i) {
    std::ostringstream f;
    f << std::setprecision(3);
    f << "<x:" << CGAL::to_double(_storage[i].x()) << ", y:" << CGAL::to_double(_storage[i].y()) << ", z:" << CGAL::to_double(_storage[i].z()) << ">";
    result[i] = f.str();
  }

  return result;
}

[[cpp11::register]]
cpp11::external_pointer<point3> create_point_3(cpp11::external_pointer<exact_numeric> x,
                                               cpp11::external_pointer<exact_numeric> y,
                                               cpp11::external_pointer<exact_numeric> z) {
  point3 *points(new point3(*x, *y, *z));

  return {points};
}
