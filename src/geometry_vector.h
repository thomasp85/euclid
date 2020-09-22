#pragma once

#include <vector>
#include <typeinfo>
#include <algorithm>
#include <cpp11/logicals.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/list.hpp>
#include <cpp11/list_of.hpp>
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
  virtual cpp11::external_pointer<geometry_vector_base> assign(cpp11::integers index, const geometry_vector_base& value) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> combine(cpp11::list_of< cpp11::external_pointer<geometry_vector_base> > extra) const = 0;

  // Self-similarity
  virtual cpp11::external_pointer<geometry_vector_base> unique() const = 0;
  virtual cpp11::writable::logicals duplicated() const = 0;
  virtual bool any_duplicated() const = 0;
  virtual cpp11::writable::integers match(const geometry_vector_base& table) const = 0;

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
  geometry_vector(const geometry_vector& copy) : _storage(copy._storage) {}
  geometry_vector& operator=(const geometry_vector& copy) const {
    _storage.clear();
    _storage.assign(_storage.end(), copy._storage.begin(), copy._storage.end());
    return *this;
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

  // Subsetting, assignment, combining etc
  virtual geometry_vector_base* new_from_vector(std::vector<T> vec) const = 0;
  cpp11::external_pointer<geometry_vector_base> subset(cpp11::integers index) const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      new_storage.push_back(_storage[index[i] - 1]);
    }
    return {new_from_vector(new_storage)};
  }
  cpp11::external_pointer<geometry_vector_base> copy() const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    new_storage.insert(new_storage.begin(), _storage.begin(), _storage.end());
    return {new_from_vector(new_storage)};
  }
  cpp11::external_pointer<geometry_vector_base> assign(cpp11::integers index, const geometry_vector_base& value) const {
    if (index.size() != value.size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    if (typeid(*this) != typeid(value)) {
      cpp11::stop("Incompatible assignment value type");
    }

    const geometry_vector<T, dim>* value_recast = dynamic_cast< const geometry_vector<T, dim>* >(&value);

    std::vector<T> new_storage(_storage);
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      new_storage[index[i] - 1] = (*value_recast)[i];
    }
    return {new_from_vector(new_storage)};
  }
  cpp11::external_pointer<geometry_vector_base> combine(cpp11::list_of< cpp11::external_pointer<geometry_vector_base> > extra) const {
    std::vector<T> new_storage(_storage);

    for (R_xlen_t i = 0; i < extra.size(); ++i) {
      geometry_vector_base* candidate = extra[i].get();
      if (typeid(*this) != typeid(*candidate)) {
        cpp11::stop("Incompatible vector types");
      }
      const geometry_vector<T, dim>* candidate_recast = dynamic_cast< const geometry_vector<T, dim>* >(candidate);
      for (size_t j = 0; j < candidate_recast->size(); ++j) {
        new_storage.push_back((*candidate_recast)[j]);
      }
    }

    return {new_from_vector(new_storage)};
  }

  // Self-similarity
  cpp11::external_pointer<geometry_vector_base> unique() const {
    std::vector<T> new_storage;

    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (std::find(new_storage.begin(), new_storage.end(), *iter) == new_storage.end()) {
        new_storage.push_back(*iter);
      }
    }

    return {new_from_vector(new_storage)};
  };
  cpp11::writable::logicals duplicated() const {
    std::vector<T> uniques;
    cpp11::writable::logicals dupes;
    dupes.reserve(size());
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (std::find(uniques.begin(), uniques.end(), *iter) == uniques.end()) {
        uniques.push_back(*iter);
        dupes.push_back(FALSE);
      } else {
        dupes.push_back(TRUE);
      }
    }

    return dupes;
  }
  bool any_duplicated() const {
    bool anyone = false;

    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (std::find(iter + 1, _storage.end(), *iter) != _storage.end()) {
        anyone = true;
        break;
      }
    }

    return anyone;
  }
  cpp11::writable::integers match(const geometry_vector_base& table) const {
    cpp11::writable::integers results;
    results.reserve(size());

    if (typeid(*this) != typeid(table)) {
      for (size_t i = 0; i < size(); ++i) {
        results.push_back(R_NaInt);
      }
      return results;
    }

    const geometry_vector<T, dim>* table_recast = dynamic_cast< const geometry_vector<T, dim>* >(&table);

    std::vector<T> lookup;
    lookup.reserve(table_recast->size());
    for (size_t i = 0; i < table_recast->size(); ++i) {
      lookup.push_back((*table_recast)[i]);
    }

    cpp11::writable::integers result;
    result.reserve(size());
    auto start = lookup.begin();
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      auto match = std::find(lookup.begin(), lookup.end(), *iter);
      if (match == lookup.end()) {
        result.push_back(R_NaInt);
      } else {
        result.push_back((match - start) + 1);
      }
    }

    return result;
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
