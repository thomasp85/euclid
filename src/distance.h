#pragma once

#include "cgal_types.h"

#include <CGAL/squared_distance_2.h>
#include <CGAL/squared_distance_3.h>

#include <cpp11/matrix.hpp>

template<typename T, typename U>
inline std::vector<Exact_number> squared_distance_impl(const std::vector<T>& geo1, const std::vector<U>& geo2) {
  size_t output_size = std::max(geo1.size(), geo2.size());
  std::vector<Exact_number> res;
  res.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (!geo1[i % geo1.size()] || !geo2[i % geo2.size()]) {
      res.push_back(Exact_number::NA_value());
      continue;
    }
    Exact_number dist2 = CGAL::squared_distance(geo1[i % geo1.size()], geo2[i % geo2.size()]);
    res.push_back(dist2);
  }
  return res;
}

inline std::vector<Exact_number> unknown_squared_distance_impl(size_t size) {
  std::vector<Exact_number> res;
  res.reserve(size);
  for (R_xlen_t i = 0; i < size; ++i) {
    res.push_back(Exact_number::NA_value());
  }
  return res;
}

template<typename T, typename U>
inline cpp11::writable::doubles_matrix distance_matrix_impl(const std::vector<T>& geo1, const std::vector<U>& geo2) {
  cpp11::writable::doubles_matrix res(geo1.size(), geo2.size());
  for (size_t i = 0; i < geo1.size(); ++i) {
    for (size_t j = 0; j < geo2.size(); ++j) {
      if (!geo1[i] || !geo2[j]) {
        res(i, j) = R_NaReal;
        continue;
      }
      res(i, j) = CGAL::sqrt(CGAL::to_double(CGAL::squared_distance(geo1[i], geo2[j])));
    }
  }
  return res;
}

inline cpp11::writable::doubles_matrix unknown_distance_matrix_impl(size_t nrow, size_t ncol) {
  cpp11::writable::doubles_matrix res(nrow, ncol);
  for (size_t i = 0; i < nrow; ++i) {
    for (size_t j = 0; j < ncol; ++j) {
      res(i, j) = R_NaReal;
    }
  }
  return res;
}
