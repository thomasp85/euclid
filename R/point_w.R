#' Vector of weighted points
#'
#' This class is an extension (but not a subclass of) [point()]. It simply
#' attaches a numeric weight to the point that is carried along with it.
#' However, most of the functionality of points are lost with this vector class
#' as all the a math operations are gone due to ambiguity on whether to operate
#' on the point or the weight. Weighted points can easily be converted to points
#' however.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A point vector or an object to convert to it
#'
#' @return a `euclid_point_w` vector
#'
#' @section Constructors:
#' **2 dimensional weighted points**
#' - Providing three numeric vector will construct points with those x and y
#'   coordinate and a weight.
#' - Providing a point and a numeric will construct points with the given weight
#'
#' **3 dimensional weighted points**
#' - Providing four numeric vector will construct points with those x, y and z
#'   coordinate and a weight.
#' - Providing a point and a numeric will construct points with the given weight
#'
#' @export
weighted_point <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_point_w_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]

  if (length(points) == 1 && length(numbers) > 0) {
    new_point_w_from_pw(points[[1]], numbers[[1]])
  } else if (length(numbers) == 3) {
    new_point_w_from_xyw(numbers[[1]], numbers[[2]], numbers[[3]])
  } else if (length(numbers) == 4) {
    new_point_w_from_xyzw(numbers[[1]], numbers[[2]], numbers[[3]], numbers[[4]])
  } else {
    rlang::abort("Don't know how to construct weighted points from the given input")
  }
}
#' @rdname weighted_point
#' @export
is_weighted_point <- function(x) inherits(x, "euclid_point_w")

# Conversion --------------------------------------------------------------

#' @rdname point
#' @export
as_weighted_point <- function(x) {
  UseMethod("as_weighted_point")
}
#' @export
as_weighted_point.default <- function(x) {
  rlang::abort("Don't know how to convert the input to weighted points")
}
#' @export
as_weighted_point.euclid_point_w <- function(x) x

#' @export
as_point.euclid_point_w <- function(x) {
  point(x)
}

# Internal constructors ---------------------------------------------------

new_point_w2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_point_w2", "euclid_point_w"))
}
new_point_w3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_point_w3", "euclid_point_w"))
}
new_point_w_empty <- function(dim) {
  if (dim == 2) {
    new_point_w2(create_point_w_2_empty())
  } else {
    new_point_w3(create_point_w_3_empty())
  }
}
new_point_w_from_xyw <- function(x, y, w) {
  new_point_w2(create_point_w_2_x_y_w(get_ptr(x), get_ptr(y), get_ptr(w)))
}
new_point_w_from_xyzw <- function(x, y, z, w) {
  new_point_w3(create_point_w_3_x_y_z_w(get_ptr(x), get_ptr(y), get_ptr(z), get_ptr(w)))
}
new_point_w_from_pw <- function(p, w) {
  if (dim(p) == 2) {
    new_point_w2(create_point_w_2_p_w(get_ptr(p), get_ptr(w)))
  } else {
    new_point_w3(create_point_w_3_p_w(get_ptr(p), get_ptr(w)))
  }
}
