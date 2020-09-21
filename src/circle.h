#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "point.h"
#include "exact_numeric.h"

class circle2 : public geometry_vector<Circle_2, 2> {
public:
  const Primitive geo_type = CIRCLE;

  using geometry_vector::geometry_vector;
  ~circle2() = default;

  circle2() : geometry_vector() {}
  circle2(cpp11::doubles x, cpp11::doubles y, cpp11::doubles r) : geometry_vector(){
    _storage.reserve(x.size());
    for (R_xlen_t i = 0; i < x.size(); ++i) {
      _storage.emplace_back(Point_2(x[i], y[i]), r[i] * r[i]);
    }
  }
  circle2(const point2& center, const exact_numeric& r) : geometry_vector(){
    _storage.reserve(center.size());
    for (size_t i = 0; i < center.size(); ++i) {
      _storage.emplace_back(center[i], r[i] * r[i]);
    }
  }

  geometry_vector_base* new_from_vector(std::vector<Circle_2> vec) const {
    circle2* copy = new circle2();

    copy->_storage.swap(vec);

    return copy;
  }

  cpp11::writable::strings dim_names() const {
    return {"x0", "y0", "r"};
  }
  cpp11::writable::doubles_matrix as_numeric() const;
  cpp11::writable::strings format() const;

  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    for (size_t i = 0; i < _storage.size(); ++i) {
      result.push_back((Rboolean) _storage[i].is_degenerate());
    }
    return result;
  }
};

//class circle3 : public geometry_vector<Circle_3, 3> {
//public:
//  const Primitive geo_type = CIRCLE;
//
//  ~circle3() = default;
//
//  circle3(cpp11::doubles x, cpp11::doubles y, cpp11::doubles z, cpp11::doubles r) : geometry_vector(){
//    _storage.reserve(x.size());
//    for (R_xlen_t i = 0; i < x.size(); ++i) {
//      _storage.emplace_back(Point_3(x[i], y[i], z[i]), r[i] * r[i]);
//    }
//  }
//  cpp11::writable::strings dim_names() const {
//    return {"x0", "y0", "z0", "r"};
//  }
//  cpp11::writable::doubles_matrix as_numeric() const;
//  cpp11::writable::strings format() const;
//};
