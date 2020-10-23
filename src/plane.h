#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"
#include "distance.h"

class plane : public geometry_vector<Plane, 3> {
public:
  using geometry_vector::geometry_vector;
  ~plane() = default;

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

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return do_intersect_impl(_storage, get_vector_of_geo<Iso_cuboid>(other));
    case LINE: return do_intersect_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return do_intersect_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return do_intersect_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return do_intersect_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case SPHERE: return do_intersect_impl(_storage, get_vector_of_geo<Sphere>(other));
    case TETRAHEDRON: return do_intersect_impl(_storage, get_vector_of_geo<Tetrahedron>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return squared_distance_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return squared_distance_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return squared_distance_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return squared_distance_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return squared_distance_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_squared_distance_impl(std::max(size(), other.size()));
    }
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return distance_matrix_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return distance_matrix_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return distance_matrix_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return distance_matrix_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return distance_matrix_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_distance_matrix_impl(size(), other.size());
    }
  }
};

typedef cpp11::external_pointer<plane> plane_p;
