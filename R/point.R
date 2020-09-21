#' Vector of points
#'
#' Points are the fundamental unit in geometry, from which other geometric
#' primitives can be constructed.
#'
#' @param x,y,z [exact_numeric] vectors or standard R numerics. If `z` is `NULL`
#' a 2-dimensional point is constructed, if not a 3 dimensional point is
#' constructed.
#'
#' @return a `euclid_point2` or `euclid_point3` vector
#'
#' @export
#'
#' @examples
#' num1 <- exact_numeric(runif(5))
#' num2 <- exact_numeric(runif(5))
#' num3 <- exact_numeric(runif(5))
#'
#' # 2 dimensions
#' point(num1, num2)
#'
#' # 3 dimensions
#' point(num1, num2, num3)
#'
#' # Standard R vectors are automatically converted to exact_numeric vectors
#' point(runif(5), runif(5))
#'
point <- function(x, y, z = NULL) {
  if (is.null(z)) {
    inputs <- validate_numeric_input(x = x, y = y)
    new_point2(inputs$x, inputs$y)
  } else {
    inputs <- validate_numeric_input(x = x, y = y, z = z)
    new_point3(inputs$x, inputs$y, inputs$z)
  }
}
#' @rdname point
#' @export
is_point <- function(x) inherits(x, "euclid_point")

new_point2 <- function(x, y) {
  if (!is_exact_numeric(x)) {
    rlang::abort("`x` must be an exact numeric")
  }
  if (!is_exact_numeric(y)) {
    rlang::abort("`y` must be an exact numeric")
  }
  assert_lengths_are_equal(x, y)
  new_geometry_vector(create_point_2(get_ptr(x), get_ptr(y)), class = c("euclid_point2", "euclid_point"))
}
new_point3 <- function(x, y, z) {
  if (!is_exact_numeric(x)) {
    rlang::abort("`x` must be an exact numeric")
  }
  if (!is_exact_numeric(y)) {
    rlang::abort("`y` must be an exact numeric")
  }
  if (!is_exact_numeric(z)) {
    rlang::abort("`z` must be an exact numeric")
  }
  assert_lengths_are_equal(x, y, z)
  new_geometry_vector(create_point_3(get_ptr(x), get_ptr(y), get_ptr(z)), class = c("euclid_point3", "euclid_point"))
}
