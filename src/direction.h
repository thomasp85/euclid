#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"

class direction2 : public geometry_vector<Direction_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~direction2() = default;

  Primitive geometry_type() const { return DIRECTION; }

  cpp11::writable::strings def_names() const {
    return {"dx", "dy"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].dx();
    case 1: return _storage[i].dy();
    }
    return _storage[i].dx();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].dx().exact()),
      CGAL::to_double(_storage[i].dy().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  std::vector<Direction_2> operator-() const {
    std::vector<Direction_2> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(Direction_2::NA_value());
        continue;
      }
      result.push_back(-_storage[i]);
    }
    return result;
  }

  cpp11::writable::logicals operator<(const std::vector<Direction_2>& other) const {
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
  cpp11::writable::logicals operator<=(const std::vector<Direction_2>& other) const {
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
  cpp11::writable::logicals operator>(const std::vector<Direction_2>& other) const {
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
  cpp11::writable::logicals operator>=(const std::vector<Direction_2>& other) const {
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
  std::vector<Direction_2> sort(bool decreasing, cpp11::logicals na_last) const {
    std::vector<Direction_2> result(_storage.begin(), _storage.end());

    auto end = std::remove_if(result.begin(), result.end(), [](const Direction_2& x) { return !x.is_valid(); });
    int n_na = result.end() - end;
    result.resize(end - result.begin());

    if (decreasing) {
      std::stable_sort(result.begin(), result.end(), std::greater<Direction_2>());
    } else {
      std::stable_sort(result.begin(), result.end());
    }

    if (cpp11::is_na(na_last[0])) {
      for (int i = 0; i < n_na; ++i) {
        result.push_back(Direction_2::NA_value());
      }
      if (n_na > 0 && na_last[0] == FALSE) {
        std::rotate(result.rbegin(), result.rbegin() + n_na, result.rend());
      }
    }

    return result;
  }
  cpp11::writable::integers rank() const {
    std::vector< std::pair<Direction_2, size_t> > ranks;
    ranks.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      ranks.emplace_back(_storage[i], i);
    }

    std::stable_sort(ranks.begin(), ranks.end(), [](const std::pair<Direction_2, size_t>& l, const std::pair<Direction_2, size_t> & r) {
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
  std::vector<Direction_2> min(bool na_rm) const {
    if (size() == 0) {
      return {Direction_2::NA_value()};
    }
    Direction_2 minimum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          minimum = Direction_2::NA_value();
          break;
        }
        continue;
      }
      minimum = _storage[i] < minimum ? _storage[i] : minimum;
    }

    return {minimum};
  }
  std::vector<Direction_2> max(bool na_rm) const {
    if (size() == 0) {
      return {Direction_2::NA_value()};
    }
    Direction_2 maximum = _storage[0];

    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          maximum = Direction_2::NA_value();
          break;
        }
        continue;
      }
      maximum = _storage[i] > maximum ? _storage[i] : maximum;
    }

    return {maximum};
  }
  std::vector<Direction_2> cummin() const {
    std::vector<Direction_2> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Direction_2 cum_min = _storage[0];
    result.push_back(cum_min);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_min = Direction_2::NA_value();
      }
      if (!is_na) {
        cum_min = _storage[i] < cum_min ? _storage[i] : cum_min;
      }
      result.push_back(cum_min);
    }

    return {result};
  }
  std::vector<Direction_2> cummax() const {
    std::vector<Direction_2> result;
    result.reserve(size());

    if (size() == 0) {
      return {result};
    }

    Direction_2 cum_max = _storage[0];
    result.push_back(cum_max);
    bool is_na = false;

    for (size_t i = 1; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_max = Direction_2::NA_value();
      }
      if (!is_na) {
        cum_max = _storage[i] < cum_max ? _storage[i] : cum_max;
      }
      result.push_back(cum_max);
    }

    return {result};
  }
  cpp11::writable::logicals between(const direction2& d1, const direction2& d2) const {
    size_t final_size = std::max(std::max(size(), d1.size()), d2.size());
    cpp11::writable::logicals result;
    result.reserve(final_size);
    for (size_t i = 0; i < final_size; ++i) {
      if (!_storage[i % size()] || !d1[i % d1.size()] || !d2[i % d2.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) _storage[i % size()].counterclockwise_in_between(d1[i % d1.size()], d2[i % d2.size()]));
    }
    return result;
  }
};

typedef cpp11::external_pointer<direction2> direction2_p;

class direction3 : public geometry_vector<Direction_3, 3, Direction_2> {
public:
  using geometry_vector::geometry_vector;
  ~direction3() = default;

  Primitive geometry_type() const { return DIRECTION; }

  cpp11::writable::strings def_names() const {
    return {"dx", "dy", "dz"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].dx();
    case 1: return _storage[i].dy();
    case 2: return _storage[i].dz();
    }
    return _storage[i].dx();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].dx().exact()),
      CGAL::to_double(_storage[i].dy().exact()),
      CGAL::to_double(_storage[i].dz().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  std::vector<Direction_3> operator-() const {
    std::vector<Direction_3> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = Direction_3::NA_value();
        continue;
      }
      result.push_back(-_storage[i]);
    }
    return result;
  }
};

typedef cpp11::external_pointer<direction3> direction3_p;
