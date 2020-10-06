#' Vector of iso rectangles
#'
#' @export
iso_rect <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_iso_rect_empty())
  }

  bboxes <- inputs[vapply(inputs, is_bbox, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  points <- inputs[vapply(inputs, is_point, logical(1))]

  if (length(bboxes) == 1) {
    new_iso_rect_from_bbox(bboxes[[1]])
  } else if (length(points) == 2) {
    new_iso_rect_from_2_points(points[[1]], points[[2]])
  } else if (length(numbers) == 4) {
    new_iso_rect_from_4_numbers(numbers[[1]], numbers[[2]], numbers[[3]], numbers[[4]])
  } else {
    rlang::abort("Don't know how to construct iso rectangles from the given input")
  }
}
#' @rdname iso_rect
#' @export
is_iso_rect <- function(x) inherits(x, "euclid_iso_rect")


# Conversion --------------------------------------------------------------

#' @rdname iso_rect
#' @export
as_iso_rect <- function(x) {
  UseMethod("as_iso_rect")
}
#' @export
as_iso_rect.default <- function(x) {
  rlang::abort("Don't know how to convert the input to iso rects")
}
#' @export
as_iso_rect.euclid_iso_rect <- function(x) x

# Internal Constructors ---------------------------------------------------

new_iso_rect <- function(x) {
  new_geometry_vector(x, class = "euclid_iso_rect")
}
new_iso_rect_empty <- function() {
  new_iso_rect(create_iso_rect_empty())
}
new_iso_rect_from_bbox <- function(bbox) {
  new_iso_rect(create_iso_rect_bbox(get_ptr(bbox)))
}
new_iso_rect_from_2_points <- function(p, q) {
  new_iso_rect(create_iso_rect_pq(get_ptr(p), get_ptr(q)))
}
new_iso_rect_from_4_numbers <- function(l, r, b, t) {
  new_iso_rect(create_iso_rect_lrbt(get_ptr(l), get_ptr(r), get_ptr(b), get_ptr(t)))
}
