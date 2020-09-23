#' Access coordinate dimensions in geometries
#'
#' This method gives access to the coordinates of geometries (if defined) as
#' [exact_numeric] vectors.
#'
#' @param x A geometry vector
#' @param dimension The dimension to retrieve coordinate value from, either as
#' a character (`"x"`, `"y"`, or `"z"`), or an integer.
#'
#' @return An exact_numeric vector
#'
#' @export
#'
#' @examples
#' points <- point(1:10, 10:1)
#' coord(points, "x")
#'
coord <- function(x, dimension) {
  UseMethod("coord")
}
#' @export
coord.default <- function(x, dimension) {
  rlang::abort("Coordinate retrieval is not defined for this geometry")
}
#' @export
coord.euclid_point <- function(x, dimension) {
  dimension <- validate_coordinate_dimension(dimension, dim(x))
  if (dim(x) == 2) {
    new_exact_numeric(point_2_coord(get_ptr(x), dimension))
  } else {
    new_exact_numeric(point_3_coord(get_ptr(x), dimension))
  }
}

validate_coordinate_dimension <- function(x, dim) {
  x <- x[1]
  if (is.character(x)) {
    x <- match(x, c("x", "y", "z"))
    if (is.na(x)) {
      rlang::abort("Uknown coordinate dimension")
    }
  }
  if (x > dim) {
    rlang::abort("Coordinate dimension exceeds dimensionality of geometry")
  }
  if (x < 1) {
    rlang::abort("Coordinate dimensino must be positive")
  }
  as.integer(x - 1L)
}
