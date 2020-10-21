#pragma once

#include "cgal_types.h"
#include <CGAL/enum.h>

template<typename T, typename U>
inline U normal_impl(const T& geometry) {
  return U::NA_value();
}

template<>
inline Direction_3 normal_impl(const Circle_3& geometry) {
  return geometry.supporting_plane().orthogonal_direction();
}

template<>
inline Direction_2 normal_impl(const Direction_2& geometry) {
  return geometry.perpendicular(CGAL::POSITIVE);
}

template<>
inline Direction_2 normal_impl(const Line_2& geometry) {
  return geometry.direction().perpendicular(CGAL::POSITIVE);
}

template<>
inline Direction_3 normal_impl(const Plane& geometry) {
  return geometry.orthogonal_direction();
}

template<>
inline Direction_2 normal_impl(const Ray_2& geometry) {
  return geometry.direction().perpendicular(CGAL::POSITIVE);
}

template<>
inline Direction_2 normal_impl(const Segment_2& geometry) {
  return geometry.direction().perpendicular(CGAL::POSITIVE);
}

template<>
inline Direction_3 normal_impl(const Triangle_3& geometry) {
  return geometry.supporting_plane().orthogonal_direction();
}

template<>
inline Direction_2 normal_impl(const Vector_2& geometry) {
  return geometry.direction().perpendicular(CGAL::POSITIVE);
}
