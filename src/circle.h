#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include "cgal_types.h"
#include "geo_vector.h"

class circle2 : public geo_vector<Circle_2, 2> {
public:
  const Primitive geo_type = CIRCLE;

  circle2(cpp11::doubles x, cpp11::doubles y, cpp11::doubles r) {
    _storage.reserve(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
      _storage.emplace_back(Point_2(x[i], y[i]), r[i] * r[i]);
    }
  }
  cpp11::writable::strings dim_names() const {
    return {"x0", "y0", "r"};
  }
  cpp11::writable::doubles_matrix as_numeric() const;
};
