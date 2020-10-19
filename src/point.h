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

  geometry_vector_base* new_2D_from_vector(std::vector<Point_2> vec) const {
    return new_from_vector(vec);
  }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].x();
    case 1: return _storage[i].y();
    }
    return _storage[i].x();
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
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] + other[i % other.size()]);
    }
    return result;
  }
  std::vector<Point_2> operator-(const std::vector<Vector_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_2> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  std::vector<Vector_2> operator-(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Vector_2> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Vector_2::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  cpp11::writable::logicals operator<(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] < other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator<=(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] <= other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] > other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>=(const std::vector<Point_2>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] >= other[i % other.size()]));
    }
    return result;
  }
  std::vector<Point_2> sort(bool decreasing, cpp11::logicals na_last) const {
    std::vector<Point_2> result(_storage.begin(), _storage.end());

    auto end = std::remove_if(result.begin(), result.end(), [](const Point_2& x) { return !x.is_valid(); });
    int n_na = result.end() - end;
    result.resize(end - result.begin());

    if (decreasing) {
      std::stable_sort(result.begin(), result.end(), std::greater<Point_2>());
    } else {
      std::stable_sort(result.begin(), result.end());
    }

    if (cpp11::is_na(na_last[0])) {
      for (int i = 0; i < n_na; ++i) {
        result.push_back(Point_2::NA_value());
      }
      if (n_na > 0 && na_last[0] == FALSE) {
        std::rotate(result.rbegin(), result.rbegin() + n_na, result.rend());
      }
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
      if (l.first && r.first) {
        return l.first < r.first;
      } else if (l.first) {
        return true;
      }
      return false;
    });

    cpp11::writable::integers result;
    result.reserve(size());
    for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
      result.push_back(iter->second + 1);
    }

    return result;
  }
  std::vector<Point_2> min(bool na_rm) const {
    if (size() == 0) {
      return {Point_2::NA_value()};
    }
    Point_2 minimum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          minimum = Point_2::NA_value();
          break;
        }
        continue;
      }
      minimum = _storage[i] < minimum ? _storage[i] : minimum;
    }

    return {minimum};
  }
  std::vector<Point_2> max(bool na_rm) const {
    if (size() == 0) {
      return {Point_2::NA_value()};
    }
    Point_2 maximum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          maximum = Point_2::NA_value();
          break;
        }
        continue;
      }
      maximum = _storage[i] > maximum ? _storage[i] : maximum;
    }

    return {maximum};
  }
  std::vector<Point_2> cummin() const {
    std::vector<Point_2> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Point_2 cum_min = _storage[0];
    result.push_back(cum_min);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_min = Point_2::NA_value();
      }
      if (!is_na) {
        cum_min = _storage[i] < cum_min ? _storage[i] : cum_min;
      }
      result.push_back(cum_min);
    }

    return {result};
  }
  std::vector<Point_2> cummax() const {
    std::vector<Point_2> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Point_2 cum_max = _storage[0];
    result.push_back(cum_max);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_max = Point_2::NA_value();
      }
      if (!is_na) {
        cum_max = _storage[i] < cum_max ? _storage[i] : cum_max;
      }
      result.push_back(cum_max);
    }

    return {result};
  }
};

typedef cpp11::external_pointer<point2> point2_p;

class point3 : public geometry_vector<Point_3, 3, Point_2> {
public:
  const Primitive geo_type = POINT;

  using geometry_vector::geometry_vector;
  ~point3() = default;

  geometry_vector_base* new_from_vector(std::vector<Point_3> vec) const {
    point3* copy = new point3();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Point_2> vec) const {
    point2* copy = new point2(vec);
    return copy;
  }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].x();
    case 1: return _storage[i].y();
    case 2: return _storage[i].z();
    }
    return _storage[i].x();
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
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] + other[i % other.size()]);
    }
    return result;
  }
  std::vector<Point_3> operator-(const std::vector<Vector_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Point_3> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  std::vector<Vector_3> operator-(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    std::vector<Vector_3> result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(Vector_3::NA_value());
        continue;
      }
      result.push_back(_storage[i % size()] - other[i % other.size()]);
    }
    return result;
  }
  cpp11::writable::logicals operator<(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] < other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator<=(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] <= other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] > other[i % other.size()]));
    }
    return result;
  }
  cpp11::writable::logicals operator>=(const std::vector<Point_3>& other) const {
    size_t final_size = std::max(size(), other.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !other[i % other.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) (_storage[i % size()] >= other[i % other.size()]));
    }
    return result;
  }
  std::vector<Point_3> sort(bool decreasing, cpp11::logicals na_last) const {
    std::vector<Point_3> result(_storage.begin(), _storage.end());

    auto end = std::remove_if(result.begin(), result.end(), [](const Point_3& x) { return !x.is_valid(); });
    int n_na = result.end() - end;
    result.resize(end - result.begin());

    if (decreasing) {
      std::stable_sort(result.begin(), result.end(), std::greater<Point_3>());
    } else {
      std::stable_sort(result.begin(), result.end());
    }

    if (cpp11::is_na(na_last[0])) {
      for (int i = 0; i < n_na; ++i) {
        result.push_back(Point_3::NA_value());
      }
      if (n_na > 0 && na_last[0] == FALSE) {
        std::rotate(result.rbegin(), result.rbegin() + n_na, result.rend());
      }
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
      if (l.first && r.first) {
        return l.first < r.first;
      } else if (l.first) {
        return true;
      }
      return false;
    });

    cpp11::writable::integers result;
    result.reserve(size());
    for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
      result.push_back(iter->second + 1);
    }

    return result;
  }
  std::vector<Point_3> min(bool na_rm) const {
    if (size() == 0) {
      return {Point_3::NA_value()};
    }
    Point_3 minimum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          minimum = Point_3::NA_value();
          break;
        }
        continue;
      }
      minimum = _storage[i] < minimum ? _storage[i] : minimum;
    }

    return {minimum};
  }
  std::vector<Point_3> max(bool na_rm) const {
    if (size() == 0) {
      return {Point_3::NA_value()};
    }
    Point_3 maximum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          maximum = Point_3::NA_value();
          break;
        }
        continue;
      }
      maximum = _storage[i] > maximum ? _storage[i] : maximum;
    }

    return {maximum};
  }
  std::vector<Point_3> cummin() const {
    std::vector<Point_3> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Point_3 cum_min = _storage[0];
    result.push_back(cum_min);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_min = Point_3::NA_value();
      }
      if (!is_na) {
        cum_min = _storage[i] < cum_min ? _storage[i] : cum_min;
      }
      result.push_back(cum_min);
    }

    return {result};
  }
  std::vector<Point_3> cummax() const {
    std::vector<Point_3> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Point_3 cum_max = _storage[0];
    result.push_back(cum_max);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_max = Point_3::NA_value();
      }
      if (!is_na) {
        cum_max = _storage[i] < cum_max ? _storage[i] : cum_max;
      }
      result.push_back(cum_max);
    }

    return {result};
  }
};

typedef cpp11::external_pointer<point3> point3_p;
