#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"

class iso_rect : public geometry_vector<Iso_rectangle, 2> {
public:
  using geometry_vector::geometry_vector;
  ~iso_rect() = default;

  geometry_vector_base* new_from_vector(std::vector<Iso_rectangle> vec) const {
    iso_rect* copy = new iso_rect();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Iso_rectangle> vec) const {
    return new_from_vector(vec);
  }

  Primitive geometry_type() const { return ISORECT; }

  size_t cardinality(size_t i) const { return 4; }
  size_t long_length() const { return size() * 4; }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    }
    return _storage[i].vertex(0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return intersection_impl(_storage, get_vector_of_geo<Iso_rectangle>(other));
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<iso_rect> iso_rect_p;
