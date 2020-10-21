#pragma once

#include "cgal_types.h"
#include <cpp11/R.hpp>

template<typename T>
inline int constant_in_impl(const T& geometry, int coord) {
  return NA_LOGICAL;
}

template<>
inline int constant_in_impl(const Plane& geometry, int coord) {
  Vector_3 normal = geometry.orthogonal_vector();
  switch (coord) {
  case 0: return normal.y() == 0.0 && normal.z() == 0.0;
  case 1: return normal.x() == 0.0 && normal.z() == 0.0;
  }
  return normal.x() == 0.0 && normal.y() == 0.0;
}

template<>
inline int constant_in_impl(const Circle_2& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  switch (coord) {
  case 0: return false;
  case 1: return false;
  }
  return true;
}

template<>
inline int constant_in_impl(const Circle_3& geometry, int coord) {
  if (geometry.squared_radius() == 0.0) {
    return NA_LOGICAL;
  }
  return constant_in_impl<Plane>(geometry.supporting_plane(), coord);
}

template<>
inline int constant_in_impl(const Direction_2& geometry, int coord) {
  switch (coord) {
  case 0: return geometry.dx() == 0.0;
  case 1: return geometry.dy() == 0.0;
  }
  return true;
}

template<>
inline int constant_in_impl(const Direction_3& geometry, int coord) {
  switch (coord) {
  case 0: return geometry.dx() == 0.0;
  case 1: return geometry.dy() == 0.0;
  }
  return geometry.dz() == 0.0;
}

template<>
inline int constant_in_impl(const Iso_cuboid& geometry, int coord) {
  return true;
}

template<>
inline int constant_in_impl(const Iso_rectangle& geometry, int coord) {
  return true;
}

template<>
inline int constant_in_impl(const Line_2& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  switch (coord) {
  case 0: return geometry.is_vertical();
  case 1: return geometry.is_horizontal();
  }
  return true;
}

template<>
inline int constant_in_impl(const Line_3& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  return constant_in_impl<Direction_3>(geometry.direction(), coord);
}

template<>
inline int constant_in_impl(const Point_2& geometry, int coord) {
  return true;
}

template<>
inline int constant_in_impl(const Point_3& geometry, int coord) {
  return true;
}

template<>
inline int constant_in_impl(const Ray_2& geometry, int coord) {
  return constant_in_impl<Direction_2>(geometry.direction(), coord);
}

template<>
inline int constant_in_impl(const Ray_3& geometry, int coord) {
  return constant_in_impl<Direction_3>(geometry.direction(), coord);
}

template<>
inline int constant_in_impl(const Segment_2& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  switch (coord) {
  case 0: return geometry.source().x() == geometry.target().x();
  case 1: return geometry.source().y() == geometry.target().y();
  }
  return true;
}

template<>
inline int constant_in_impl(const Segment_3& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  switch (coord) {
  case 0: return geometry.source().x() == geometry.target().x();
  case 1: return geometry.source().y() == geometry.target().y();
  }
  return geometry.source().z() == geometry.target().z();
}

template<>
inline int constant_in_impl(const Sphere& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  return false;
}

template<>
inline int constant_in_impl(const Tetrahedron& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  return false;
}

template<>
inline int constant_in_impl(const Triangle_2& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  switch (coord) {
  case 0: return false;
  case 1: return false;
  }
  return true;
}

template<>
inline int constant_in_impl(const Triangle_3& geometry, int coord) {
  if (geometry.is_degenerate()) {
    return NA_LOGICAL;
  }
  return constant_in_impl<Plane>(geometry.supporting_plane(), coord);
}

template<>
inline int constant_in_impl(const Vector_2& geometry, int coord) {
  return constant_in_impl<Direction_2>(geometry.direction(), coord);
}

template<>
inline int constant_in_impl(const Vector_3& geometry, int coord) {
  return constant_in_impl<Direction_3>(geometry.direction(), coord);
}

template<>
inline int constant_in_impl(const Weighted_point_2& geometry, int coord) {
  return true;
}

template<>
inline int constant_in_impl(const Weighted_point_3& geometry, int coord) {
  return true;
}
