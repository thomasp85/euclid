#pragma once

#include "internal/cgal_types.h"
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <vector>

namespace euclid {

enum Primitive {
  VIRTUAL,
  CIRCLE,
  DIRECTION,
  ISOCUBE,
  ISORECT,
  LINE,
  PLANE,
  POINT,
  RAY,
  SEGMENT,
  SPHERE,
  TETRAHEDRON,
  TRIANGLE,
  VECTOR,
  WPOINT
};

const std::vector<Bbox_2> get_bbox_2_vec(SEXP val) {
  typedef std::vector<Bbox_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_bbox_2_vec");
  return fn(val);
}
const std::vector<Bbox_3> get_bbox_3_vec(SEXP val) {
  typedef std::vector<Bbox_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_bbox_3_vec");
  return fn(val);
}
const std::vector<Circle_2> get_circle_2_vec(SEXP val) {
  typedef std::vector<Circle_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_circle_2_vec");
  return fn(val);
}
const std::vector<Circle_3> get_circle_3_vec(SEXP val) {
  typedef std::vector<Circle_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_circle_3_vec");
  return fn(val);
}
const std::vector<Direction_2> get_direction_2_vec(SEXP val) {
  typedef std::vector<Direction_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_direction_2_vec");
  return fn(val);
}
const std::vector<Direction_3> get_direction_3_vec(SEXP val) {
  typedef std::vector<Direction_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_direction_3_vec");
  return fn(val);
}
const std::vector<Iso_cuboid> get_iso_cube_vec(SEXP val) {
  typedef std::vector<Iso_cuboid> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_iso_cube_vec");
  return fn(val);
}
const std::vector<Iso_rectangle> get_iso_rect_vec(SEXP val) {
  typedef std::vector<Iso_rectangle> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_iso_rect_vec");
  return fn(val);
}
const std::vector<Line_2> get_line_2_vec(SEXP val) {
  typedef std::vector<Line_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_line_2_vec");
  return fn(val);
}
const std::vector<Line_3> get_line_3_vec(SEXP val) {
  typedef std::vector<Line_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_line_3_vec");
  return fn(val);
}
const std::vector<Plane> get_plane_vec(SEXP val) {
  typedef std::vector<Plane> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_plane_vec");
  return fn(val);
}
const std::vector<Point_2> get_point_2_vec(SEXP val) {
  typedef std::vector<Point_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_point_2_vec");
  return fn(val);
}
const std::vector<Point_3> get_point_3_vec(SEXP val) {
  typedef std::vector<Point_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_point_3_vec");
  return fn(val);
}
const std::vector<Ray_2> get_ray_2_vec(SEXP val) {
  typedef std::vector<Ray_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_ray_2_vec");
  return fn(val);
}
const std::vector<Ray_3> get_ray_3_vec(SEXP val) {
  typedef std::vector<Ray_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_ray_3_vec");
  return fn(val);
}
const std::vector<Segment_2> get_segment_2_vec(SEXP val) {
  typedef std::vector<Segment_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_segment_2_vec");
  return fn(val);
}
const std::vector<Segment_3> get_segment_3_vec(SEXP val) {
  typedef std::vector<Segment_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_segment_3_vec");
  return fn(val);
}
const std::vector<Sphere> get_sphere_vec(SEXP val) {
  typedef std::vector<Sphere> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_sphere_vec");
  return fn(val);
}
const std::vector<Tetrahedron> get_tetrahedron_vec(SEXP val) {
  typedef std::vector<Tetrahedron> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_tetrahedron_vec");
  return fn(val);
}
const std::vector<Triangle_2> get_triangle_2_vec(SEXP val) {
  typedef std::vector<Triangle_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_triangle_2_vec");
  return fn(val);
}
const std::vector<Triangle_3> get_triangle_3_vec(SEXP val) {
  typedef std::vector<Triangle_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_triangle_3_vec");
  return fn(val);
}
const std::vector<Vector_2> get_vector_2_vec(SEXP val) {
  typedef std::vector<Vector_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_vector_2_vec");
  return fn(val);
}
const std::vector<Vector_3> get_vector_3_vec(SEXP val) {
  typedef std::vector<Vector_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_vector_3_vec");
  return fn(val);
}
const std::vector<Weighted_point_2> get_weighted_point_2_vec(SEXP val) {
  typedef std::vector<Weighted_point_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_weighted_point_2_vec");
  return fn(val);
}
const std::vector<Weighted_point_3> get_weighted_point_3_vec(SEXP val) {
  typedef std::vector<Weighted_point_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_weighted_point_3_vec");
  return fn(val);
}
const std::vector<Aff_transformation_2> get_transform_2_vec(SEXP val) {
  typedef std::vector<Aff_transformation_2> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_transform_2_vec");
  return fn(val);
}
const std::vector<Aff_transformation_3> get_transform_3_vec(SEXP val) {
  typedef std::vector<Aff_transformation_3> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_transform_3_vec");
  return fn(val);
}
const std::vector<Exact_number> get_exact_numeric_vec(SEXP val) {
  typedef std::vector<Exact_number> fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_exact_numeric_vec");
  return fn(val);
}

SEXP create_bbox_2_vec(std::vector<Bbox_2>& val) {
  typedef SEXP fn_ptr(std::vector<Bbox_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_bbox_2_vec");
  return fn(val);
}
SEXP create_bbox_3_vec(std::vector<Bbox_3>& val) {
  typedef SEXP fn_ptr(std::vector<Bbox_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_bbox_3_vec");
  return fn(val);
}
SEXP create_circle_2_vec(std::vector<Circle_2>& val) {
  typedef SEXP fn_ptr(std::vector<Circle_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_circle_2_vec");
  return fn(val);
}
SEXP create_circle_3_vec(std::vector<Circle_3>& val) {
  typedef SEXP fn_ptr(std::vector<Circle_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_circle_3_vec");
  return fn(val);
}
SEXP create_direction_2_vec(std::vector<Direction_2>& val) {
  typedef SEXP fn_ptr(std::vector<Direction_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_direction_2_vec");
  return fn(val);
}
SEXP create_direction_3_vec(std::vector<Direction_3>& val) {
  typedef SEXP fn_ptr(std::vector<Direction_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_direction_3_vec");
  return fn(val);
}
SEXP create_iso_cube_vec(std::vector<Iso_cuboid>& val) {
  typedef SEXP fn_ptr(std::vector<Iso_cuboid>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_iso_cube_vec");
  return fn(val);
}
SEXP create_iso_rect_vec(std::vector<Iso_rectangle>& val) {
  typedef SEXP fn_ptr(std::vector<Iso_rectangle>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_iso_rect_vec");
  return fn(val);
}
SEXP create_line_2_vec(std::vector<Line_2>& val) {
  typedef SEXP fn_ptr(std::vector<Line_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_line_2_vec");
  return fn(val);
}
SEXP create_line_3_vec(std::vector<Line_3>& val) {
  typedef SEXP fn_ptr(std::vector<Line_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_line_3_vec");
  return fn(val);
}
SEXP create_plane_vec(std::vector<Plane>& val) {
  typedef SEXP fn_ptr(std::vector<Plane>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_plane_vec");
  return fn(val);
}
SEXP create_point_2_vec(std::vector<Point_2>& val) {
  typedef SEXP fn_ptr(std::vector<Point_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_point_2_vec");
  return fn(val);
}
SEXP create_point_3_vec(std::vector<Point_3>& val) {
  typedef SEXP fn_ptr(std::vector<Bbox_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_bbox_2_vec");
  return fn(val);
}
SEXP create_ray_2_vec(std::vector<Ray_2>& val) {
  typedef SEXP fn_ptr(std::vector<Ray_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_ray_2_vec");
  return fn(val);
}
SEXP create_ray_3_vec(std::vector<Ray_3>& val) {
  typedef SEXP fn_ptr(std::vector<Ray_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_ray_3_vec");
  return fn(val);
}
SEXP create_segment_2_vec(std::vector<Segment_2>& val) {
  typedef SEXP fn_ptr(std::vector<Segment_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_segment_2_vec");
  return fn(val);
}
SEXP create_segment_3_vec(std::vector<Segment_3>& val) {
  typedef SEXP fn_ptr(std::vector<Segment_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_segment_3_vec");
  return fn(val);
}
SEXP create_sphere_vec(std::vector<Sphere>& val) {
  typedef SEXP fn_ptr(std::vector<Sphere>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_sphere_vec");
  return fn(val);
}
SEXP create_tetrahedron_vec(std::vector<Tetrahedron>& val) {
  typedef SEXP fn_ptr(std::vector<Tetrahedron>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_tetrahedron_vec");
  return fn(val);
}
SEXP create_triangle_2_vec(std::vector<Triangle_2>& val) {
  typedef SEXP fn_ptr(std::vector<Triangle_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_triangle_2_vec");
  return fn(val);
}
SEXP create_triangle_3_vec(std::vector<Triangle_3>& val) {
  typedef SEXP fn_ptr(std::vector<Triangle_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_triangle_3_vec");
  return fn(val);
}
SEXP create_vector_2_vec(std::vector<Vector_2>& val) {
  typedef SEXP fn_ptr(std::vector<Vector_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_vector_2_vec");
  return fn(val);
}
SEXP create_vector_3_vec(std::vector<Vector_3>& val) {
  typedef SEXP fn_ptr(std::vector<Vector_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_vector_3_vec");
  return fn(val);
}
SEXP create_weighted_point_2_vec(std::vector<Weighted_point_2>& val) {
  typedef SEXP fn_ptr(std::vector<Weighted_point_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_weighted_point_2_vec");
  return fn(val);
}
SEXP create_weighted_point_3_vec(std::vector<Weighted_point_3>& val) {
  typedef SEXP fn_ptr(std::vector<Weighted_point_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_weighted_point_3_vec");
  return fn(val);
}
SEXP create_transform_2_vec(std::vector<Aff_transformation_2>& val) {
  typedef SEXP fn_ptr(std::vector<Aff_transformation_2>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_transform_2_vec");
  return fn(val);
}
SEXP create_transform_3_vec(std::vector<Aff_transformation_3>& val) {
  typedef SEXP fn_ptr(std::vector<Aff_transformation_3>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_transform_3_vec");
  return fn(val);
}
SEXP create_exact_numeric_vec(std::vector<Exact_number>& val) {
  typedef SEXP fn_ptr(std::vector<Exact_number>&);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "create_exact_numeric_vec");
  return fn(val);
}

Primitive get_geometry_type(SEXP val) {
  typedef Primitive fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_geometry_type");
  return fn(val);
}
size_t get_geometry_dimensions(SEXP val) {
  typedef size_t fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_geometry_dimensions");
  return fn(val);
}
size_t get_bbox_dimensions(SEXP val) {
  typedef size_t fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_bbox_dimensions");
  return fn(val);
}
size_t get_transform_dimensions(SEXP val) {
  typedef size_t fn_ptr(SEXP);
  static fn_ptr *fn = (fn_ptr*) R_GetCCallable("euclid", "get_transform_dimensions");
  return fn(val);
}
};
