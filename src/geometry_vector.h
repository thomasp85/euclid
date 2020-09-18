#pragma once

#include <vector>
#include <typeinfo>
#include <cpp11/logicals.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

enum Primitive {
  VIRTUAL,
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
  const Primitive geometry_type = VIRTUAL;

  geometry_vector_base() {}
  virtual ~geometry_vector_base() = default;

  // Conversion
  virtual cpp11::writable::doubles_matrix as_numeric() const = 0;
  virtual cpp11::writable::strings format() const = 0;

  // Equality
  virtual cpp11::writable::logicals operator==(const geometry_vector_base& other) const = 0;
  virtual cpp11::writable::logicals operator!=(const geometry_vector_base& other) const = 0;

  // Dimensions
  virtual size_t size() const = 0;
  virtual size_t dimensions() const = 0;
  virtual cpp11::writable::strings dim_names() const = 0;

  // Subsetting etc
  virtual cpp11::external_pointer<geometry_vector_base> subset(cpp11::integers index) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> copy() const = 0;

  // Predicates
  virtual cpp11::writable::logicals is_degenerate() const = 0;
};

template <typename T, size_t dim>
class geometry_vector : public geometry_vector_base {
protected:
  std::vector<T> _storage;

public:
  geometry_vector() {}
  // Construct without element copy - BEWARE!
  geometry_vector(std::vector<T> content) {
    _storage.swap(content);
  }
  geometry_vector(const geometry_vector& copy) : _storage(copy.storage) {}
  geometry_vector& operator=(const geometry_vector& copy) const {
    _storage.clear();
    _storage.assign(_storage.end(), copy._storage.begin(), copy._storage.end());
  }
  ~geometry_vector() = default;

  cpp11::writable::logicals operator==(const geometry_vector_base& other) const {
    if (other.size() != 1 && other.size() != size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    cpp11::writable::logicals result(size());

    if (typeid(*this) != typeid(other)) {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) false;
        return result;
      }
    }

    const geometry_vector<T, dim>* other_recast = dynamic_cast< const geometry_vector<T, dim>* >(&other);
    if (other.size() == 1) {
      T geom = (*other_recast)[0];
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) (_storage[i] == geom);
      }
    } else {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) (_storage[i] == (*other_recast)[i]);
      }
    }
    return result;
  }
  cpp11::writable::logicals operator!=(const geometry_vector_base& other) const {
    if (other.size() != 1 && other.size() != size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    cpp11::writable::logicals result(size());

    if (typeid(*this) != typeid(other)) {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) true;
        return result;
      }
    }

    const geometry_vector<T, dim>* other_recast = dynamic_cast< const geometry_vector<T, dim>* >(&other);
    if (other.size() == 1) {
      T geom = (*other_recast)[0];
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) (_storage[i] != geom);
      }
    } else {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) (_storage[i] != (*other_recast)[i]);
      }
    }
    return result;
  }

  size_t size() const { return _storage.size(); }
  T operator[](size_t i) const { return _storage[i]; }
  void clear() { _storage.clear(); }
  void push_back(T element) { _storage.push_back(element); }
  size_t dimensions() const {
    return dim;
  };

  // Subsetting
  virtual geometry_vector_base* new_from_vector(std::vector<T> vec) const = 0;
  cpp11::external_pointer<geometry_vector_base> subset(cpp11::integers index) const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      new_storage.push_back(_storage[index[i]]);
    }
    return {new_from_vector(new_storage)};
  }
  cpp11::external_pointer<geometry_vector_base> copy() const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    new_storage.insert(new_storage.begin(), _storage.begin(), _storage.end());
    return {new_from_vector(new_storage)};
  }

  // Predicates
  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    for (size_t i = 0; i < _storage.size(); ++i) {
      result.push_back((Rboolean) false);
    }
    return result;
  }
};
