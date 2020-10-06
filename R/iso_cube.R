#' Vector of iso cubes
#'
#' @export
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

new_iso_cube <- function(x) {
  new_geometry_vector(x, class = "euclid_iso_cube")
}
new_iso_cube_empty <- function() {
  new_iso_cube(create_iso_cube_empty())
}
new_iso_cube_from_bbox <- function(bbox) {
  new_iso_cube(create_iso_cube_bbox(get_ptr(bbox)))
}
new_iso_cube_from_2_points <- function(p, q) {
  new_iso_cube(create_iso_cube_pq(get_ptr(p), get_ptr(q)))
}
new_iso_cube_from_6_numbers <- function(l, r, b, t, f, c) {
  new_iso_cube(create_iso_cube_lrbtfc(get_ptr(l), get_ptr(r), get_ptr(b), get_ptr(t), get_ptr(f), get_ptr(c)))
}
