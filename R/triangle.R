#' Vector of triangles
#'
#' @export
triangle <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_triangle_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]

  if (length(points) == 3) {
    new_triangle_from_3_points(points[[1]], points[[2]], points[[3]])
  } else {
    rlang::abort("Don't know how to construct triangles from the given input")
  }
}
#' @rdname triangle
#' @export
is_triangle <- function(x) inherits(x, "euclid_triangle")


# Conversion --------------------------------------------------------------

#' @rdname triangle
#' @export
as_triangle <- function(x) {
  UseMethod("as_triangle")
}
#' @export
as_triangle.default <- function(x) {
  rlang::abort("Don't know how to convert the input to triangles")
}
#' @export
as_triangle.euclid_triangle <- function(x) x

#' @export
as_plane.euclid_triangle <- function(x) {
  plane(x)
}

# Internal Constructors ---------------------------------------------------

new_triangle2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_triangle2", "euclid_triangle"))
}
new_triangle3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_triangle3", "euclid_triangle"))
}
new_triangle_empty <- function(dim) {
  if (dim == 2) {
    new_triangle2(create_triangle_2_empty())
  } else {
    new_triangle3(create_triangle_3_empty())
  }
}
new_triangle_from_3_points <- function(p, q, r) {
  if (dim == 2) {
    new_triangle2(create_triangle_2_3points(get_ptr(p), get_ptr(q), get_ptr(r)))
  } else {
    new_triangle3(create_triangle_3_3points(get_ptr(p), get_ptr(q), get_ptr(r)))
  }
}
