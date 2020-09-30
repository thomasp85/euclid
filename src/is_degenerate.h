#pragma once

#include "cgal_types.h"

template<typename T>
inline bool is_degenerate_impl(const T& geo) {
  return false;
}
template<>
inline bool is_degenerate_impl<Circle_2>(const Circle_2& geo) {
  return geo.is_degenerate();
}
template<>
inline bool is_degenerate_impl<Circle_3>(const Circle_3& geo) {
  return geo.squared_radius() == 0.0;
}
template<>
inline bool is_degenerate_impl<Ray_2>(const Ray_2& geo) {
  return geo.is_degenerate();
}
template<>
inline bool is_degenerate_impl<Ray_3>(const Ray_3& geo) {
  return geo.is_degenerate();
}
