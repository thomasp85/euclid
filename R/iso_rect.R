#' Vector of iso rectangles
#'
#' Iso rectangles are axis aligned rectangles mimicking bounding boxes but given
#' by exact numerics (bounding boxes are defined by floats because not all
#' geometries have exact defined extent). Internally they are stored as two
#' points giving the bottom-left and top-right corner of the rectangle. Iso
#' rectangles are considered [degenerate][is_degenerate] all its vertices are
#' colinear.
#'
#' @param ... Various input. See the Constructor section.
#' @param x A vector of iso rectangles or an object to convert to it
#'
#' @return An `euclid_iso_rect` vector
#'
#' @section Constructors:
#' **2 dimensional iso rectangles**
#' - Providing a bbox will create iso rectangles matching the bbox
#' - Providing two points will create iso rectangles with the points as diagonal
#'   opposite vertices
#' - Providing 4 numeric will construct iso rectangles with the given extent,
#'   with the numerics being interpreted in the following order: left, bottom,
#'   right, top
#'
#' @export
#'
#' @examples
#' # Construction
#' p <- point(sample(10, 2), sample(10, 2))
#' iso_rect(p[1], p[2])
#'
#' iso_rect(4, 10, 7, 16)
#'
#' circ <- circle(point(5, 9), 13)
#' iso_rect(bbox(circ))
#'
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

new_iso_rect_empty <- function() {
  new_geometry_vector(create_iso_rect_empty())
}
new_iso_rect_from_bbox <- function(bbox) {
  new_geometry_vector(create_iso_rect_bbox(get_ptr(bbox)))
}
new_iso_rect_from_2_points <- function(p, q) {
  new_geometry_vector(create_iso_rect_pq(get_ptr(p), get_ptr(q)))
}
new_iso_rect_from_4_numbers <- function(l, b, r, t) {
  new_geometry_vector(create_iso_rect_minmax(get_ptr(l), get_ptr(b), get_ptr(r), get_ptr(t)))
}
