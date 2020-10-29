#include "api.h"

#include <vector>
#include <cpp11/list.hpp>
#include <R_ext/Rdynload.h>

#include "cgal_types.h"
#include "geometry_vector.h"
#include "bbox.h"
#include "transform.h"
#include "exact_numeric.h"

const std::vector<Bbox_2> get_bbox_2_vec(SEXP val) {
  bbox_vector_base_p pointer = get_ext_pointer<bbox_vector_base>(val);
  return get_vector_of_bbox<Bbox_2>(*pointer);
}
const std::vector<Bbox_3> get_bbox_3_vec(SEXP val) {
  bbox_vector_base_p pointer = get_ext_pointer<bbox_vector_base>(val);
  return get_vector_of_bbox<Bbox_3>(*pointer);
}
const std::vector<Circle_2> get_circle_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Circle_2>(*pointer);
}
const std::vector<Circle_3> get_circle_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Circle_3>(*pointer);
}
const std::vector<Direction_2> get_direction_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Direction_2>(*pointer);
}
const std::vector<Direction_3> get_direction_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Direction_3>(*pointer);
}
const std::vector<Iso_cuboid> get_iso_cube_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Iso_cuboid>(*pointer);
}
const std::vector<Iso_rectangle> get_iso_rect_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Iso_rectangle>(*pointer);
}
const std::vector<Line_2> get_line_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Line_2>(*pointer);
}
const std::vector<Line_3> get_line_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Line_3>(*pointer);
}
const std::vector<Plane> get_plane_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Plane>(*pointer);
}
const std::vector<Point_2> get_point_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Point_2>(*pointer);
}
const std::vector<Point_3> get_point_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Point_3>(*pointer);
}
const std::vector<Ray_2> get_ray_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Ray_2>(*pointer);
}
const std::vector<Ray_3> get_ray_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Ray_3>(*pointer);
}
const std::vector<Segment_2> get_segment_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Segment_2>(*pointer);
}
const std::vector<Segment_3> get_segment_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Segment_3>(*pointer);
}
const std::vector<Sphere> get_sphere_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Sphere>(*pointer);
}
const std::vector<Tetrahedron> get_tetrahedron_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Tetrahedron>(*pointer);
}
const std::vector<Triangle_2> get_triangle_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Triangle_2>(*pointer);
}
const std::vector<Triangle_3> get_triangle_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Triangle_3>(*pointer);
}
const std::vector<Vector_2> get_vector_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Vector_2>(*pointer);
}
const std::vector<Vector_3> get_vector_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Vector_3>(*pointer);
}
const std::vector<Weighted_point_2> get_weighted_point_2_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Weighted_point_2>(*pointer);
}
const std::vector<Weighted_point_3> get_weighted_point_3_vec(SEXP val) {
  geometry_vector_base_p pointer = get_ext_pointer<geometry_vector_base>(val);
  return get_vector_of_geo<Weighted_point_3>(*pointer);
}
const std::vector<Aff_transformation_2> get_transform_2_vec(SEXP val) {
  transform_vector_base_p pointer = get_ext_pointer<transform_vector_base>(val);
  return get_vector_of_trans<Aff_transformation_2>(*pointer);
}
const std::vector<Aff_transformation_3> get_transform_3_vec(SEXP val) {
  transform_vector_base_p pointer = get_ext_pointer<transform_vector_base>(val);
  return get_vector_of_trans<Aff_transformation_3>(*pointer);
}
const std::vector<Exact_number> get_exact_numeric_vec(SEXP val) {
  exact_numeric_p pointer = get_ext_pointer<exact_numeric>(val);
  return pointer->get_storage();
}

SEXP create_bbox_2_vec(std::vector<Bbox_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_bbox_vector(val));
  result.attr("class") = {"euclid_bbox2", "euclid_bbox"};
  return result;
}
SEXP create_bbox_3_vec(std::vector<Bbox_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_bbox_vector(val));
  result.attr("class") = {"euclid_bbox3", "euclid_bbox"};
  return result;
}
SEXP create_circle_2_vec(std::vector<Circle_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_circle2", "euclid_circle", "euclid_geometry"};
  return result;
}
SEXP create_circle_3_vec(std::vector<Circle_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_circle3", "euclid_circle", "euclid_geometry"};
  return result;
}
SEXP create_direction_2_vec(std::vector<Direction_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_direction2", "euclid_direction", "euclid_geometry"};
  return result;
}
SEXP create_direction_3_vec(std::vector<Direction_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_direction3", "euclid_direction", "euclid_geometry"};
  return result;
}
SEXP create_iso_cube_vec(std::vector<Iso_cuboid>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_iso_cube", "euclid_geometry"};
  return result;
}
SEXP create_iso_rect_vec(std::vector<Iso_rectangle>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_iso_rect", "euclid_geometry"};
  return result;
}
SEXP create_line_2_vec(std::vector<Line_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_line2", "euclid_line", "euclid_geometry"};
  return result;
}
SEXP create_line_3_vec(std::vector<Line_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_line3", "euclid_line", "euclid_geometry"};
  return result;
}
SEXP create_plane_vec(std::vector<Plane>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_plane", "euclid_geometry"};
  return result;
}
SEXP create_point_2_vec(std::vector<Point_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_point2", "euclid_point", "euclid_geometry"};
  return result;
}
SEXP create_point_3_vec(std::vector<Point_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_point3", "euclid_point", "euclid_geometry"};
  return result;
}
SEXP create_ray_2_vec(std::vector<Ray_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_ray2", "euclid_ray", "euclid_geometry"};
  return result;
}
SEXP create_ray_3_vec(std::vector<Ray_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_ray3", "euclid_ray", "euclid_geometry"};
  return result;
}
SEXP create_segment_2_vec(std::vector<Segment_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_segment2", "euclid_segment", "euclid_geometry"};
  return result;
}
SEXP create_segment_3_vec(std::vector<Segment_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_segment3", "euclid_segment", "euclid_geometry"};
  return result;
}
SEXP create_sphere_vec(std::vector<Sphere>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_sphere", "euclid_geometry"};
  return result;
}
SEXP create_tetrahedron_vec(std::vector<Tetrahedron>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_tetrahedron", "euclid_geometry"};
  return result;
}
SEXP create_triangle_2_vec(std::vector<Triangle_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_triangle2", "euclid_triangle", "euclid_geometry"};
  return result;
}
SEXP create_triangle_3_vec(std::vector<Triangle_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_triangle3", "euclid_triangle", "euclid_geometry"};
  return result;
}
SEXP create_vector_2_vec(std::vector<Vector_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_vector2", "euclid_vector", "euclid_geometry"};
  return result;
}
SEXP create_vector_3_vec(std::vector<Vector_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_vector3", "euclid_vector", "euclid_geometry"};
  return result;
}
SEXP create_weighted_point_2_vec(std::vector<Weighted_point_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_point_w2", "euclid_point_w", "euclid_geometry"};
  return result;
}
SEXP create_weighted_point_3_vec(std::vector<Weighted_point_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_geometry_vector(val));
  result.attr("class") = {"euclid_point_w3", "euclid_point_w", "euclid_geometry"};
  return result;
}
SEXP create_transform_2_vec(std::vector<Aff_transformation_2>& val) {
  cpp11::writable::list result;
  result.push_back(create_transform_vector(val));
  result.attr("class") = {"euclid_affine_transformation2", "euclid_affine_transformation"};
  return result;
}
SEXP create_transform_3_vec(std::vector<Aff_transformation_3>& val) {
  cpp11::writable::list result;
  result.push_back(create_transform_vector(val));
  result.attr("class") = {"euclid_affine_transformation3", "euclid_affine_transformation"};
  return result;
}
SEXP create_exact_numeric_vec(std::vector<Exact_number>& val) {
  cpp11::writable::list result;
  exact_numeric* vec = new exact_numeric(val);
  result.push_back(exact_numeric_p(vec));
  result.attr("class") = "euclid_exact_numeric";
  return result;
}

Primitive get_geometry_type(SEXP val) {
  geometry_vector_base_p  pointer = get_ext_pointer<geometry_vector_base>(val);
  return pointer->geometry_type();
}
size_t get_geometry_dimensions(SEXP val) {
  geometry_vector_base_p  pointer = get_ext_pointer<geometry_vector_base>(val);
  return pointer->dimensions();
}
size_t get_bbox_dimensions(SEXP val) {
  bbox_vector_base_p  pointer = get_ext_pointer<bbox_vector_base>(val);
  return pointer->dimensions();
}
size_t get_transform_dimensions(SEXP val) {
  transform_vector_base_p pointer = get_ext_pointer<transform_vector_base>(val);
  return pointer->dimensions();
}

[[cpp11::init]]
void export_euclid_api(DllInfo* dll) {
  R_RegisterCCallable("euclid", "get_bbox_2_vec", (DL_FUNC)get_bbox_2_vec);
  R_RegisterCCallable("euclid", "get_bbox_3_vec", (DL_FUNC)get_bbox_3_vec);
  R_RegisterCCallable("euclid", "get_circle_2_vec", (DL_FUNC)get_circle_2_vec);
  R_RegisterCCallable("euclid", "get_circle_3_vec", (DL_FUNC)get_circle_3_vec);
  R_RegisterCCallable("euclid", "get_direction_2_vec", (DL_FUNC)get_direction_2_vec);
  R_RegisterCCallable("euclid", "get_direction_3_vec", (DL_FUNC)get_direction_3_vec);
  R_RegisterCCallable("euclid", "get_iso_cube_vec", (DL_FUNC)get_iso_cube_vec);
  R_RegisterCCallable("euclid", "get_iso_rect_vec", (DL_FUNC)get_iso_rect_vec);
  R_RegisterCCallable("euclid", "get_line_2_vec", (DL_FUNC)get_line_2_vec);
  R_RegisterCCallable("euclid", "get_line_3_vec", (DL_FUNC)get_line_3_vec);
  R_RegisterCCallable("euclid", "get_plane_vec", (DL_FUNC)get_plane_vec);
  R_RegisterCCallable("euclid", "get_point_2_vec", (DL_FUNC)get_point_2_vec);
  R_RegisterCCallable("euclid", "get_point_3_vec", (DL_FUNC)get_point_3_vec);
  R_RegisterCCallable("euclid", "get_ray_2_vec", (DL_FUNC)get_ray_2_vec);
  R_RegisterCCallable("euclid", "get_ray_3_vec", (DL_FUNC)get_ray_3_vec);
  R_RegisterCCallable("euclid", "get_segment_2_vec", (DL_FUNC)get_segment_2_vec);
  R_RegisterCCallable("euclid", "get_segment_3_vec", (DL_FUNC)get_segment_3_vec);
  R_RegisterCCallable("euclid", "get_sphere_vec", (DL_FUNC)get_sphere_vec);
  R_RegisterCCallable("euclid", "get_tetrahedron_vec", (DL_FUNC)get_tetrahedron_vec);
  R_RegisterCCallable("euclid", "get_triangle_2_vec", (DL_FUNC)get_triangle_2_vec);
  R_RegisterCCallable("euclid", "get_triangle_3_vec", (DL_FUNC)get_triangle_3_vec);
  R_RegisterCCallable("euclid", "get_vector_2_vec", (DL_FUNC)get_vector_2_vec);
  R_RegisterCCallable("euclid", "get_vector_3_vec", (DL_FUNC)get_vector_3_vec);
  R_RegisterCCallable("euclid", "get_weighted_point_2_vec", (DL_FUNC)get_weighted_point_2_vec);
  R_RegisterCCallable("euclid", "get_weighted_point_3_vec", (DL_FUNC)get_weighted_point_3_vec);
  R_RegisterCCallable("euclid", "get_transform_2_vec", (DL_FUNC)get_transform_2_vec);
  R_RegisterCCallable("euclid", "get_transform_3_vec", (DL_FUNC)get_transform_3_vec);
  R_RegisterCCallable("euclid", "get_exact_numeric_vec", (DL_FUNC)get_exact_numeric_vec);

  R_RegisterCCallable("euclid", "create_bbox_2_vec", (DL_FUNC)create_bbox_2_vec);
  R_RegisterCCallable("euclid", "create_bbox_3_vec", (DL_FUNC)create_bbox_3_vec);
  R_RegisterCCallable("euclid", "create_circle_2_vec", (DL_FUNC)create_circle_2_vec);
  R_RegisterCCallable("euclid", "create_circle_3_vec", (DL_FUNC)create_circle_3_vec);
  R_RegisterCCallable("euclid", "create_direction_2_vec", (DL_FUNC)create_direction_2_vec);
  R_RegisterCCallable("euclid", "create_direction_3_vec", (DL_FUNC)create_direction_3_vec);
  R_RegisterCCallable("euclid", "create_iso_cube_vec", (DL_FUNC)create_iso_cube_vec);
  R_RegisterCCallable("euclid", "create_iso_rect_vec", (DL_FUNC)create_iso_rect_vec);
  R_RegisterCCallable("euclid", "create_line_2_vec", (DL_FUNC)create_line_2_vec);
  R_RegisterCCallable("euclid", "create_line_3_vec", (DL_FUNC)create_line_3_vec);
  R_RegisterCCallable("euclid", "create_plane_vec", (DL_FUNC)create_plane_vec);
  R_RegisterCCallable("euclid", "create_point_2_vec", (DL_FUNC)create_point_2_vec);
  R_RegisterCCallable("euclid", "create_point_3_vec", (DL_FUNC)create_point_3_vec);
  R_RegisterCCallable("euclid", "create_ray_2_vec", (DL_FUNC)create_ray_2_vec);
  R_RegisterCCallable("euclid", "create_ray_3_vec", (DL_FUNC)create_ray_3_vec);
  R_RegisterCCallable("euclid", "create_segment_2_vec", (DL_FUNC)create_segment_2_vec);
  R_RegisterCCallable("euclid", "create_segment_3_vec", (DL_FUNC)create_segment_3_vec);
  R_RegisterCCallable("euclid", "create_sphere_vec", (DL_FUNC)create_sphere_vec);
  R_RegisterCCallable("euclid", "create_tetrahedron_vec", (DL_FUNC)create_tetrahedron_vec);
  R_RegisterCCallable("euclid", "create_triangle_2_vec", (DL_FUNC)create_triangle_2_vec);
  R_RegisterCCallable("euclid", "create_triangle_3_vec", (DL_FUNC)create_triangle_3_vec);
  R_RegisterCCallable("euclid", "create_vector_2_vec", (DL_FUNC)create_vector_2_vec);
  R_RegisterCCallable("euclid", "create_vector_3_vec", (DL_FUNC)create_vector_3_vec);
  R_RegisterCCallable("euclid", "create_weighted_point_2_vec", (DL_FUNC)create_weighted_point_2_vec);
  R_RegisterCCallable("euclid", "create_weighted_point_3_vec", (DL_FUNC)create_weighted_point_3_vec);
  R_RegisterCCallable("euclid", "create_transform_2_vec", (DL_FUNC)create_transform_2_vec);
  R_RegisterCCallable("euclid", "create_transform_3_vec", (DL_FUNC)create_transform_3_vec);
  R_RegisterCCallable("euclid", "create_exact_numeric_vec", (DL_FUNC)create_exact_numeric_vec);

  R_RegisterCCallable("euclid", "get_geometry_type", (DL_FUNC)get_geometry_type);
  R_RegisterCCallable("euclid", "get_geometry_dimensions", (DL_FUNC)get_geometry_dimensions);
  R_RegisterCCallable("euclid", "get_bbox_dimensions", (DL_FUNC)get_bbox_dimensions);
  R_RegisterCCallable("euclid", "get_transform_dimensions", (DL_FUNC)get_transform_dimensions);
}
