#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "circle.h"
#include "intersection.h"

class sphere : public geometry_vector<Sphere, 3, Circle_2> {
public:
  using geometry_vector::geometry_vector;
  ~sphere() = default;

  Primitive geometry_type() const { return SPHERE; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "r2"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].center().x();
    case 1: return _storage[i].center().y();
    case 2: return _storage[i].center().z();
    case 3: return _storage[i].squared_radius();
    }
    return _storage[i].center().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].center().x().exact()),
      CGAL::to_double(_storage[i].center().y().exact()),
      CGAL::to_double(_storage[i].center().z().exact()),
      CGAL::to_double(_storage[i].squared_radius().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case PLANE: return intersection_impl(get_vector_of_geo<Plane>(other), _storage);
    case POINT: return intersection_impl(get_vector_of_geo<Point_3>(other), _storage);
    case SPHERE: return intersection_impl(_storage, get_vector_of_geo<Sphere>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<sphere> sphere_p;
