#include "circle.h"

#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>

cpp11::writable::doubles_matrix circle2::as_numeric() const {
  cpp11::writable::doubles_matrix result(size(), dimensions());
  result.attr("dimnames") = cpp11::writable::list({R_NilValue, dim_names()});

  for (size_t i = 0; i < size(); ++i) {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    result(i, 0) = CGAL::to_double(center.x());
    result(i, 1) = CGAL::to_double(center.y());
    result(i, 2) = std::sqrt(CGAL::to_double(circ.squared_radius()));
  }

  return result;
}

[[cpp11::register]]
cpp11::external_pointer<circle2> create_circle_2(cpp11::doubles x, cpp11::doubles y, cpp11::doubles r) {
  circle2 *circles(new circle2(x, y, r));

  return {circles};
}
