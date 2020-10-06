#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class segment2 : public geometry_vector<Segment_2, 2> {
public:
  const Primitive geo_type = SEGMENT;

  using geometry_vector::geometry_vector;
  ~segment2() = default;

  geometry_vector_base* new_from_vector(std::vector<Segment_2> vec) const {
    segment2* copy = new segment2();

    copy->_storage.swap(vec);

    return copy;
  }

  size_t cardinality(size_t i) const { return 2; }
  size_t long_length() const { return size() * 2; }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact())
    };
  }

  std::vector<Segment_2> operator-() const {
    std::vector<Segment_2> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = Segment_2::NA_value();
        continue;
      }
      result.push_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<segment2> segment2_p;

class segment3 : public geometry_vector<Segment_3, 3> {
public:
  const Primitive geo_type = SEGMENT;

  using geometry_vector::geometry_vector;
  ~segment3() = default;

  geometry_vector_base* new_from_vector(std::vector<Segment_3> vec) const {
    segment3* copy = new segment3();

    copy->_storage.swap(vec);

    return copy;
  }

  size_t cardinality(size_t i) const { return 2; }
  size_t long_length() const { return size() * 2; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    case 2: return _storage[i].vertex(element).z();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact()),
      CGAL::to_double(_storage[i].vertex(j).z().exact())
    };
  }

  std::vector<Segment_3> operator-() const {
    std::vector<Segment_3> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = Segment_3::NA_value();
        continue;
      }
      result.emplace_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<segment3> segment3_p;
