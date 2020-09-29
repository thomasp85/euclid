#pragma once

#include <vector>
#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/external_pointer.hpp>
#include <cpp11/list_of.hpp>

#include "cgal_types.h"
#include "exact_numeric.h"

#include <sstream>
#include <iomanip>

class transform_vector_base {
public:
  transform_vector_base() {}
  virtual ~transform_vector_base() = default;

  // Conversion
  virtual cpp11::writable::doubles as_numeric() const = 0;
  virtual cpp11::writable::strings format() const = 0;

  // Equality
  virtual cpp11::writable::logicals operator==(const transform_vector_base& other) const = 0;
  virtual cpp11::writable::logicals operator!=(const transform_vector_base& other) const = 0;
  virtual cpp11::external_pointer<transform_vector_base> operator*(const transform_vector_base& other) const = 0;
  virtual cpp11::external_pointer<transform_vector_base> inverse() const = 0;

  // Dimensions
  virtual size_t size() const = 0;
  virtual size_t dimensions() const = 0;
  virtual exact_numeric definition(cpp11::integers i, cpp11::integers j) const = 0;

  // Subsetting etc
  virtual cpp11::external_pointer<transform_vector_base> subset(cpp11::integers index) const = 0;
  virtual cpp11::external_pointer<transform_vector_base> copy() const = 0;
  virtual cpp11::external_pointer<transform_vector_base> assign(cpp11::integers index, const transform_vector_base& value) const = 0;
  virtual cpp11::external_pointer<transform_vector_base> combine(cpp11::list_of< cpp11::external_pointer<transform_vector_base> > extra) const = 0;

  // Self-similarity
  virtual cpp11::external_pointer<transform_vector_base> unique() const = 0;
  virtual cpp11::writable::logicals duplicated() const = 0;
  virtual int any_duplicated() const = 0;
  virtual cpp11::writable::integers match(const transform_vector_base& table) const = 0;
  virtual cpp11::writable::logicals is_na() const = 0;
  virtual bool any_na() const = 0;

  // Misc
  virtual cpp11::writable::logicals is_reflecting() const = 0;
  virtual cpp11::external_pointer<transform_vector_base> prod(bool na_rm) const = 0;
  virtual cpp11::external_pointer<transform_vector_base> cumprod() const = 0;
};

typedef cpp11::external_pointer<transform_vector_base> transform_vector_base_p;

template <typename T, size_t dim>
class transform_vector : public transform_vector_base {
protected:
  std::vector<T> _storage;

public:
  transform_vector() {}
  // Construct without element copy - BEWARE!
  transform_vector(std::vector<T> content) {
    _storage.swap(content);
  }
  ~transform_vector() = default;
  const std::vector<T>& get_storage() const { return _storage; }

  // Conversion
  cpp11::writable::doubles as_numeric() const {
    size_t ncols = dim + 1;
    cpp11::writable::doubles result;
    result.reserve(ncols * ncols * size());

    for (size_t k = 0; k < size(); ++k) {
      bool is_na = !_storage[k];
      for (size_t i = 0; i < ncols; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
          if (is_na) {
            result.push_back(R_NaReal);
          } else {
            result.push_back(CGAL::to_double(_storage[k].m(i, j)));
          }
        }
      }
    }

    result.attr("dim") = cpp11::writable::integers({(int) ncols, (int) ncols, (int) size()});
    return result;
  }
  cpp11::writable::strings format() const {
    cpp11::writable::strings result(size());
    size_t ncols = dim + 1;

    for (size_t k = 0; k < size(); ++k) {
      if (!_storage[k]) {
        result[k] = "<NA>";
        continue;
      }
      std::ostringstream f;
      f << std::setprecision(3);
      size_t rows = dim;
      f << "<";
      for (size_t i = 0; i < rows; ++i) {
        if (i != 0) {
          f << "/";
        }
        f << "<";
        for (size_t j = 0; j < ncols; ++j) {
          if (j != 0) {
            f << ", ";
          }
          f << CGAL::to_double(_storage[k].m(i, j));
        }
        f << ">";
      }
      f << ">";

      result[k] = f.str();
    }

    return result;
  }
  exact_numeric definition(cpp11::integers i, cpp11::integers j) const {
    std::vector<Exact_number> result;
    result.reserve(size());

    for (size_t k = 0; k < size(); ++k) {
      result.push_back(_storage[k].m(i[k], j[k]));
    }

    return {result};
  }

  // Equality
  cpp11::writable::logicals operator==(const transform_vector_base& other) const {
    size_t output_length = std::max(size(), other.size());

    cpp11::writable::logicals result(output_length);

    if (typeid(*this) != typeid(other)) {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) false;
        return result;
      }
    }

    const transform_vector<T, dim>* other_recast = dynamic_cast< const transform_vector<T, dim>* >(&other);

    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !(*other_recast)[i % other_recast->size()]) {
        result[i] = NA_LOGICAL;
        continue;
      }
      result[i] = (Rboolean) (_storage[i % size()] == (*other_recast)[i % other_recast->size()]);
    }

    return result;
  }
  cpp11::writable::logicals operator!=(const transform_vector_base& other) const {
    size_t output_length = std::max(size(), other.size());

    cpp11::writable::logicals result(output_length);

    if (typeid(*this) != typeid(other)) {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) true;
        return result;
      }
    }

    const transform_vector<T, dim>* other_recast = dynamic_cast< const transform_vector<T, dim>* >(&other);

    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !(*other_recast)[i % other_recast->size()]) {
        result[i] = NA_LOGICAL;
        continue;
      }
      result[i] = (Rboolean) !(_storage[i % size()] == (*other_recast)[i % other_recast->size()]);
    }

    return result;
  }
  transform_vector_base_p operator*(const transform_vector_base& other) const {
    size_t output_length = std::max(size(), other.size());

    if (typeid(*this) != typeid(other)) {
      cpp11::stop("Incompatible vector types");
    }

    std::vector<T> result;
    result.reserve(output_length);

    const transform_vector<T, dim>* other_recast = dynamic_cast< const transform_vector<T, dim>* >(&other);

    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !(*other_recast)[i % other_recast->size()]) {
        result.push_back(T::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] * (*other_recast)[i % other_recast->size()]);
    }

    return {new_from_vector(result)};
  }
  transform_vector_base_p inverse() const {
    std::vector<T> result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = T::NA_value();
        continue;
      }
      result[i] = _storage[i].inverse();
    }

    return {new_from_vector(result)};
  }

  // Utility
  size_t size() const { return _storage.size(); }
  T operator[](size_t i) const { return _storage[i]; }
  void clear() { _storage.clear(); }
  void push_back(T element) { _storage.push_back(element); }
  size_t dimensions() const {
    return dim;
  };

  // Subsetting, assignment, combining etc
  virtual transform_vector_base* new_from_vector(std::vector<T> vec) const = 0;
  transform_vector_base_p subset(cpp11::integers index) const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      if (index[i] == R_NaInt) {
        new_storage.push_back(T::NA_value());
      } else {
        new_storage.push_back(_storage[index[i] - 1]);
      }
    }
    return {new_from_vector(new_storage)};
  }
  transform_vector_base_p copy() const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    new_storage.insert(new_storage.begin(), _storage.begin(), _storage.end());
    return {new_from_vector(new_storage)};
  }
  transform_vector_base_p assign(cpp11::integers index, const transform_vector_base& value) const {
    if (index.size() != value.size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    if (typeid(*this) != typeid(value)) {
      cpp11::stop("Incompatible assignment value type");
    }

    const transform_vector<T, dim>* value_recast = dynamic_cast< const transform_vector<T, dim>* >(&value);

    std::vector<T> new_storage(_storage);
    int max_size = *std::max_element(index.begin(), index.end());
    if (max_size > new_storage.size()) {
      new_storage.reserve(max_size);
      for (int j = new_storage.size(); j < max_size; ++j) {
        new_storage.push_back(T::NA_value());
      }
    }
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      new_storage[index[i] - 1] = (*value_recast)[i];
    }
    return {new_from_vector(new_storage)};
  }
  transform_vector_base_p combine(cpp11::list_of< transform_vector_base_p > extra) const {
    std::vector<T> new_storage(_storage);

    for (R_xlen_t i = 0; i < extra.size(); ++i) {
      transform_vector_base* candidate = extra[i].get();
      if (typeid(*this) != typeid(*candidate)) {
        cpp11::stop("Incompatible vector types");
      }
      const transform_vector<T, dim>* candidate_recast = dynamic_cast< const transform_vector<T, dim>* >(candidate);
      for (size_t j = 0; j < candidate_recast->size(); ++j) {
        new_storage.push_back((*candidate_recast)[j]);
      }
    }

    return {new_from_vector(new_storage)};
  }

  // Self-similarity
  transform_vector_base_p unique() const {
    std::vector<T> new_storage;
    bool NA_seen = false;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!iter->is_valid()) {
        if (!NA_seen) {
          new_storage.push_back(T::NA_value());
          NA_seen = true;
        }
        continue;
      }
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
    bool NA_seen = false;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!iter->is_valid()) {
        if (!NA_seen) {
          dupes.push_back(TRUE);
          NA_seen = true;
        }
        continue;
      }
      if (std::find(uniques.begin(), uniques.end(), *iter) == uniques.end()) {
        uniques.push_back(*iter);
        dupes.push_back(FALSE);
      } else {
        dupes.push_back(TRUE);
      }
    }

    return dupes;
  }
  int any_duplicated() const {
    int anyone = -1;
    bool NA_seen = false;;
    int i = 0;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!_storage[i].is_valid()) {
        if (NA_seen) {
          anyone = i;
          break;
        }
        NA_seen = true;
      } else if (std::find(iter + 1, _storage.end(), *iter) != _storage.end()) {
        anyone = true;
        break;
      }
      ++i;
    }

    return anyone;
  }
  cpp11::writable::integers match(const transform_vector_base& table) const {
    cpp11::writable::integers results;
    results.reserve(size());

    if (typeid(*this) != typeid(table)) {
      for (size_t i = 0; i < size(); ++i) {
        results.push_back(R_NaInt);
      }
      return results;
    }

    const transform_vector<T, dim>* table_recast = dynamic_cast< const transform_vector<T, dim>* >(&table);

    int NA_ind = -1;

    std::vector<T> lookup;
    lookup.reserve(table_recast->size());
    for (size_t i = 0; i < table_recast->size(); ++i) {
      if (NA_ind == -1 && !(*table_recast)[i]) {
        NA_ind = i;
      }
      lookup.push_back((*table_recast)[i]);
    }

    cpp11::writable::integers result;
    result.reserve(size());
    auto start = lookup.begin();
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!iter->is_valid()) {
        if (NA_ind == -1) {
          result.push_back(R_NaInt);
        } else {
          result.push_back(NA_ind + 1);
        }
        continue;
      }
      auto match = std::find(lookup.begin(), lookup.end(), *iter);
      if (match == lookup.end()) {
        result.push_back(R_NaInt);
      } else {
        result.push_back((match - start) + 1);
      }
    }

    return result;
  }
  cpp11::writable::logicals is_na() const {
    cpp11::writable::logicals result;
    result.reserve(size());

    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      result.push_back((Rboolean) !(*iter));
    }

    return result;
  }
  bool any_na() const {
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!(*iter)) {
        return true;
      }
    }
    return false;
  }

  // Misc
  cpp11::writable::logicals is_reflecting() const {
    cpp11::writable::logicals result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = NA_LOGICAL;
        continue;
      }
      result[i] = (Rboolean) _storage[i].is_odd();
    }

    return result;
  }
  transform_vector_base_p prod(bool na_rm) const {
    T total(CGAL::IDENTITY);

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          total = T::NA_value();
          break;
        }
        continue;
      }
      total = total * _storage[i];
    }
    std::vector<T> result;
    result.push_back(total);

    return {new_from_vector(result)};
  }
  transform_vector_base_p cumprod() const {
    std::vector<T> result;
    result.reserve(size());

    T cum_prod(CGAL::IDENTITY);
    bool is_na = false;

    for (size_t i = 0; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_prod = T::NA_value();
      }
      if (!is_na) {
        cum_prod = cum_prod * _storage[i];
      }
      result.push_back(cum_prod);
    }

    return {new_from_vector(result)};
  }
};

class transform2: public transform_vector<Aff_transformation_2, 2> {
public:
  using transform_vector::transform_vector;
  ~transform2() = default;

  transform_vector_base* new_from_vector(std::vector<Aff_transformation_2> vec) const {
    transform2* copy = new transform2();

    copy->_storage.swap(vec);

    return copy;
  }
};
typedef cpp11::external_pointer<transform2> transform2_p;

class transform3: public transform_vector<Aff_transformation_3, 3> {
  public:
    using transform_vector::transform_vector;
    ~transform3() = default;

    transform_vector_base* new_from_vector(std::vector<Aff_transformation_3> vec) const {
      transform3* copy = new transform3();

      copy->_storage.swap(vec);

      return copy;
    }
};
typedef cpp11::external_pointer<transform3> transform3_p;
