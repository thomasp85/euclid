#' Approximate geometry measures
#'
#' These functions provide approximate measures of length, area, and volume of
#' geometries where relevant. The reason for approximation is that some measures
#' require square root operations or multiplication by π, both operations where
#' exactness is necessarily lost. Not all geometries have meaningful measures,
#' e.g. a direction is dimensionless, a line is without area, and a circle has
#' no volume. Some geometries are infinite in some measures, e.g. a plane has an
#' infinite area. The return value will reflect this.
#'
#' @param x A geometry vector
#'
#' @return A numeric vector
#'
#' @rdname geometry_measures
#' @name geometry_measures
NULL

#' @rdname geometry_measures
#' @export
approx_length <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`approx_length()` is only defined for geometries")
  }
  geometry_approx_length(get_ptr(x))
}
#' @rdname geometry_measures
#' @export
approx_area <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`approx_area()` is only defined for geometries")
  }
  geometry_approx_area(get_ptr(x))
}
#' @rdname geometry_measures
#' @export
approx_volume <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`approx_volume()` is only defined for geometries")
  }
  geometry_approx_volume(get_ptr(x))
}
