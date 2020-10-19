#' Check if a geometry is degenerate
#'
#' Geometries can be ill-defined for several reasons, e.g. circles with a radius
#' of zero, segments that start and end at the same location, etc. See details
#' for a list of conditions that are considered degenerate.
#'
#' @param x A geometry vector
#'
#' @details
#' The following conditions are considered to produce degenerate geometries:
#' - A circle having a radius of zero
#' - An iso-rectangle with zero width or zero height
#' - An iso-cuboid with zero width, zero height, or zero depth
#' - A 2D line with the coefficients being zero
#' - A 3D line that is degenerated to a point
#' - A plane with the coefficients being zero
#' - A ray with the source and the second defining point being equal
#' - A segment with the source and target being equal
#' - A sphere with a radius of zero
#' - A tetrahedron with all vertices being co-planar
#' - A triangle with collinear vertices
#'
#' @return A logical vector
#'
#' @export
is_degenerate <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`is_degenerate` is only defined for geometries")
  }
  geometry_is_degenerate(get_ptr(x))
}

#' Query location of points relative to geometry
#'
#' Point predicates is at the heart of many geometry algorithms. These set of
#' functions allows you to query the location of points relative to a given
#' geometry vector. The functions are provided as both regular and binary
#' operators.
#'
#' @param x A geometry vector
#' @param y A points vector
#'
#' @details
#' There are two types of location predicates:
#'
#' ### Containment (inside and outside)
#' Queries whether a point is inside or outside the boundary defined by the
#' geometry. In 2D it is defined for geometries that have an area, In 3D it is
#' defined for geometries that has a volume. This means that containment is
#' defined for 2D circles but not 3D circles.
#'
#' ### Orientation (positive and negative)
#' Queries whether a point lies on the positive or negative side of a geometry.
#' It is defined for geometries that splits the dimensional space in two. This
#' means that it is not defined for rays, segments, etc with a finite length.
#'
#' For both types of predicates there are also the condition that the point lies
#' *on* the geometry. This predicate is equivalent for both types of predicates
#' and is defined for all geometries that has a location. This means that e.g.
#' directions and vectors do not define this predicate.
#'
#' @return A logical vector
#'
#' @rdname location_predicates
#' @name location_predicates
NULL

#' @rdname location_predicates
#' @export
has_on <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on%` <- function(y, x) has_on(x, y)

#' @rdname location_predicates
#' @export
has_inside <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_inside(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_inside%` <- function(y, x) has_inside(x, y)

#' @rdname location_predicates
#' @export
has_outside <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_outside(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_outside%` <- function(y, x) has_outside(x, y)

#' @rdname location_predicates
#' @export
has_on_positive_side <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on_positive(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on_positive_side%` <- function(y, x) has_on_positive_side(x, y)

#' @rdname location_predicates
#' @export
has_on_negative_side <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on_negative(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on_negative_side%` <- function(y, x) has_on_negative_side(x, y)
