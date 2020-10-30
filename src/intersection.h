#pragma once

#include "cgal_types.h"
#include "geometry_vector.h"
#include "is_degenerate.h"
#include <cpp11/list.hpp>
#include <CGAL/intersections.h>
#include <boost/variant/apply_visitor.hpp>

struct Intersection_visitor {
  typedef geometry_vector_base_p result_type;

  result_type operator()(const Kernel::Circle_3& i) const {
    return create_scalar_geometry(Circle_3(i));
  }
  result_type operator()(const Kernel::Iso_rectangle_2& i) const {
    return create_scalar_geometry(Iso_rectangle(i));
  }
  result_type operator()(const Kernel::Iso_cuboid_3& i) const {
    return create_scalar_geometry(Iso_cuboid(i));
  }
  result_type operator()(const Kernel::Line_2& i) const {
    return create_scalar_geometry(Line_2(i));
  }
  result_type operator()(const Kernel::Line_3& i) const {
    return create_scalar_geometry(Line_3(i));
  }
  result_type operator()(const Kernel::Plane_3& i) const {
    return create_scalar_geometry(Plane(i));
  }
  result_type operator()(const Kernel::Point_2& i) const {
    return create_scalar_geometry(Point_2(i));
  }
  result_type operator()(const Kernel::Point_3& i) const {
    return create_scalar_geometry(Point_3(i));
  }
  result_type operator()(const std::vector<Kernel::Point_2>& i) const {
    return create_scalar_geometry(Point_2::NA_value());
  }
  result_type operator()(const std::vector<Kernel::Point_3>& i) const {
    return create_scalar_geometry(Point_3::NA_value());
  }
  result_type operator()(const Kernel::Ray_2& i) const {
    return create_scalar_geometry(Ray_2(i));
  }
  result_type operator()(const Kernel::Ray_3& i) const {
    return create_scalar_geometry(Ray_3(i));
  }
  result_type operator()(const Kernel::Segment_2& i) const {
    return create_scalar_geometry(Segment_2(i));
  }
  result_type operator()(const Kernel::Segment_3& i) const {
    return create_scalar_geometry(Segment_3(i));
  }
  result_type operator()(const Kernel::Sphere_3& i) const {
    return create_scalar_geometry(Sphere(i));
  }
  result_type operator()(const Kernel::Triangle_2& i) const {
    return create_scalar_geometry(Triangle_2(i));
  }
  result_type operator()(const Kernel::Triangle_3& i) const {
    return create_scalar_geometry(Triangle_3(i));
  }
};

template<typename T, typename U>
inline cpp11::writable::list intersection_impl(const std::vector<T>& geo1, const std::vector<U>& geo2) {
  if (geo1.size() == 0 || geo2.size() == 0) {
    return {};
  }
  size_t output_size = std::max(geo1.size(), geo2.size());
  cpp11::writable::list result;
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (invalid_geo(geo1[i % geo1.size()]) || invalid_geo(geo2[i % geo2.size()])) {
      result.push_back(R_NilValue);
      continue;
    }
    auto overlap = CGAL::intersection(geo1[i % geo1.size()], geo2[i % geo2.size()]);
    if (overlap) {
      result.push_back(boost::apply_visitor(Intersection_visitor(), *overlap));
    } else {
      result.push_back(R_NilValue);
    }
  }
  return result;
}

template<typename T, typename U>
inline cpp11::writable::logicals do_intersect_impl(const std::vector<T>& geo1, const std::vector<U>& geo2) {
  if (geo1.size() == 0 || geo2.size() == 0) {
    return {};
  }
  size_t output_size = std::max(geo1.size(), geo2.size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (invalid_geo(geo1[i % geo1.size()]) || invalid_geo(geo2[i % geo2.size()])) {
      result.push_back(NA_LOGICAL);
      continue;
    }
    bool overlap = CGAL::do_intersect(geo1[i % geo1.size()], geo2[i % geo2.size()]);
    result.push_back((Rboolean) overlap);
  }
  return result;
}

inline cpp11::writable::logicals unknown_intersect_impl(size_t size) {
  cpp11::writable::logicals res(size);
  for (size_t i = 0; i < size; ++i) {
    res[i] = NA_LOGICAL;
  }
  return res;
}
