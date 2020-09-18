#' @export
#'
circle <- function(x, y, z = NULL, r) {
  if (is.null(z)) {
    inputs <- validate_numeric_input(x = x, y = y, r = r)
    new_circle2(inputs$x, inputs$y, inputs$r)
  }
}
#' @export
new_circle2 <- function(x, y, r) {
  vec_assert(x, double())
  vec_assert(y, double())
  vec_assert(r, double())
  assert_lengths_are_equal(x, y, r)
  new_geometry_vector(create_circle_2(x, y, r), class = "euclid_circle2")
}
