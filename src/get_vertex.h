#include "cgal_types.h"
#include <cpp11/protect.hpp>

template<typename T, typename U>
inline U get_vertex_impl(const T& geometry, int which) {
  return geometry.vertex(which);
}

template<>
inline Point_2 get_vertex_impl(const Circle_2& geometry, int which) {
  return geometry.center();
}

template<>
inline Point_3 get_vertex_impl(const Circle_3& geometry, int which) {
  return geometry.center();
}

template<>
inline Point_2 get_vertex_impl(const Direction_2& geometry, int which) {
  return Point_2::NA_value();
}

template<>
inline Point_3 get_vertex_impl(const Direction_3& geometry, int which) {
  return Point_3::NA_value();
}

template<>
inline Point_2 get_vertex_impl(const Line_2& geometry, int which) {
  return geometry.point(0);
}

template<>
inline Point_3 get_vertex_impl(const Line_3& geometry, int which) {
  return geometry.point(0);
}

template<>
inline Point_3 get_vertex_impl(const Plane& geometry, int which) {
  return geometry.point();
}

template<>
inline Point_2 get_vertex_impl(const Point_2& geometry, int which) {
  return geometry;
}

template<>
inline Point_3 get_vertex_impl(const Point_3& geometry, int which) {
  return geometry;
}

template<>
inline Point_2 get_vertex_impl(const Weighted_point_2& geometry, int which) {
  return geometry.point();
}

template<>
inline Point_3 get_vertex_impl(const Weighted_point_3& geometry, int which) {
  return geometry.point();
}

template<>
inline Point_2 get_vertex_impl(const Ray_2& geometry, int which) {
  return geometry.source();
}

template<>
inline Point_3 get_vertex_impl(const Ray_3& geometry, int which) {
  return geometry.source();
}

template<>
inline Point_3 get_vertex_impl(const Sphere& geometry, int which) {
  return geometry.center();
}

template<>
inline Point_2 get_vertex_impl(const Vector_2& geometry, int which) {
  return Point_2::NA_value();
}

template<>
inline Point_3 get_vertex_impl(const Vector_3& geometry, int which) {
  return Point_3::NA_value();
}
