#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"

class tetrahedron : public geometry_vector<Tetrahedron, 3> {
public:
  using geometry_vector::geometry_vector;
  ~tetrahedron() = default;

  Primitive geometry_type() const { return TETRAHEDRON; }

  size_t cardinality(size_t i) const { return 4; }
  size_t long_length() const { return size() * 4; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    case 2: return _storage[i].vertex(element).z();
    }
    return _storage[i].vertex(element).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact()),
      CGAL::to_double(_storage[i].vertex(j).z().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return do_intersect_impl(get_vector_of_geo<Iso_cuboid>(other), _storage);
    case LINE: return do_intersect_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return do_intersect_impl(get_vector_of_geo<Plane>(other), _storage);
    case POINT: return do_intersect_impl(get_vector_of_geo<Point_3>(other), _storage);
    case RAY: return do_intersect_impl(get_vector_of_geo<Ray_3>(other), _storage);
    case SEGMENT: return do_intersect_impl(get_vector_of_geo<Segment_3>(other), _storage);
    case SPHERE: return do_intersect_impl(get_vector_of_geo<Sphere>(other), _storage);
    case TETRAHEDRON: return do_intersect_impl(_storage, get_vector_of_geo<Tetrahedron>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }
};

typedef cpp11::external_pointer<tetrahedron> tetrahedron_p;
