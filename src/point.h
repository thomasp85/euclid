#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"

class point2 : public geometry_vector<Point_2, 2> {
public:
  const Primitive geo_type = POINT;

  ~point2() = default;

  point2() : geometry_vector() {}
  point2(cpp11::doubles x, cpp11::doubles y) : geometry_vector(){
    _storage.reserve(x.size());
    for (R_xlen_t i = 0; i < x.size(); ++i) {
      _storage.emplace_back(x[i], y[i]);
    }
  }

  geometry_vector_base* new_from_vector(std::vector<Point_2> vec) const {
    point2* copy = new point2();

    copy->_storage.swap(vec);

    return copy;
  }

  cpp11::writable::strings dim_names() const {
    return {"x", "y"};
  }
  cpp11::writable::doubles_matrix as_numeric() const;
  cpp11::writable::strings format() const;
};

class point3 : public geometry_vector<Point_3, 3> {
public:
  const Primitive geo_type = POINT;

  ~point3() = default;

  point3() : geometry_vector() {}
  point3(cpp11::doubles x, cpp11::doubles y, cpp11::doubles z) : geometry_vector(){
    _storage.reserve(x.size());
    for (R_xlen_t i = 0; i < x.size(); ++i) {
      _storage.emplace_back(x[i], y[i], z[i]);
    }
  }

  geometry_vector_base* new_from_vector(std::vector<Point_3> vec) const {
    point3* copy = new point3();

    copy->_storage.swap(vec);

    return copy;
  }

  cpp11::writable::strings dim_names() const {
    return {"x", "y", "z"};
  }
  cpp11::writable::doubles_matrix as_numeric() const;
  cpp11::writable::strings format() const;
};
