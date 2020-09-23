#' Vector of vectors
#'
#' A geometrical vector is somewhat different from the concept of a vector in
#' programming hence the slightly confusing terminology. In geometry a vector is
#' a direction and a magnitude most often defined by a point in space where the
#' direction is defined as the direction from the origin to the point and the
#' magnitude is defined as the distance from the origin to the point.
#'
#' @param ... Various input. See the Constructor section.
#' @param x A vector of vectors or an object to convert to it
#'
#' @return An `euclid_vector` vector
#'
#' @section Constructors:
#' **2 dimensional vectors**
#' - Providing a point will construct vectors pointing to the points from the
#'   origin centered.
#' - Providing two exact numeric vectors will construct vectors pointing to the
#'   point defined by the coordinates given.
#'
#' **3 dimensional vectors**
#' - Providing a point will construct vectors pointing to the points from the
#'   origin centered.
#' - Providing three exact numeric vectors will construct vectors pointing to
#'   the point defined by the coordinates given.
#'
#' @export
vec <- function(...) {
  inputs <- validate_constructor_input(...)

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]

  if (length(points) == 1) {
    new_vector_from_point(points[[1]])
  } else if (length(numbers) == 2) {
    new_vector_from_xy(numbers[[1]], numbers[[2]])
  } else if (length(numbers) == 3) {
    new_vector_from_xyz(numbers[[1]], numbers[[2]], numbers[[3]])
  } else {
    rlang::abort("Don't know how to construct vectors from the given input")
  }
}
#'
#' @rdname vec
#' @export
is_vec <- function(x) inherits(x, "euclid_vector")

# Conversion --------------------------------------------------------------

#' @rdname vec
#' @export
as_vec <- function(x) {
  UseMethod("as_vec")
}
#' @export
as_vec.default <- function(x) {
  rlang::abort("Don't know how to convert the input to vectors")
}
#' @export
as_vec.euclid_vector <- function(x) x

#' @export
as_point.euclid_vector <- function(x) {
  point(x)
}

# Internal Constructors ---------------------------------------------------

new_vector2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_vector2", "euclid_vector"))
}
new_vector3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_vector3", "euclid_vector"))
}
new_vector_from_point <- function(p) {
  if (dim(p) == 2) {
    new_vector2(create_vector_2_point(get_ptr(p)))
  } else {
    new_vector3(create_vector_3_point(get_ptr(p)))
  }
}
new_vector_from_xy <- function(x, y) {
  new_vector2(create_vector_2_x_y(get_ptr(x), get_ptr(y)))
}
new_vector_from_xyz <- function(x, y, z) {
  new_vector3(create_vector_3_x_y_z(get_ptr(x), get_ptr(y), get_ptr(z)))
}
