#pragma once

#include <cpp11/strings.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"
#include "distance.h"

#include <vector>

class point_w2 : public geometry_vector<Weighted_point_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~point_w2() = default;

  Primitive geometry_type() const { return WPOINT; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "w"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].x();
    case 1: return _storage[i].y();
    case 2: return _storage[i].weight();
    }
    return _storage[i].x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].x().exact()),
      CGAL::to_double(_storage[i].y().exact()),
      CGAL::to_double(_storage[i].weight().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_intersect_impl(std::max(size(), other.size()));
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_squared_distance_impl(std::max(size(), other.size()));
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_distance_matrix_impl(size(), other.size());
  }
};

typedef cpp11::external_pointer<point_w2> point_w2_p;

class point_w3 : public geometry_vector<Weighted_point_3, 3, Weighted_point_2> {
public:
  using geometry_vector::geometry_vector;
  ~point_w3() = default;

  Primitive geometry_type() const { return WPOINT; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "w"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].x();
    case 1: return _storage[i].y();
    case 2: return _storage[i].z();
    case 3: return _storage[i].weight();
    }
    return _storage[i].x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].x().exact()),
      CGAL::to_double(_storage[i].y().exact()),
      CGAL::to_double(_storage[i].z().exact()),
      CGAL::to_double(_storage[i].weight().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_intersect_impl(std::max(size(), other.size()));
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_squared_distance_impl(std::max(size(), other.size()));
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_distance_matrix_impl(size(), other.size());
  }
};

typedef cpp11::external_pointer<point_w3> point_w3_p;
