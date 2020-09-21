#' Vector of circles
#'
#' This function create circles from various combinations of input.
#'
#' @param ... Various input. See the Constructor section.
#' @param x A circle vector
#'
#' @return An `euclid_circle2` or `euclid_circle3` vector
#'
#' @section Constructors:
#' **2 dimensional circles**
#' - Providing one point and one numeric vector will construct circles centered
#'   at the point with the radius given by the numeric.
#' - Providing two point vectors will construct circles centered between the two
#'   points with a radius of half the distance between the two points.
#' - Providing three point vectors will construct the unique circle that pass
#'   through the three points.
#'
#' @export
#'
#' @examples
#' ## 2 Dimensions
#'
#' point1 <- point(runif(5), runif(5))
#' point2 <- point(runif(5), runif(5))
#' point3 <- point(runif(5), runif(5))
#' number <- exact_numeric(1:5)
#'
#' # Construction with center and radius
#' circle(point1, number)
#'
#' # integers and numerics are converted automatically
#' circle(point1, 1:5)
#'
#' # You are free to name the input for readability
#' circle(center = point1, radius = number)
#'
#' # Construction with 2 points
#' circle(point1, point2)
#'
#' # Construction with 3 points
#' circle(point1, point2, point3)
#'
circle <- function(...) {
  inputs <- lapply(list(...), function(x) {
    if (!is_geometry(x)) {
      x <- as_exact_numeric(x)
    }
    x
  })
  dim <- unique(unlist(lapply(inputs, dim)))
  if (length(dim) != 1) {
    rlang::abort("Inputs must be of the same dimensionality")
  }
  input_lengths <- lengths(inputs)
  max_length <- max(input_lengths)
  if (any(input_lengths != 1 & input_lengths != max_length)) {
    rlang::abort("Inputs must be either scalar or of the same length")
  }
  inputs[input_lengths == 1] <- lapply(inputs[input_lengths == 1], function(x) {
    rep_len(x, max_length)
  })

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]

  if (length(points) == 3) {
    new_circle_from_3_points(points[[1]], points[[2]], points[[3]])
  } else if (length(points) == 2) {
    new_circle_from_2_points(points[[1]], points[[2]])
  } else if (length(points) == 1 && length(numbers) >= 1) {
    new_circle_from_point_number(points[[1]], numbers[[1]])
  } else {
    rlang::abort("Don't know how to construct a circle from the given input")
  }
}
#' @rdname circle
#' @export
is_circle <- function(x) inherits(x, "euclid_circle")

new_circle_from_point_number <- function(center, r) {
  if (dim(center) != 2) {
    rlang::abort("Circles in 3 dimensions cannot be constructed from center and radius")
  }
  new_geometry_vector(create_circle_2_center_radius(get_ptr(center), get_ptr(r)), class = c("euclid_circle2", "euclid_circle"))
}
new_circle_from_3_points <- function(p, q, r) {
  if (dim(p) == 2) {
    new_geometry_vector(create_circle_2_3_point(get_ptr(p), get_ptr(q), get_ptr(r)), class = c("euclid_circle2", "euclid_circle"))
  }
}
new_circle_from_2_points <- function(p, q) {
  if (dim(p) != 2) {
    rlang::abort("Circles in 3 dimensions cannot be constructed from 2 points")
  }
  new_geometry_vector(create_circle_2_2_point(get_ptr(p), get_ptr(q)), class = c("euclid_circle2", "euclid_circle"))
}
