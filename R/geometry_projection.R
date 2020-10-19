#' Project geometries to lines and planes
#'
#' These functions handles projections and mappings of geometries to lines and
#' planes. For projections, the geometry type will stay the same, while for
#' mapping the geometries will be converted to their 2D variants. Not all
#' geometries can be projected and mapped. Specifically, iso rectangles and iso
#' cuboids cannot do either, only 3 dimensional geometries can be projected to a
#' plane, and only 3 dimensional geometries with a 2 dimensional counterpart can
#' be mapped to a plane. Circles and spheres are special in the sense that no
#' ellipse and ellipsoid primitives exist. Because of this, projections will
#' retain the radius and circularity of the primitives despite this not being
#' geometrically sound. Projecting a 3D circle to a line will keep the
#' orientation of the circle, while projecting it to a plane will adopt the
#' orientation of the plane. Mapping a 2D circle to a plane will map the center
#' and keep the radius. Mapping a sphere to a plane will produce a circle.
#'
#' @param x A vector of geometries to project or map
#' @param target A vector of lines (for projection) or planes (for projection or
#' mapping)
#'
#' @return A vector of geometries. For projection the class match that of `x`,
#' for mapping it is the 2 dimensional counterpart to `x`
#'
#' @rdname geometry_projection
#' @name geometry_projection
#'
NULL

#' @rdname geometry_projection
#' @export
project <- function(x, target) {
  if (!is_geometry(x)) {
    rlang::abort("Only geometries can be projected")
  }
  if (dim(x) != dim(target)) {
    rlang::abort("geometry must have the same dimensionality as the projection target")
  }
  if (is_line(target)) {
    restore_euclid_vector(geometry_project_to_line(get_ptr(x), get_ptr(target)), x)
  } else if (is_plane(target)) {
    restore_euclid_vector(geometry_project_to_plane(get_ptr(x), get_ptr(target)), x)
  } else {
    rlang::abort("projection target must either be lines or planes")
  }
}

#' @rdname geometry_projection
#' @export
map_to <- function(x, target) {
  if (!is_geometry(x)) {
    rlang::abort("Only geometries can be mapped to planes")
  }
  if (dim(x) != 3) {
    rlang::abort("Only 3 dimensional geometries can be mapped to planes")
  }
  if (!is_plane(target)) {
    rlang::abort("Only planes can be used as mapping target")
  }
  result <- geometry_map_to_plane(get_ptr(x), get_ptr(target))
  switch(geometry_type(x),
    circle = new_circle2(result),
    direction = new_direction2(result),
    line = new_line2(result),
    point_w = new_point_w2(result),
    point = new_point2(result),
    ray = new_ray2(result),
    segment = new_segment2(result),
    sphere = new_circle2(result),
    triangle = new_triangle2(result),
    vector = new_vector2(result),
    rlang::abort("Unknown geometry")
  )
}
