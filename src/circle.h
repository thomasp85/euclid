#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/logicals.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "intersection.h"

#include <vector>

class circle2 : public geometry_vector<Circle_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~circle2() = default;

  geometry_vector_base* new_from_vector(std::vector<Circle_2> vec) const {
    circle2* copy = new circle2();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Circle_2> vec) const {
    return new_from_vector(vec);
  }

  Primitive geometry_type() const { return CIRCLE; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "r2"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].center().x();
    case 1: return _storage[i].center().y();
    case 2: return _storage[i].squared_radius();
    }
    return _storage[i].center().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    Circle_2 circ = _storage[i];
    Point_2 center = circ.center();
    return {
      CGAL::to_double(center.x().exact()),
      CGAL::to_double(center.y().exact()),
      CGAL::to_double(circ.squared_radius().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }
};

typedef cpp11::external_pointer<circle2> circle2_p;

class circle3 : public geometry_vector<Circle_3, 3, Circle_2> {
public:
  using geometry_vector::geometry_vector;
  ~circle3() = default;

  geometry_vector_base* new_from_vector(std::vector<Circle_3> vec) const {
    circle3* copy = new circle3();

    copy->_storage.swap(vec);

    return copy;
  }

  geometry_vector_base* new_2D_from_vector(std::vector<Circle_2> vec) const {
    circle2* copy = new circle2(vec);
    return copy;
  }

  Primitive geometry_type() const { return CIRCLE; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "r2", "dx", "dy", "dz"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].center().x();
    case 1: return _storage[i].center().y();
    case 2: return _storage[i].center().z();
    case 3: return _storage[i].squared_radius();
    case 4: return _storage[i].supporting_plane().orthogonal_direction().dx();
    case 5: return _storage[i].supporting_plane().orthogonal_direction().dy();
    case 6: return _storage[i].supporting_plane().orthogonal_direction().dz();
    }
    return _storage[i].center().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].center().x().exact()),
      CGAL::to_double(_storage[i].center().y().exact()),
      CGAL::to_double(_storage[i].center().z().exact()),
      CGAL::to_double(_storage[i].squared_radius().exact()),
      CGAL::to_double(_storage[i].supporting_plane().orthogonal_direction().dx().exact()),
      CGAL::to_double(_storage[i].supporting_plane().orthogonal_direction().dy().exact()),
      CGAL::to_double(_storage[i].supporting_plane().orthogonal_direction().dz().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    cpp11::stop("Don't know how to calculate the intersection of these geometries");
  }
};

typedef cpp11::external_pointer<circle3> circle3_p;
