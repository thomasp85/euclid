#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class triangle2 : public geometry_vector<Triangle_2, 2> {
public:
  const Primitive geo_type = TRIANGLE;

  using geometry_vector::geometry_vector;
  ~triangle2() = default;

  geometry_vector_base* new_from_vector(std::vector<Triangle_2> vec) const {
    triangle2* copy = new triangle2();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Triangle_2> vec) const {
    return new_from_vector(vec);
  }

  size_t cardinality(size_t i) const { return 3; }
  size_t long_length() const { return size() * 3; }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    }
    return _storage[i].vertex(0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact())
    };
  }
};

typedef cpp11::external_pointer<triangle2> triangle2_p;

class triangle3 : public geometry_vector<Triangle_3, 3, Triangle_2> {
public:
  const Primitive geo_type = TRIANGLE;

  using geometry_vector::geometry_vector;
  ~triangle3() = default;

  geometry_vector_base* new_from_vector(std::vector<Triangle_3> vec) const {
    triangle3* copy = new triangle3();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Triangle_2> vec) const {
    triangle2* copy = new triangle2(vec);
    return copy;
  }

  size_t cardinality(size_t i) const { return 3; }
  size_t long_length() const { return size() * 3; }

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

typedef cpp11::external_pointer<triangle3> triangle3_p;
