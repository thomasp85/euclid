#' Vector of segments
#'
#' A segment is a finite directed line going from one point to another. If the
#' two points are equal it is considered to be [degenerate][is_degenerate]. A
#' segment can be flipped be taking its negative.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A vector of segments or an object to convert to it
#'
#' @return An `euclid_segment` vector
#'
#' @section Constructors:
#' **2 and 3 dimensional segments**
#' - Providing two points will construct segments starting at the first point
#'   and ending at the second
#' - Providing a point and a vector will construct segments starting at the
#'   point and ending at the point defined by the start point plus the vector
#'
#' @export
#'
#' @examples
#' # Construction
#' p <- point(sample(4), sample(4))
#' s <- segment(p[1:2], p[3:4])
#' s
#'
#' segment(p[1:2], as_vec(p[3:4]))
#'
#' # Flip segments
#' -s
#'
#' # Segments can be converted to vectors, directions and lines
#' as_vec(s)
#'
#' as_direction(s)
#'
#' as_line(s)
#'
segment <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_segment_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]

  if (length(points) == 2) {
    new_segment_from_2_points(points[[1]], points[[2]])
  } else if (length(points) == 1 && length(vectors) == 1) {
    new_segment_from_point_vector(points[[1]], vectors[[1]])
  } else {
    rlang::abort("Don't know how to construct segments from the given input")
  }
}
#' @rdname ray
#' @export
is_segment <- function(x) inherits(x, "euclid_segment")

# Conversion --------------------------------------------------------------

#' @rdname segment
#' @export
as_segment <- function(x) {
  UseMethod("as_segment")
}
#' @export
as_segment.default <- function(x) {
  rlang::abort("Don't know how to convert the input to segments")
}
#' @export
as_segment.euclid_segment <- function(x) x

#' @export
as_vec.euclid_segment <- function(x) {
  vec(x)
}
#' @export
as_direction.euclid_segment <- function(x) {
  direction(x)
}
#' @export
as_line.euclid_segment <- function(x) {
  line(x)
}

# Operators ---------------------------------------------------------------

#' @export
geometry_op_minus.euclid_segment <- function(e1, e2) {
  if (!missing(e2)) {
    rlang::abort("Segments cannot be subtracted, only negated")
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(segment_2_negate(get_ptr(e1)), e1)
  } else {
    restore_euclid_vector(segment_3_negate(get_ptr(e1)), e1)
  }
}

# Internal Constructors ---------------------------------------------------

new_segment_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_segment_2_empty())
  } else {
    new_geometry_vector(create_segment_3_empty())
  }
}
new_segment_from_2_points <- function(p, q) {
  if (dim(p) == 2) {
    new_geometry_vector(create_segment_2_p_q(get_ptr(p), get_ptr(q)))
  } else {
    new_geometry_vector(create_segment_3_p_q(get_ptr(p), get_ptr(q)))
  }
}
new_segment_from_point_vector <- function(p, v) {
  if (dim(p) == 2) {
    new_geometry_vector(create_segment_2_p_v(get_ptr(p), get_ptr(v)))
  } else {
    new_geometry_vector(create_segment_3_p_v(get_ptr(p), get_ptr(v)))
  }
}
