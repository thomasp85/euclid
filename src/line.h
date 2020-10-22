#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"

class line2 : public geometry_vector<Line_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~line2() = default;

  geometry_vector_base* new_from_vector(std::vector<Line_2> vec) const {
    line2* copy = new line2();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Line_2> vec) const {
    return new_from_vector(vec);
  }

  Primitive geometry_type() const { return LINE; }

  cpp11::writable::strings def_names() const {
    return {"a", "b", "c"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].a();
    case 1: return _storage[i].b();
    case 2: return _storage[i].c();
    }
    return _storage[i].a();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].a().exact()),
      CGAL::to_double(_storage[i].b().exact()),
      CGAL::to_double(_storage[i].c().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return intersection_impl(get_vector_of_geo<Iso_rectangle>(other), _storage);
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<line2> line2_p;

class line3 : public geometry_vector<Line_3, 3, Line_2> {
public:
  using geometry_vector::geometry_vector;
  ~line3() = default;

  geometry_vector_base* new_from_vector(std::vector<Line_3> vec) const {
    line3* copy = new line3();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Line_2> vec) const {
    line2* copy = new line2(vec);
    return copy;
  }

  Primitive geometry_type() const { return LINE; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "dx", "dy", "dz"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].point(0.0).x();
    case 1: return _storage[i].point(0.0).y();
    case 2: return _storage[i].point(0.0).z();
    case 3: return _storage[i].direction().dx();
    case 4: return _storage[i].direction().dy();
    case 5: return _storage[i].direction().dz();
    }
    return _storage[i].point(0.0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].point(0.0).x().exact()),
      CGAL::to_double(_storage[i].point(0.0).y().exact()),
      CGAL::to_double(_storage[i].point(0.0).z().exact()),
      CGAL::to_double(_storage[i].direction().dx().exact()),
      CGAL::to_double(_storage[i].direction().dy().exact()),
      CGAL::to_double(_storage[i].direction().dz().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return intersection_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<line3> line3_p;
