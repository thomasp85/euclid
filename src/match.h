#pragma once

#include <cpp11/integers.hpp>
#include <map>
#include "cgal_types.h"

// Only assumes working ==
template<typename T>
inline cpp11::writable::integers match_impl(const std::vector<T>& x, const std::vector<T>& lookup) {
  cpp11::writable::integers results;
  results.reserve(x.size());

  int NA_ind = -1;

  for (size_t i = 0; i < lookup.size(); ++i) {
    if (NA_ind == -1 && !lookup[i]) {
      NA_ind = i;
    }
  }
  auto start = lookup.begin();
  for (auto iter = x.begin(); iter != x.end(); ++iter) {
    if (!iter->is_valid()) {
      if (NA_ind == -1) {
        results.push_back(R_NaInt);
      } else {
        results.push_back(NA_ind + 1);
      }
      continue;
    }
    auto match = std::find(lookup.begin(), lookup.end(), *iter);
    if (match == lookup.end()) {
      results.push_back(R_NaInt);
    } else {
      results.push_back((match - start) + 1);
    }
  }

  return results;
}

// Efficient version for types with < comparison
template<typename T>
inline cpp11::writable::integers match_map_impl(const std::vector<T>& x, const std::vector<T>& lookup) {
  std::map<T, size_t> lookup_map;

  int NA_ind = -1;
  for (size_t i = 0; i < lookup.size(); ++i) {
    if (!lookup[i]) {
      if (NA_ind == -1) NA_ind = i;
      continue;
    }
    if (lookup_map.find(lookup[i]) == lookup_map.end()) {
      lookup_map[lookup[i]] = i;
    }
  }
  cpp11::writable::integers results;
  results.reserve(x.size());
  for (auto iter = x.begin(); iter != x.end(); ++iter) {
    if (!iter->is_valid()) {
      if (NA_ind == -1) {
        results.push_back(R_NaInt);
      } else {
        results.push_back(NA_ind + 1);
      }
      continue;
    }
    auto match = lookup_map.find(*iter);
    if (match == lookup_map.end()) {
      results.push_back(R_NaInt);
    } else {
      results.push_back(match->second + 1);
    }
  }

  return results;
}

template<>
inline cpp11::writable::integers match_impl(const std::vector<Point_2>& x, const std::vector<Point_2>& lookup) {
  return match_map_impl(x, lookup);
}

template<>
inline cpp11::writable::integers match_impl(const std::vector<Point_3>& x, const std::vector<Point_3>& lookup) {
  return match_map_impl(x, lookup);
}

template<>
inline cpp11::writable::integers match_impl(const std::vector<Exact_number>& x, const std::vector<Exact_number>& lookup) {
  return match_map_impl(x, lookup);
}

template<>
inline cpp11::writable::integers match_impl(const std::vector<Direction_2>& x, const std::vector<Direction_2>& lookup) {
  return match_map_impl(x, lookup);
}
