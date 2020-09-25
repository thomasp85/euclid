#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class vector2 : public geometry_vector<Vector_2, 2> {
  public:
    const Primitive geo_type = VECTOR;

    using geometry_vector::geometry_vector;
    ~vector2() = default;

    geometry_vector_base* new_from_vector(std::vector<Vector_2> vec) const {
      vector2* copy = new vector2();

      copy->_storage.swap(vec);

      return copy;
    }

    cpp11::writable::strings dim_names() const {
      return {"x", "y"};
    }

    std::vector<double> get_row(size_t i, size_t j) const {
      return {
        CGAL::to_double(_storage[i].x().exact()),
        CGAL::to_double(_storage[i].y().exact())
      };
    }

    std::vector<Vector_2> operator+(const std::vector<Vector_2>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_2::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] + other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator-(const std::vector<Vector_2>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_2::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] - other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator-() const {
      std::vector<Vector_2> result;
      result.reserve(size());
      for (size_t i = 0; i < size(); ++i) {
        if (!_storage[i]) {
          result[i] = Vector_2::NA_value();
          continue;
        }
        result.push_back(-_storage[i]);
      }
      return result;
    }
    std::vector<Exact_number> operator*(const std::vector<Vector_2>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Exact_number> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Exact_number::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator*(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_2::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator/(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()] || other[i % other.size()] == 0.0) {
          result[i] = Vector_2::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] / other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> sum(bool na_rm) const {
      if (size() == 0) {
        return {};
      }
      Vector_2 total = _storage[0];

      for (size_t i = 1; i < size(); ++i) {
        if (!_storage[i]) {
          if (!na_rm) {
            total = Vector_2::NA_value();
            break;
          }
          continue;
        }
        total += _storage[i];
      }

      return {total};
    }
    std::vector<Vector_2> cumsum() const {
      std::vector<Vector_2> result;
      result.reserve(size());

      if (size() == 0) {
        return {result};
      }

      Vector_2 cum_sum = _storage[0];
      result.push_back(cum_sum);
      bool is_na = false;

      for (size_t i = 1; i < size(); ++i) {
        if (!is_na && !_storage[i]) {
          is_na = true;
          cum_sum = Vector_2::NA_value();
        }
        if (!is_na) {
          cum_sum += _storage[i];
        }
        result.push_back(cum_sum);
      }

      return {result};
    }
    std::vector<Exact_number> coord(size_t index) const {
      std::vector<Exact_number> result;
      result.reserve(size());
      for (size_t i = 0; i < size(); ++i) {
        result.push_back(_storage[i][index]);
      }

      return result;
    }
};

typedef cpp11::external_pointer<vector2> vector2_p;

class vector3 : public geometry_vector<Vector_3, 3> {
  public:
    const Primitive geo_type = VECTOR;

    using geometry_vector::geometry_vector;
    ~vector3() = default;

    geometry_vector_base* new_from_vector(std::vector<Vector_3> vec) const {
      vector3* copy = new vector3();

      copy->_storage.swap(vec);

      return copy;
    }

    cpp11::writable::strings dim_names() const {
      return {"x", "y", "z"};
    }

    std::vector<double> get_row(size_t i, size_t j) const {
      return {
        CGAL::to_double(_storage[i].x().exact()),
        CGAL::to_double(_storage[i].y().exact()),
        CGAL::to_double(_storage[i].z().exact())
      };
    }

    std::vector<Vector_3> operator+(const std::vector<Vector_3>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_3::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] + other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator-(const std::vector<Vector_3>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_3::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] - other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator-() const {
      std::vector<Vector_3> result;
      result.reserve(size());
      for (size_t i = 0; i < size(); ++i) {
        if (!_storage[i]) {
          result[i] = Vector_3::NA_value();
          continue;
        }
        result.push_back(-_storage[i]);
      }
      return {result};
    }
    std::vector<Exact_number> operator*(const std::vector<Vector_3>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Exact_number> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Exact_number::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator*(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), (size_t) other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()]) {
          result[i] = Vector_3::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator/(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), (size_t) other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        if (!_storage[i % size()] || !other[i % other.size()] || other[i % other.size()] == 0.0) {
          result[i] = Vector_3::NA_value();
          continue;
        }
        result.push_back(_storage[i % size()] / other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> sum(bool na_rm) const {
      if (size() == 0) {
        return {};
      }
      Vector_3 total = _storage[0];

      for (size_t i = 1; i < size(); ++i) {
        if (!_storage[i]) {
          if (!na_rm) {
            total = Vector_3::NA_value();
            break;
          }
          continue;
        }
        total += _storage[i];
      }

      return {total};
    }
    std::vector<Vector_3> cumsum() const {
      std::vector<Vector_3> result;
      result.reserve(size());

      if (size() == 0) {
        return {result};
      }

      Vector_3 cum_sum = _storage[0];
      result.push_back(cum_sum);
      bool is_na = false;

      for (size_t i = 1; i < size(); ++i) {
        if (!is_na && !_storage[i]) {
          is_na = true;
          cum_sum = Vector_3::NA_value();
        }
        if (!is_na) {
          cum_sum += _storage[i];
        }
        result.push_back(cum_sum);
      }

      return {result};
    }
    std::vector<Exact_number> coord(size_t index) const {
      std::vector<Exact_number> result;
      result.reserve(size());

      for (size_t i = 0; i < size(); ++i) {
        result.push_back(_storage[i][index]);
      }

      return result;
    }
};

typedef cpp11::external_pointer<vector3> vector3_p;
