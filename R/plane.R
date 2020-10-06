#' Vector of planes
#'
#' @export
plane <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_plane_empty())
  }

  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  points <- inputs[vapply(inputs, is_point, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  directions <- inputs[vapply(inputs, is_direction, logical(1))]
  lines <- inputs[vapply(inputs, is_line, logical(1))]
  rays <- inputs[vapply(inputs, is_ray, logical(1))]
  segments <- inputs[vapply(inputs, is_segment, logical(1))]
  circles <- inputs[vapply(inputs, is_circle, logical(1))]
  triangles <- inputs[vapply(inputs, is_triangle, logical(1))]

  if (length(numbers) == 4) {
    new_plane_from_abcd(numbers[[1]], numbers[[2]], numbers[[3]], numbers[[4]])
  } else if (length(points) == 3) {
    new_plane_from_3_points(points[[1]], points[[2]], points[[3]])
  } else if (length(points) == 1 && length(vectors) == 1) {
    new_plane_from_point_vector(points[[1]], vectors[[1]])
  } else if (length(points) == 1 && length(directions) == 1) {
    new_plane_from_point_direction(points[[1]], directions[[1]])
  } else if (length(points) == 1 && length(lines) == 1) {
    new_plane_from_point_line(points[[1]], lines[[1]])
  } else if (length(points) == 1 && length(rays) == 1) {
    new_plane_from_point_ray(points[[1]], rays[[1]])
  } else if (length(points) == 1 && length(segments) == 1) {
    new_plane_from_point_segment(points[[1]], segments[[1]])
  } else if (length(circles) == 1) {
    new_plane_from_circle(circles[[1]])
  } else if (length(triangles) == 1) {
    new_plane_from_triangle(triangles[[1]])
  } else {
    rlang::abort("Don't know how to construct planes from the given input")
  }
}
#' @rdname plane
#' @export
is_plane <- function(x) inherits(x, "euclid_plane")


# Conversion --------------------------------------------------------------

#' @rdname plane
#' @export
as_plane <- function(x) {
  UseMethod("as_plane")
}
#' @export
as_plane.default <- function(x) {
  rlang::abort("Don't know how to convert the input to planes")
}
#' @export
as_plane.euclid_plane <- function(x) x

# Internal Constructors ---------------------------------------------------

new_plane <- function(x) {
  new_geometry_vector(x, class = "euclid_plane")
}
new_plane_empty <- function() {
  new_plane(create_plane_empty())
}
new_plane_from_abcd <- function(a, b, c, d) {
  new_plane(create_plane_abcd(get_ptr(a), get_ptr(b), get_ptr(c), get_ptr(d)))
}
new_plane_from_3_points <- function(p, q, r) {
  new_plane(create_plane_pqr(get_ptr(p), get_ptr(q), get_ptr(r)))
}
new_plane_from_point_vector <- function(p, v) {
  new_plane(create_plane_pv(get_ptr(p), get_ptr(v)))
}
new_plane_from_point_direction <- function(p, d) {
  new_plane(create_plane_pd(get_ptr(p), get_ptr(d)))
}
new_plane_from_point_line <- function(p, l) {
  new_plane(create_plane_pl(get_ptr(p), get_ptr(l)))
}
new_plane_from_point_ray <- function(p, r) {
  new_plane(create_plane_pr(get_ptr(p), get_ptr(r)))
}
new_plane_from_point_segment <- function(p, s) {
  new_plane(create_plane_ps(get_ptr(p), get_ptr(s)))
}
new_plane_from_circle <- function(circ) {
  new_plane(create_plane_circle(get_ptr(circ)))
}
new_plane_from_triangle <- function(tri) {
  new_plane(create_plane_triangle(get_ptr(tri)))
}
