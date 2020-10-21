#' Vector of triangles
#'
#' Triangles are sets of three vertices in either 2 or three dimensions. In
#' three dimensions the order of the vertices determines the orientation of the
#' triangle with vertices being in counter-clockwise order from the facing side.
#' If the 3 vertices are colinear the triangle is considered to be
#' [degenerate][is_degenerate]
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A vector of triangles or an object to convert to it
#'
#' @return An `euclid_triangle` vector
#'
#' @section Constructors:
#' **2 and 3 dimensional triangles**
#' - Providing three points will construct triangles in the order the points are
#'   given.
#'
#' @export
#'
#' @examples
#' # Construction
#' p <- point(sample(6), sample(6))
#' triangle(p[1:2], p[3:4], p[5:6])
#'
#' # 3D triangles can be converted to planes
#' p <- point(sample(6), sample(6), sample(6))
#' t <- triangle(p[1:2], p[3:4], p[5:6])
#' as_plane(t)
#'
triangle <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_triangle_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]

  if (length(points) == 3) {
    new_triangle_from_3_points(points[[1]], points[[2]], points[[3]])
  } else {
    rlang::abort("Don't know how to construct triangles from the given input")
  }
}
#' @rdname triangle
#' @export
is_triangle <- function(x) inherits(x, "euclid_triangle")


# Conversion --------------------------------------------------------------

#' @rdname triangle
#' @export
as_triangle <- function(x) {
  UseMethod("as_triangle")
}
#' @export
as_triangle.default <- function(x) {
  rlang::abort("Don't know how to convert the input to triangles")
}
#' @export
as_triangle.euclid_triangle <- function(x) x

#' @export
as_plane.euclid_triangle <- function(x) {
  plane(x)
}

# Internal Constructors ---------------------------------------------------

new_triangle_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_triangle_2_empty())
  } else {
    new_geometry_vector(create_triangle_3_empty())
  }
}
new_triangle_from_3_points <- function(p, q, r) {
  if (dim(p) == 2) {
    new_geometry_vector(create_triangle_2_3points(get_ptr(p), get_ptr(q), get_ptr(r)))
  } else {
    new_geometry_vector(create_triangle_3_3points(get_ptr(p), get_ptr(q), get_ptr(r)))
  }
}
