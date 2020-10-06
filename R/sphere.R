#' Vector of spheres
#'
#' @export
sphere <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_sphere_empty())
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  circles <- inputs[vapply(inputs, is_circle, logical(1))]

  if (length(points) == 4) {
    new_sphere_from_4_points(points[[1]], points[[2]], points[[3]], points[[4]])
  } else if (length(points) == 3) {
    new_sphere_from_3_points(points[[1]], points[[2]], points[[3]])
  } else if (length(points) == 2) {
    new_sphere_from_2_points(points[[1]], points[[2]])
  } else if (length(points) == 1 && length(numbers) == 1) {
    new_sphere_from_center_radius(points[[1]], numbers[[1]])
  } else if (length(circles) == 1) {
    new_sphere_from_circle(circles[[1]])
  } else {
    rlang::abort("Don't know how to construct spheres from the given input")
  }
}
#' @rdname sphere
#' @export
is_sphere <- function(x) inherits(x, "euclid_sphere")


# Conversion --------------------------------------------------------------

#' @rdname sphere
#' @export
as_sphere <- function(x) {
  UseMethod("as_sphere")
}
#' @export
as_sphere.default <- function(x) {
  rlang::abort("Don't know how to convert the input to spheres")
}
#' @export
as_sphere.euclid_sphere <- function(x) x

# Internal Constructors ---------------------------------------------------

new_sphere <- function(x) {
  new_geometry_vector(x, class = "euclid_sphere")
}
new_sphere_empty <- function() {
  new_sphere(create_sphere_empty())
}
new_sphere_from_2_points <- function(p, q) {
  new_sphere(create_sphere_2_point(get_ptr(p), get_ptr(q)))
}
new_sphere_from_3_points <- function(p, q, r) {
  new_sphere(create_sphere_3_point(get_ptr(p), get_ptr(q), get_ptr(r)))
}
new_sphere_from_4_points <- function(p, q, r, s) {
  new_sphere(create_sphere_4_point(get_ptr(p), get_ptr(q), get_ptr(r), get_ptr(s)))
}
new_sphere_from_center_radius <- function(center, r2) {
  new_sphere(create_sphere_center_radius(get_ptr(center), get_ptr(r2)))
}
new_sphere_from_circle <- function(circ) {
  new_sphere(create_sphere_circle(get_ptr(circ)))
}
