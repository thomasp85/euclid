#' Vector of lines
#'
#' A line is an undirected infinite line. For 2D it can be defined by the line
#' equation `ax + by + c = 0` whereas for 3D it is usually defined by a point
#' and a direction in the same way as rays, but implicitly extending to infinity
#' in the opposite direction as well.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A vector of lines or an object to convert to it
#'
#' @return An `euclid_line` vector
#'
#' @section Constructors:
#' **2 dimensional rays**
#' - Providing 3 numerics will create lines with the given line equation
#' - Providing two points will construct lines going through those
#' - Providing a point and a vector will construct lines going through the point
#'   and extending in the direction of the vector.
#' - Providing a point and a direction will construct lines going through the
#'   point and extending in the given direction.
#' - Providing a ray will construct the supporting line for the ray
#' - Providing a segment will construct the supporting line for the segment
#'
#' **3 dimensional rays**
#' - Providing two points will construct lines going through those
#' - Providing a point and a vector will construct lines going through the point
#'   and extending in the direction of the vector.
#' - Providing a point and a direction will construct lines going through the
#'   point and extending in the given direction.
#' - Providing a ray will construct the supporting line for the ray
#' - Providing a segment will construct the supporting line for the segment
#'
#' @export
#'
#' @examples
#' # Construction
#' l <- line(sample(10, 2), sample(10, 2), sample(10, 2))
#' l
#'
#' # 3D lines cannot be constructed from coefficients
#' p <- point(sample(6), sample(6), sample(6))
#' line(p[1:3], p[4:6])
#'
#' # Construction from point and vector
#' line(p, vec(4, -2, 0))
#'
line <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_line_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  directions <- inputs[vapply(inputs, is_direction, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  segments <- inputs[vapply(inputs, is_segment, logical(1))]
  rays <- inputs[vapply(inputs, is_ray, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]

  if (length(points) == 2) {
    new_line_from_pq(points[[1]], points[[2]])
  } else if (length(segments) == 1) {
    new_line_from_seg(segments[[1]])
  } else if (length(rays) == 1) {
    new_line_from_ray(rays[[1]])
  } else if (length(numbers) == 3) {
    new_line_from_abc(numbers[[1]], numbers[[2]], numbers[[3]])
  } else if (length(points) == 1 && length(vectors) == 1) {
    new_line_from_pv(points[[1]], vectors[[1]])
  } else if (length(points) == 1 && length(directions) == 1) {
    new_line_from_pd(points[[1]], directions[[1]])
  } else {
    rlang::abort("Don't know how to construct lines from the given input")
  }
}
#' @rdname line
#' @export
is_line <- function(x) inherits(x, "euclid_line")

# Conversion --------------------------------------------------------------

#' @rdname line
#' @export
as_line <- function(x) {
  UseMethod("as_line")
}
#' @export
as_line.default <- function(x) {
  rlang::abort("Don't know how to convert the input to lines")
}
#' @export
as_line.euclid_line <- function(x) x

#' @export
as_direction.euclid_line <- function(x) {
  direction(x)
}
#' @export
as_vec.euclid_line <- function(x) {
  vec(x)
}

# Internal Constructors ---------------------------------------------------

new_line2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_line2", "euclid_line"))
}
new_line3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_line3", "euclid_line"))
}
new_line_empty <- function(dim) {
  if (dim == 2) {
    new_line2(create_line_2_empty())
  } else {
    new_line3(create_line_3_empty())
  }
}
new_line_from_pq <- function(p, q) {
  if (dim(p) == 2) {
    new_line2(create_line_2_p_q(get_ptr(p), get_ptr(q)))
  } else {
    new_line3(create_line_3_p_q(get_ptr(p), get_ptr(q)))
  }
}
new_line_from_pv <- function(p, v) {
  if (dim(p) == 2) {
    new_line2(create_line_2_p_v(get_ptr(p), get_ptr(v)))
  } else {
    new_line3(create_line_3_p_v(get_ptr(p), get_ptr(v)))
  }
}
new_line_from_pd <- function(p, d) {
  if (dim(p) == 2) {
    new_line2(create_line_2_p_d(get_ptr(p), get_ptr(d)))
  } else {
    new_line3(create_line_3_p_d(get_ptr(p), get_ptr(d)))
  }
}
new_line_from_abc <- function(a, b, c) {
  new_line2(create_line_2_a_b_c(get_ptr(a), get_ptr(b), get_ptr(c)))
}
new_line_from_ray <- function(r) {
  if (dim(r) == 2) {
    new_line2(create_line_2_ray(get_ptr(r)))
  } else {
    new_line3(create_line_3_ray(get_ptr(r)))
  }
}
new_line_from_seg <- function(s) {
  if (dim(s) == 2) {
    new_line2(create_line_2_seg(get_ptr(s)))
  } else {
    new_line3(create_line_3_seg(get_ptr(s)))
  }
}
