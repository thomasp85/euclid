#' Vector of rays
#'
#' A ray is a directed line that starts at a given point and extends to
#' infinity. As such it does not have a magnitude (like a vector) but only a
#' beginning and a direction. A ray is considered to be
#' [degenerate][is_degenerate] if constructed be two points that are equal (and
#' thus have no direction). Rays can be flipped by taking their negative
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A vector of rays or an object to convert to it
#'
#' @return An `euclid_ray` vector
#'
#' @section Constructors:
#' **2 and 3 dimensional rays**
#' - Providing two points will construct rays starting at the first point and
#'   going through the second
#' - Providing a point and a vector will construct rays starting at the point
#'   and moving in the direction of the vector.
#' - Providing a point and a direction will construct rays starting at the point
#'   and moving in the given direction.
#' - Providing a point and a line will construct rays starting at the point
#'   and moving in the direction of the line. Note that the point does not have
#'   lie on line.
#'
#' @export
#'
#' @examples
#' # Construction
#' p <- point(sample(10, 2), sample(10, 2))
#' r <- ray(p[1], p[2])
#' r
#'
#' ray(p, -as_vec(p))
#'
#' ray(p, direction(7, -2))
#'
#' ray(p, line(3, 10, -8))
#'
#' # Flip direction
#' -r
#'
#' # Convert to vector, direction, or lines
#' as_vec(r)
#'
#' as_direction(r)
#'
#' as_line(r)
#'
ray <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_ray_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  directions <- inputs[vapply(inputs, is_direction, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  lines <- inputs[vapply(inputs, is_line, logical(1))]

  if (length(points) == 2) {
    new_ray_from_2_points(points[[1]], points[[2]])
  } else if (length(points) == 1 && length(directions) == 1) {
    new_ray_from_point_direction(points[[1]], directions[[1]])
  } else if (length(points) == 1 && length(vectors) == 1) {
    new_ray_from_point_vector(points[[1]], vectors[[1]])
  } else if (length(points) == 1 && length(lines) == 1) {
    new_ray_from_point_line(points[[1]], lines[[1]])
  } else {
    rlang::abort("Don't know how to construct rays from the given input")
  }
}
#' @rdname ray
#' @export
is_ray <- function(x) inherits(x, "euclid_ray")

# Conversion --------------------------------------------------------------

#' @rdname ray
#' @export
as_ray <- function(x) {
  UseMethod("as_ray")
}
#' @export
as_ray.default <- function(x) {
  rlang::abort("Don't know how to convert the input to rays")
}
#' @export
as_ray.euclid_ray <- function(x) x

#' @export
as_vec.euclid_ray <- function(x) {
  vec(x)
}

#' @export
as_direction.euclid_ray <- function(x) {
  direction(x)
}
#' @export
as_line.euclid_ray <- function(x) {
  line(x)
}

# Operators ---------------------------------------------------------------

#' @export
geometry_op_minus.euclid_ray <- function(e1, e2) {
  if (!missing(e2)) {
    rlang::abort("Rays cannot be subtracted, only negated")
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(ray_2_negate(get_ptr(e1)), e1)
  } else {
    restore_euclid_vector(ray_3_negate(get_ptr(e1)), e1)
  }
}

# Internal Constructors ---------------------------------------------------

new_ray_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_ray_2_empty())
  } else {
    new_geometry_vector(create_ray_3_empty())
  }
}
new_ray_from_2_points <- function(p, q) {
  if (dim(p) == 2) {
    new_geometry_vector(create_ray_2_p_q(get_ptr(p), get_ptr(q)))
  } else {
    new_geometry_vector(create_ray_3_p_q(get_ptr(p), get_ptr(q)))
  }
}
new_ray_from_point_direction <- function(p, d) {
  if (dim(p) == 2) {
    new_geometry_vector(create_ray_2_p_d(get_ptr(p), get_ptr(d)))
  } else {
    new_geometry_vector(create_ray_3_p_d(get_ptr(p), get_ptr(d)))
  }
}
new_ray_from_point_vector <- function(p, v) {
  if (dim(p) == 2) {
    new_geometry_vector(create_ray_2_p_v(get_ptr(p), get_ptr(v)))
  } else {
    new_geometry_vector(create_ray_3_p_v(get_ptr(p), get_ptr(v)))
  }
}
new_ray_from_point_line <- function(p, l) {
  if (dim(p) == 2) {
    new_geometry_vector(create_ray_2_p_l(get_ptr(p), get_ptr(l)))
  } else {
    new_geometry_vector(create_ray_3_p_l(get_ptr(p), get_ptr(l)))
  }
}
