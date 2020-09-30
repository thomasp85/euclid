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

  cpp11::writable::strings def_names() const {
    return {"x", "y", "r2"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].center().x();
    case 1: return _storage[i].center().y();
    case 2: return _storage[i].squared_radius();
    }
    return _storage[i].center().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    return {
      CGAL::to_double(center.x().exact()),
      CGAL::to_double(center.y().exact()),
      CGAL::to_double(circ.squared_radius().exact())
    };
  }
};

typedef cpp11::external_pointer<circle2> circle2_p;
