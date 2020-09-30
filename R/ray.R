#' Vector of rays
#'
#' A ray is a directed line that starts at a given point and extends to
#' infinity. As such it does not have a magnitude (like a vector) but only a
#' beginning and a direction.
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
#'
#' @export
#'
ray <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_ray_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]

  if (length(points) == 2) {
    new_ray_from_pq(points[[1]], points[[2]])
  } else if (length(points) > 0 && length(vectors) > 0) {
    new_ray_from_pv(points[[1]], vectors[[2]])
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

# Operators ---------------------------------------------------------------

#' @export
geometry_op_minus.euclid_vector <- function(e1, e2) {
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

new_ray2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_ray2", "euclid_ray"))
}
new_ray3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_ray3", "euclid_ray"))
}
new_ray_empty <- function(dim) {
  if (dim == 2) {
    new_ray2(create_ray_2_empty())
  } else {
    new_ray3(create_ray_3_empty())
  }
}
new_ray_from_pq <- function(p, q) {
  if (dim(p) == 2) {
    new_ray2(create_ray_2_p_q(get_ptr(p), get_ptr(q)))
  } else {
    new_ray3(create_ray_3_p_q(get_ptr(p), get_ptr(q)))
  }
}
new_ray_from_pv <- function(p, v) {
  if (dim(p) == 2) {
    new_ray2(create_ray_2_p_v(get_ptr(p), get_ptr(v)))
  } else {
    new_ray3(create_ray_3_p_v(get_ptr(p), get_ptr(v)))
  }
}
