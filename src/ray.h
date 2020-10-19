#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class ray2 : public geometry_vector<Ray_2, 2> {
public:
  const Primitive geo_type = RAY;

  using geometry_vector::geometry_vector;
  ~ray2() = default;

  geometry_vector_base* new_from_vector(std::vector<Ray_2> vec) const {
    ray2* copy = new ray2();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Ray_2> vec) const {
    return new_from_vector(vec);
  }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "dx", "dy"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].source().x();
    case 1: return _storage[i].source().y();
    case 2: return _storage[i].direction().dx();
    case 3: return _storage[i].direction().dy();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].source().x().exact()),
      CGAL::to_double(_storage[i].source().y().exact()),
      CGAL::to_double(_storage[i].direction().dx().exact()),
      CGAL::to_double(_storage[i].direction().dy().exact())
    };
  }

  std::vector<Ray_2> operator-() const {
    std::vector<Ray_2> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = Ray_2::NA_value();
        continue;
      }
      result.push_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<ray2> ray2_p;

class ray3 : public geometry_vector<Ray_3, 3, Ray_2> {
public:
  const Primitive geo_type = RAY;

  using geometry_vector::geometry_vector;
  ~ray3() = default;

  geometry_vector_base* new_from_vector(std::vector<Ray_3> vec) const {
    ray3* copy = new ray3();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Ray_2> vec) const {
    ray2* copy = new ray2(vec);
    return copy;
  }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "dx", "dy", "dz"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].source().x();
    case 1: return _storage[i].source().y();
    case 2: return _storage[i].source().z();
    case 3: return _storage[i].direction().dx();
    case 4: return _storage[i].direction().dy();
    case 5: return _storage[i].direction().dz();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].source().x().exact()),
      CGAL::to_double(_storage[i].source().y().exact()),
      CGAL::to_double(_storage[i].source().z().exact()),
      CGAL::to_double(_storage[i].direction().dx().exact()),
      CGAL::to_double(_storage[i].direction().dy().exact()),
      CGAL::to_double(_storage[i].direction().dz().exact())
    };
  }

  std::vector<Ray_3> operator-() const {
    std::vector<Ray_3> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = Ray_3::NA_value();
        continue;
      }
      result.emplace_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<ray3> ray3_p;
