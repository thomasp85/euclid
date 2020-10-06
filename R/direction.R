#' Vector of directions
#'
#' @export
direction <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_direction_empty(default_dim))
  }

  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  lines <- inputs[vapply(inputs, is_line, logical(1))]
  rays <- inputs[vapply(inputs, is_ray, logical(1))]
  segments <- inputs[vapply(inputs, is_segment, logical(1))]

  if (length(numbers) == 3) {
    new_direction_from_x_y_z(numbers[[1]], numbers[[2]], numbers[[3]])
  } else if (length(numbers) == 2) {
    new_direction_from_x_y(numbers[[1]], numbers[[2]])
  } else if (length(lines) == 1) {
    new_direction_from_line(lines[[1]])
  } else if (length(rays) == 1) {
    new_direction_from_ray(rays[[1]])
  } else if (length(segments) == 1) {
    new_direction_from_segment(segments[[1]])
  } else {
    rlang::abort("Don't know how to construct directions from the given input")
  }
}
#' @rdname direction
#' @export
is_direction <- function(x) inherits(x, "euclid_direction")


# Conversion --------------------------------------------------------------

#' @rdname direction
#' @export
as_direction <- function(x) {
  UseMethod("as_direction")
}
#' @export
as_direction.default <- function(x) {
  rlang::abort("Don't know how to convert the input to directions")
}
#' @export
as_direction.euclid_direction <- function(x) x

#' @export
as_vec.euclid_direction <- function(x) {
  vec(x)
}

# Internal Constructors ---------------------------------------------------

new_direction2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_direction2", "euclid_direction"))
}
new_direction3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_direction3", "euclid_direction"))
}
new_direction_empty <- function(dim) {
  if (dim == 2) {
    new_direction2(create_direction_2_empty())
  } else {
    new_direction3(create_direction_3_empty())
  }
}
new_direction_from_line <- function(l) {
  if (dim(l) == 2) {
    new_direction2(create_direction_2_line(get_ptr(l)))
  } else {
    new_direction3(create_direction_3_line(get_ptr(l)))
  }
}
new_direction_from_ray <- function(r) {
  if (dim(r) == 2) {
    new_direction2(create_direction_2_ray(get_ptr(r)))
  } else {
    new_direction3(create_direction_3_ray(get_ptr(r)))
  }
}
new_direction_from_segment <- function(s) {
  if (dim(s) == 2) {
    new_direction2(create_direction_2_segment(get_ptr(s)))
  } else {
    new_direction3(create_direction_3_segment(get_ptr(s)))
  }
}
new_direction_from_x_y <- function(x, y) {
  new_direction2(create_direction_2_xy(get_ptr(x), get_ptr(y)))
}
new_direction_from_x_y_z <- function(x, y, z) {
  new_direction3(create_direction_3_xyz(get_ptr(x), get_ptr(y), get_ptr(z)))
}
