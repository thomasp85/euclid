#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class iso_cube : public geometry_vector<Iso_cuboid, 3> {
public:
  const Primitive geo_type = ISOCUBE;

  using geometry_vector::geometry_vector;
  ~iso_cube() = default;

  geometry_vector_base* new_from_vector(std::vector<Iso_cuboid> vec) const {
    iso_cube* copy = new iso_cube();

    copy->_storage.swap(vec);

    return copy;
  }
  geometry_vector_base* new_2D_from_vector(std::vector<Iso_cuboid> vec) const {
    cpp11::stop("Iso cuboids cannot be mapped to 2D");
  }

  size_t cardinality(size_t i) const { return 8; }
  size_t long_length() const { return size() * 8; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    case 2: return _storage[i].vertex(element).z();
    }
    return _storage[i].vertex(0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact()),
      CGAL::to_double(_storage[i].vertex(j).z().exact())
    };
  }
};

typedef cpp11::external_pointer<iso_cube> iso_cube_p;
