#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class tetrahedron : public geometry_vector<Tetrahedron, 3> {
  public:
    using geometry_vector::geometry_vector;
    ~tetrahedron() = default;

    Primitive geometry_type() const { return TETRAHEDRON; }

    size_t cardinality(size_t i) const { return 4; }
    size_t long_length() const { return size() * 4; }

    cpp11::writable::strings def_names() const {
      return {"x", "y", "z"};
    }

    Exact_number get_single_definition(size_t i, int which, int element) const {
      switch(which) {
      case 0: return _storage[i].vertex(element).x();
      case 1: return _storage[i].vertex(element).y();
      case 2: return _storage[i].vertex(element).z();
      }
      return _storage[i].vertex(element).x();
    }

    std::vector<double> get_row(size_t i, size_t j) const {
      return {
        CGAL::to_double(_storage[i].vertex(j).x().exact()),
        CGAL::to_double(_storage[i].vertex(j).y().exact()),
        CGAL::to_double(_storage[i].vertex(j).z().exact())
      };
    }

    cpp11::writable::list intersection(const geometry_vector_base& other) const {
      cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
};

typedef cpp11::external_pointer<tetrahedron> tetrahedron_p;
