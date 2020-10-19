#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class plane : public geometry_vector<Plane, 3> {
public:
  const Primitive geo_type = PLANE;

  using geometry_vector::geometry_vector;
  ~plane() = default;

  geometry_vector_base* new_from_vector(std::vector<Plane> vec) const {
    plane* copy = new plane();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Plane> vec) const {
    cpp11::stop("Planes cannot be mapped to 2D");
  }

  cpp11::writable::strings def_names() const {
    return {"a", "b", "c", "d"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].a();
    case 1: return _storage[i].b();
    case 2: return _storage[i].c();
    case 3: return _storage[i].d();
    }
    return _storage[i].a();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].a().exact()),
      CGAL::to_double(_storage[i].b().exact()),
      CGAL::to_double(_storage[i].c().exact()),
      CGAL::to_double(_storage[i].d().exact())
    };
  }
};

typedef cpp11::external_pointer<plane> plane_p;
