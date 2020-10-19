#pragma once

#include "cgal_types.h"
#include <cpp11/protect.hpp>

// project_to_line -------------------------------------------------------------

template<typename T, typename Line>
inline T project_to_line_impl(const T& geo, const Line& line) {
  cpp11::stop("The geometry cannot be projected to a line");
}
template<>
inline Circle_2 project_to_line_impl(const Circle_2& geo, const Line_2& line) {
  return Circle_2(line.projection(geo.center()), geo.squared_radius());
}
template<>
inline Circle_3 project_to_line_impl(const Circle_3& geo, const Line_3& line) {
  return Circle_3(line.projection(geo.center()), geo.squared_radius(), geo.supporting_plane());
}
template<>
inline Direction_2 project_to_line_impl(const Direction_2& geo, const Line_2& line) {
  return Direction_2(line);
}
template<>
inline Direction_3 project_to_line_impl(const Direction_3& geo, const Line_3& line) {
  return Direction_3(line);
}
template<>
inline Line_2 project_to_line_impl(const Line_2& geo, const Line_2& line) {
  return line;
}
template<>
inline Line_3 project_to_line_impl(const Line_3& geo, const Line_3& line) {
  return line;
}
template<>
inline Point_2 project_to_line_impl(const Point_2& geo, const Line_2& line) {
  return line.projection(geo);
}
template<>
inline Point_3 project_to_line_impl(const Point_3& geo, const Line_3& line) {
  return line.projection(geo);
}
template<>
inline Ray_2 project_to_line_impl(const Ray_2& geo, const Line_2& line) {
  return Ray_2(line.projection(geo.source()), line);
}
template<>
inline Ray_3 project_to_line_impl(const Ray_3& geo, const Line_3& line) {
  return Ray_3(line.projection(geo.source()), line);
}
template<>
inline Segment_2 project_to_line_impl(const Segment_2& geo, const Line_2& line) {
  return Segment_2(line.projection(geo.source()), line.projection(geo.target()));
}
template<>
inline Segment_3 project_to_line_impl(const Segment_3& geo, const Line_3& line) {
  return Segment_3(line.projection(geo.source()), line.projection(geo.target()));
}
template<>
inline Sphere project_to_line_impl(const Sphere& geo, const Line_3& line) {
  return Sphere(line.projection(geo.center()), geo.squared_radius());
}
template<>
inline Tetrahedron project_to_line_impl(const Tetrahedron& geo, const Line_3& line) {
  return Tetrahedron(line.projection(geo[0]), line.projection(geo[1]), line.projection(geo[2]), line.projection(geo[3]));
}
template<>
inline Triangle_2 project_to_line_impl(const Triangle_2& geo, const Line_2& line) {
  return Triangle_2(line.projection(geo[0]), line.projection(geo[1]), line.projection(geo[2]));
}
template<>
inline Triangle_3 project_to_line_impl(const Triangle_3& geo, const Line_3& line) {
  return Triangle_3(line.projection(geo[0]), line.projection(geo[1]), line.projection(geo[2]));
}
template<>
inline Vector_2 project_to_line_impl(const Vector_2& geo, const Line_2& line) {
  Point_2 source = line.projection(Point_2(0, 0));
  Point_2 target = line.projection(Point_2(geo.x(), geo.y()));
  return target - source;
}
template<>
inline Vector_3 project_to_line_impl(const Vector_3& geo, const Line_3& line) {
  Point_3 source = line.projection(Point_3(0, 0, 0));
  Point_3 target = line.projection(Point_3(geo.x(), geo.y(), geo.z()));
  return target - source;
}
template<>
inline Weighted_point_2 project_to_line_impl(const Weighted_point_2& geo, const Line_2& line) {
  return Weighted_point_2(line.projection(geo.point()), geo.weight());
}
template<>
inline Weighted_point_3 project_to_line_impl(const Weighted_point_3& geo, const Line_3& line) {
  return Weighted_point_3(line.projection(geo.point()), geo.weight());
}


// project_to_plane ------------------------------------------------------------

template<typename T>
inline T project_to_plane_impl(const T& geo, const Plane& plane) {
  cpp11::stop("The geometry cannot be projected to a plane");
}
template<>
inline Circle_3 project_to_plane_impl(const Circle_3& geo, const Plane& plane) {
  return Circle_3(plane.projection(geo.center()), geo.squared_radius(), plane);
}
template<>
inline Line_3 project_to_plane_impl(const Line_3& geo, const Plane& plane) {
  return Line_3(plane.projection(geo.point(0)), plane.projection(geo.point(1)));
}
template<>
inline Plane project_to_plane_impl(const Plane& geo, const Plane& plane) {
  return plane;
}
template<>
inline Point_3 project_to_plane_impl(const Point_3& geo, const Plane& plane) {
  return plane.projection(geo);
}
template<>
inline Ray_3 project_to_plane_impl(const Ray_3& geo, const Plane& plane) {
  return Ray_3(plane.projection(geo.source()), plane.projection(geo.point(1)));
}
template<>
inline Segment_3 project_to_plane_impl(const Segment_3& geo, const Plane& plane) {
  return Segment_3(plane.projection(geo.source()), plane.projection(geo.target()));
}
template<>
inline Sphere project_to_plane_impl(const Sphere& geo, const Plane& plane) {
  return Sphere(plane.projection(geo.center()), geo.squared_radius());
}
template<>
inline Tetrahedron project_to_plane_impl(const Tetrahedron& geo, const Plane& plane) {
  return Tetrahedron(plane.projection(geo[0]), plane.projection(geo[1]), plane.projection(geo[2]), plane.projection(geo[3]));
}
template<>
inline Triangle_3 project_to_plane_impl(const Triangle_3& geo, const Plane& plane) {
  return Triangle_3(plane.projection(geo[0]), plane.projection(geo[1]), plane.projection(geo[2]));
}
template<>
inline Vector_3 project_to_plane_impl(const Vector_3& geo, const Plane& plane) {
  Point_3 source = plane.projection(Point_3(0, 0, 0));
  Point_3 target = plane.projection(Point_3(geo.x(), geo.y(), geo.z()));
  return target - source;
}
template<>
inline Direction_3 project_to_plane_impl(const Direction_3& geo, const Plane& plane) {
  return Direction_3(project_to_plane_impl(geo.vector(), plane));
}
template<>
inline Weighted_point_3 project_to_plane_impl(const Weighted_point_3& geo, const Plane& plane) {
  return Weighted_point_3(plane.projection(geo.point()), geo.weight());
}


// map_to_plane ----------------------------------------------------------------

template<typename T, typename U>
inline U map_to_plane_impl(const T& geo, const Plane& plane) {
  cpp11::stop("The geometry cannot be mapped to a plane");
}
template<>
inline Circle_2 map_to_plane_impl(const Circle_3& geo, const Plane& plane) {
  return Circle_2(plane.to_2d(geo.center()), geo.squared_radius());
}
template<>
inline Line_2 map_to_plane_impl(const Line_3& geo, const Plane& plane) {
  return Line_2(plane.to_2d(geo.point(0)), plane.to_2d(geo.point(1)));
}
template<>
inline Point_2 map_to_plane_impl(const Point_3& geo, const Plane& plane) {
  return plane.to_2d(geo);
}
template<>
inline Ray_2 map_to_plane_impl(const Ray_3& geo, const Plane& plane) {
  return Ray_2(plane.to_2d(geo.source()), plane.to_2d(geo.point(1)));
}
template<>
inline Segment_2 map_to_plane_impl(const Segment_3& geo, const Plane& plane) {
  return Segment_2(plane.to_2d(geo.source()), plane.to_2d(geo.target()));
}
template<>
inline Circle_2 map_to_plane_impl(const Sphere& geo, const Plane& plane) {
  return Circle_2(plane.to_2d(geo.center()), geo.squared_radius());
}
template<>
inline Triangle_2 map_to_plane_impl(const Triangle_3& geo, const Plane& plane) {
  return Triangle_2(plane.to_2d(geo[0]), plane.to_2d(geo[1]), plane.to_2d(geo[2]));
}
template<>
inline Vector_2 map_to_plane_impl(const Vector_3& geo, const Plane& plane) {
  Point_2 source = plane.to_2d(Point_3(0, 0, 0));
  Point_2 target = plane.to_2d(Point_3(geo.x(), geo.y(), geo.z()));
  return target - source;
}
template<>
inline Direction_2 map_to_plane_impl(const Direction_3& geo, const Plane& plane) {
  return Direction_2(map_to_plane_impl<Vector_3, Vector_2>(geo.vector(), plane));
}
template<>
inline Weighted_point_2 map_to_plane_impl(const Weighted_point_3& geo, const Plane& plane) {
  return Weighted_point_2(plane.to_2d(geo.point()), geo.weight());
}
