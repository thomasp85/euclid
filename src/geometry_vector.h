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

class geometry_vector_base {
public:
  geometry_vector_base() {}
  virtual ~geometry_vector_base() = default;

  // Conversion
  virtual cpp11::writable::doubles_matrix as_numeric() const = 0;

  // Equality
  virtual cpp11::writable::logicals operator==(const geometry_vector_base& other) const = 0;
  virtual cpp11::writable::logicals operator!=(const geometry_vector_base& other) const = 0;

  // Dimensions
  virtual size_t size() const = 0;
  virtual size_t dimensions() const = 0;
  virtual cpp11::writable::strings dim_names() const = 0;

  // Predicates
  virtual cpp11::writable::logicals is_degenerate() const = 0;
};

template <typename T, size_t dim>
class geometry_vector : public geometry_vector_base {
protected:
  std::vector<T> _storage;

public:
  const Primitive geometry_type = POINT;

  geometry_vector() {}
  geometry_vector(std::vector<T> content) : _storage(content) {}
  geometry_vector(const geometry_vector& copy) : _storage(copy.storage) {}
  geometry_vector& operator=(const geometry_vector& copy) const {
    _storage.clear();
    _storage.assign(_storage.end(), copy._storage.begin(), copy._storage.end());
  }
  ~geometry_vector() = default;

  cpp11::writable::logicals operator==(const geometry_vector& other) const {
    if (other.size() != 1 || other.size() != size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    cpp11::writable::logicals result(size());
    if (other.size() == 1) {
      T geom = other[0];
      for (size_t i = 0; i < size(); ++i) {
        result[i] = _storage[i] == geom;
      }
    } else {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = _storage[i] == other[i];
      }
    }
    return result;
  }
  cpp11::writable::logicals operator!=(const geometry_vector& other) const {
    if (other.size() != 1 || other.size() != size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    cpp11::writable::logicals result(size());
    if (other.size() == 1) {
      T geom = other[0];
      for (size_t i = 0; i < size(); ++i) {
        result[i] = _storage[i] != geom;
      }
    } else {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = _storage[i] != other[i];
      }
    }
    return result;
  }

  size_t size() const { return _storage.size(); }
  T operator[](size_t i) const { return _storage[i]; }
  size_t dimensions() const {
    return dim;
  };

  // Predicates
  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    switch (geometry_type) {
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
