#' Vector of iso cubes
#'
#' Iso cubes are axis-aligned cuboids, i.e. a cube with faces parallel to the x,
#' y, and z plane. Iso cuboids are the 3 dimensional version of
#' [iso rectangles][iso_rect] and shares the feature that it can be constructed
#' from bounding boxes (in 3D). An Iso cube is [degenerate][is_degenerate] all
#' its vertices are coplanar.
#'
#' @param ... Various input. See the Constructor section.
#' @param x A vector of iso cubes or an object to convert to it
#'
#' @return An `euclid_iso_cube` vector
#'
#' @section Constructors:
#' **3 dimensional iso cubes**
#' - Providing a bbox will create iso cubes matching the bbox
#' - Providing two points will create iso cubes with the points as diagonal
#'   opposite vertices
#' - Providing 6 numeric will construct iso cubes with the given extent,
#'   with the numerics being interpreted in the following order: minimum x,
#'   minimum y, minimum z, maximum x, maximum y, and maximum z
#'
#' @export
#'
#' @examples
#' # Construction
#' p <- point(sample(10, 2), sample(10, 2), sample(10, 2))
#' iso_cube(p[1], p[2])
#'
#' iso_cube(4, 10, 7, 16, -4, 0)
#'
#' s <- sphere(point(5, 9, 2), 13)
#' iso_cube(bbox(s))
#'
iso_cube <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_iso_cube_empty())
  }

  bboxes <- inputs[vapply(inputs, is_bbox, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  points <- inputs[vapply(inputs, is_point, logical(1))]

  if (length(bboxes) == 1) {
    new_iso_cube_from_bbox(bboxes[[1]])
  } else if (length(points) == 2) {
    new_iso_cube_from_2_points(points[[1]], points[[2]])
  } else if (length(numbers) == 6) {
    new_iso_cube_from_6_numbers(numbers[[1]], numbers[[2]], numbers[[3]], numbers[[4]], numbers[[5]], numbers[[6]])
  } else {
    rlang::abort("Don't know how to construct iso cubes from the given input")
  }
}
#' @rdname iso_cube
#' @export
is_iso_cube <- function(x) inherits(x, "euclid_iso_cube")


# Conversion --------------------------------------------------------------

#' @rdname iso_cube
#' @export
as_iso_cube <- function(x) {
  UseMethod("as_iso_cube")
}
#' @export
as_iso_cube.default <- function(x) {
  rlang::abort("Don't know how to convert the input to iso cubes")
}
#' @export
as_iso_cube.euclid_iso_cube <- function(x) x

# Internal Constructors ---------------------------------------------------

new_iso_cube_empty <- function() {
  new_geometry_vector(create_iso_cube_empty())
}
new_iso_cube_from_bbox <- function(bbox) {
  new_geometry_vector(create_iso_cube_bbox(get_ptr(bbox)))
}
new_iso_cube_from_2_points <- function(p, q) {
  new_geometry_vector(create_iso_cube_pq(get_ptr(p), get_ptr(q)))
}
new_iso_cube_from_6_numbers <- function(x0, y0, z0, x1, y1, z1) {
  new_geometry_vector(create_iso_cube_minmax(get_ptr(x0), get_ptr(y0), get_ptr(z0), get_ptr(x1), get_ptr(y1), get_ptr(z1)))
}
