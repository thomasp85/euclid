#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class sphere : public geometry_vector<Sphere, 3> {
public:
  const Primitive geo_type = SPHERE;

  using geometry_vector::geometry_vector;
  ~sphere() = default;

  geometry_vector_base* new_from_vector(std::vector<Sphere> vec) const {
    sphere* copy = new sphere();

    copy->_storage.swap(vec);

    return copy;
  }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "r2"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].center().x();
    case 1: return _storage[i].center().y();
    case 2: return _storage[i].center().z();
    case 3: return _storage[i].squared_radius();
    }
    return _storage[i].center().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].center().x().exact()),
      CGAL::to_double(_storage[i].center().y().exact()),
      CGAL::to_double(_storage[i].center().z().exact()),
      CGAL::to_double(_storage[i].squared_radius().exact())
    };
  }
};

typedef cpp11::external_pointer<sphere> sphere_p;
