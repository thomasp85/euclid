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
        result.push_back(_storage[i % size()] + other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator-(const std::vector<Vector_2>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] - other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator-() const {
      std::vector<Vector_2> result;
      result.reserve(size());
      for (size_t i = 0; i < size(); ++i) {
        result.push_back(-_storage[i]);
      }
      return result;
    }
    std::vector<Exact_number> operator*(const std::vector<Vector_2>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Exact_number> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator*(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return result;
    }
    std::vector<Vector_2> operator/(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_2> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] / other[i % other.size()]);
      }
      return result;
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
        result.push_back(_storage[i % size()] + other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator-(const std::vector<Vector_3>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] - other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator-() const {
      std::vector<Vector_3> result;
      result.reserve(size());
      for (size_t i = 0; i < size(); ++i) {
        result.push_back(-_storage[i]);
      }
      return {result};
    }
    std::vector<Exact_number> operator*(const std::vector<Vector_3>& other) const {
      size_t final_size = std::max(size(), other.size());
      std::vector<Exact_number> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator*(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), (size_t) other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] * other[i % other.size()]);
      }
      return {result};
    }
    std::vector<Vector_3> operator/(const std::vector<Exact_number>& other) const {
      size_t final_size = std::max(size(), (size_t) other.size());
      std::vector<Vector_3> result;
      result.reserve(final_size);
      for (size_t i = 0; i < final_size; ++i) {
        result.push_back(_storage[i % size()] / other[i % other.size()]);
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
