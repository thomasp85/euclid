#pragma once

#include <cpp11/strings.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

#include <vector>

class point2 : public geometry_vector<Point_2, 2> {
public:
  const Primitive geo_type = POINT;

  using geometry_vector::geometry_vector;
  ~point2() = default;

  geometry_vector_base* new_from_vector(std::vector<Point_2> vec) const {
    point2* copy = new point2();

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

  std::vector<Point_2> operator+(const std::vector<Vector_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_2> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] + other[i % other.size()]);
    }
    return result;
  }
  std::vector<Point_2> operator-(const std::vector<Vector_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_2> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  std::vector<Vector_2> operator-(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Vector_2> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  cpp11::writable::logicals operator<(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] < other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator<=(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] <= other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] > other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>=(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] >= other[i % other.size()]));
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
  std::vector<Point_2> sort(bool decreasing) const {
    std::vector<Point_2> result(_storage.begin(), _storage.end());

    if (decreasing) {
      std::stable_sort(result.begin(), result.end(), std::greater<Point_2>());
    } else {
      std::stable_sort(result.begin(), result.end());
    }

    return result;
  }
  cpp11::writable::integers rank() const {
    std::vector< std::pair<Point_2, size_t> > ranks;
    ranks.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      ranks.emplace_back(_storage[i], i);
    }

    std::stable_sort(ranks.begin(), ranks.end(), [](const std::pair<Point_2, size_t>& l, const std::pair<Point_2, size_t> & r) {
      return l.first < r.first;
    });

    cpp11::writable::integers result;
    result.reserve(size());
    for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
      result.push_back(iter->second + 1);
    }

    return result;
  }
};

typedef cpp11::external_pointer<point2> point2_p;

class point3 : public geometry_vector<Point_3, 3> {
public:
  const Primitive geo_type = POINT;

  using geometry_vector::geometry_vector;
  ~point3() = default;

  geometry_vector_base* new_from_vector(std::vector<Point_3> vec) const {
    point3* copy = new point3();

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

  std::vector<Point_3> operator+(const std::vector<Vector_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_3> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] + other[i % other.size()]);
    }
    return result;
  }
  std::vector<Point_3> operator-(const std::vector<Vector_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_3> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  std::vector<Vector_3> operator-(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Vector_3> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  cpp11::writable::logicals operator<(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] < other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator<=(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] <= other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] > other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>=(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      result.push_back((Rboolean) (_storage[i % size()] >= other[i % other.size()]));
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
  std::vector<Point_3> sort(bool decreasing) const {
    std::vector<Point_3> result(_storage.begin(), _storage.end());

    if (decreasing) {
      std::stable_sort(result.begin(), result.end(), std::greater<Point_3>());
    } else {
      std::stable_sort(result.begin(), result.end());
    }

    return result;
  }
  cpp11::writable::integers rank() const {
    std::vector< std::pair<Point_3, size_t> > ranks;
    ranks.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      ranks.emplace_back(_storage[i], i);
    }

    std::stable_sort(ranks.begin(), ranks.end(), [](const std::pair<Point_3, size_t>& l, const std::pair<Point_3, size_t> & r) {
      return l.first < r.first;
    });

    cpp11::writable::integers result;
    result.reserve(size());
    for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
      result.push_back(iter->second + 1);
    }

    return result;
  }
};

typedef cpp11::external_pointer<point3> point3_p;
