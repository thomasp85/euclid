#' Vector of tetrahedrons
#'
#' @export
tetrahedron <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_tetrahedron_empty())
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]

  if (length(points) == 4) {
    new_tetrahedron_from_4_points(points[[1]], points[[2]], points[[3]], points[[4]])
  } else {
    rlang::abort("Don't know how to construct tetrahedrons from the given input")
  }
}
#' @rdname tetrahedron
#' @export
is_tetrahedron <- function(x) inherits(x, "euclid_tetrahedron")


# Conversion --------------------------------------------------------------

#' @rdname tetrahedron
#' @export
as_tetrahedron <- function(x) {
  UseMethod("as_tetrahedron")
}
#' @export
as_tetrahedron.default <- function(x) {
  rlang::abort("Don't know how to convert the input to tetrahedrons")
}
#' @export
as_tetrahedron.euclid_tetrahedron <- function(x) x

# Internal Constructors ---------------------------------------------------

new_tetrahedron <- function(x) {
  new_geometry_vector(x, class = "euclid_tetrahedron")
}
new_tetrahedron_empty <- function() {
  new_tetrahedron(create_tetrahedron_empty())
}
new_tetrahedron_from_4_points <- function(p, q, r, s) {
  new_tetrahedron(create_tetrahedron_4points(get_ptr(p), get_ptr(q), get_ptr(r), get_ptr(s)))
}
