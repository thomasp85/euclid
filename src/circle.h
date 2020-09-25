#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/logicals.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"

#include <vector>

class circle2 : public geometry_vector<Circle_2, 2> {
public:
  const Primitive geo_type = CIRCLE;

  using geometry_vector::geometry_vector;
  ~circle2() = default;

  geometry_vector_base* new_from_vector(std::vector<Circle_2> vec) const {
    circle2* copy = new circle2();

    copy->_storage.swap(vec);

    return copy;
  }

  cpp11::writable::strings dim_names() const {
    return {"x0", "y0", "r"};
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    return {
      CGAL::to_double(center.x().exact()),
      CGAL::to_double(center.y().exact()),
      CGAL::sqrt(CGAL::to_double(circ.squared_radius().exact()))
    };
  }

  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    for (size_t i = 0; i < _storage.size(); ++i) {
      result.push_back((Rboolean) _storage[i].is_degenerate());
    }
    return result;
  }
};

typedef cpp11::external_pointer<circle2> circle2_p;

//class circle3 : public geometry_vector<Circle_3, 3> {
//public:
//  const Primitive geo_type = CIRCLE;
//
//  using geometry_vector::geometry_vector;
//  ~circle3() = default;
//
//  cpp11::writable::strings dim_names() const {
//    return {"x0", "y0", "z0", "r"};
//  }
//
//  std::vector<double> get_row(size_t i) const {
//    Circle_3 circ = _storage[i];
//    Point_3 center = circ.center();
//    return {
//      CGAL::to_double(center.x().exact()),
//      CGAL::to_double(center.y().exact()),
//      CGAL::to_double(center.z().exact()),
//      CGAL::sqrt(CGAL::to_double(circ.squared_radius().exact()))
//    };
//  }
//};
