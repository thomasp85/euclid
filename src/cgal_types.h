#pragma once

#include "cran.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Circle_3.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Iso_cuboid_3.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Line_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Point_2.h>
#include <CGAL/Point_3.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Sphere_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Weighted_point_2.h>
#include <CGAL/Weighted_point_3.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/Aff_transformation_3.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>

template<class T>
class with_NA : public T {
public:
  using T::T;

  with_NA() : T(), _valid(true) {}
  with_NA(const T& copy) : T(copy), _valid(true) {}

  operator bool() const { return _valid; }
  bool is_valid() const { return _valid; }

  T base() const { return {*this}; }

  static with_NA<T> NA_value() {
    with_NA<T> invalid;
    invalid._valid = false;
    return invalid;
  }

private:
  bool _valid = true;
};

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef with_NA<Kernel::FT> Exact_number;
typedef with_NA<Kernel::Circle_2> Circle_2;
typedef with_NA<Kernel::Circle_3> Circle_3;
typedef with_NA<Kernel::Direction_2> Direction_2;
typedef with_NA<Kernel::Direction_3> Direction_3;
typedef with_NA<Kernel::Iso_cuboid_3> Iso_cuboid;
typedef with_NA<Kernel::Iso_rectangle_2> Iso_rectangle;
typedef with_NA<Kernel::Line_2> Line_2;
typedef with_NA<Kernel::Line_3> Line_3;
typedef with_NA<Kernel::Plane_3> Plane;
typedef with_NA<Kernel::Point_2> Point_2;
typedef with_NA<Kernel::Point_3> Point_3;
typedef with_NA<Kernel::Ray_2> Ray_2;
typedef with_NA<Kernel::Ray_3> Ray_3;
typedef with_NA<Kernel::Segment_2> Segment_2;
typedef with_NA<Kernel::Segment_3> Segment_3;
typedef with_NA<Kernel::Sphere_3> Sphere;
typedef with_NA<Kernel::Tetrahedron_3> Tetrahedron;
typedef with_NA<Kernel::Triangle_2> Triangle_2;
typedef with_NA<Kernel::Triangle_3> Triangle_3;
typedef with_NA<Kernel::Vector_2> Vector_2;
typedef with_NA<Kernel::Vector_3> Vector_3;
typedef with_NA<Kernel::Weighted_point_2> Weighted_point_2;
typedef with_NA<Kernel::Weighted_point_3> Weighted_point_3;
typedef with_NA<Kernel::Aff_transformation_2> Aff_transformation_2;
typedef with_NA<Kernel::Aff_transformation_3> Aff_transformation_3;
typedef with_NA<CGAL::Bbox_2> Bbox_2;
typedef with_NA<CGAL::Bbox_3> Bbox_3;
