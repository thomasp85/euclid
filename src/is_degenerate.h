#pragma once

#include "cgal_types.h"

template<typename T>
inline bool is_degenerate_impl(const T& geo) {
  return geo.is_degenerate();
}
template<>
inline bool is_degenerate_impl<Circle_3>(const Circle_3& geo) {
  return geo.squared_radius() == 0.0;
}
template<>
inline bool is_degenerate_impl<Point_2>(const Point_2& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Point_3>(const Point_3& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Vector_2>(const Vector_2& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Vector_3>(const Vector_3& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Direction_2>(const Direction_2& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Direction_3>(const Direction_3& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Weighted_point_2>(const Weighted_point_2& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Weighted_point_3>(const Weighted_point_3& geo) {
  return false;
}
