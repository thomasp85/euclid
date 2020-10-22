#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"

class plane : public geometry_vector<Plane, 3> {
public:
  using geometry_vector::geometry_vector;
  ~plane() = default;

  geometry_vector_base* new_from_vector(std::vector<Plane> vec) const {
    plane* copy = new plane();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Plane> vec) const {
    cpp11::stop("Planes cannot be mapped to 2D");
  }

  Primitive geometry_type() const { return PLANE; }

  cpp11::writable::strings def_names() const {
    return {"a", "b", "c", "d"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].a();
    case 1: return _storage[i].b();
    case 2: return _storage[i].c();
    case 3: return _storage[i].d();
    }
    return _storage[i].a();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].a().exact()),
      CGAL::to_double(_storage[i].b().exact()),
      CGAL::to_double(_storage[i].c().exact()),
      CGAL::to_double(_storage[i].d().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return intersection_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return intersection_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case SPHERE: return intersection_impl(_storage, get_vector_of_geo<Sphere>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<plane> plane_p;
