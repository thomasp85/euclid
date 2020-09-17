#pragma once

#include <vector>
#include <cpp11/logicals.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/list.hpp>


enum Primitive {
  CIRCLE,
  DIRECTION,
  ISOCUBE,
  ISORECT,
  LINE,
  PLANE,
  POINT,
  RAY,
  SEGMENT,
  SPHERE,
  TETRAHEDRON,
  TRIANGLE,
  VECTOR,
  WPOINT
};

template <typename T, size_t dim>
class geo_vector {
protected:
  std::vector<T> _storage;

public:
  const Primitive geo_type = POINT;

  geo_vector() {}
  geo_vector(std::vector<T> content) : _storage(content) {}

  virtual ~geo_vector() {};

  size_t size() const { return _storage.size(); }
  T operator[](size_t i) const { return _storage[i]; }
  size_t dimensions() const {
    return dim;
  };
  virtual cpp11::writable::strings dim_names() const = 0;

  // Conversion
  virtual cpp11::writable::doubles_matrix as_numeric() const = 0;

  // Predicates
  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    switch (geo_type) {
    case DIRECTION:
    case POINT:
    case VECTOR:
    case WPOINT:
      for (size_t i = 0; i < _storage.size(); ++i) {
        result.push_back((Rboolean) false);
      }
      return result;
    }

    for (size_t i = 0; i < _storage.size(); ++i) {
      result.push_back((Rboolean) _storage[i].is_degenerate());
    }
    return result;
  }
};
