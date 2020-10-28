#' Vector of circles
#'
#' A circle is defined by a center and a radius (given as the squared radius due
#' to the inexactness of square roots). In 3 dimensions a circle is a disc and
#' thus have an orientation given by an orthogonal direction. If the radius is 0
#' the circle is considered [degenerate][is_degenerate].
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A circle vector or an object to convert to it
#'
#' @return An `euclid_circle` vector
#'
#' @section Constructors:
#' **2 dimensional circles**
#' - Providing one point and one numeric vector will construct circles centered
#'   at the point with the **squared** radius given by the numeric.
#' - Providing two points will construct circles centered between the two
#'   points with a radius of half the distance between the two points.
#' - Providing three point vectors will construct the unique circle that pass
#'   through the three points.
#'
#' **3 dimensional circles**
#' - Providing three point vectors will construct the unique circle that pass
#'   through the three points.
#' - Providing a point, a numeric, and a plane will construct a circle centered
#'   on the point with the squared radius given by the numeric and the
#'   orientation given by the plane. The point must lie on the plane
#' - Providing a point, a numeric, and a vector will construct a circle centered
#'   on the point with the squared radius given by the numeric and the
#'   orientation orthogonal to the vector
#' - Providing two spheres will construct a circle given by the intersection of
#'   the two spheres. The spheres must intersect
#' - Providing a sphere and a plane will construct a circle given by the
#'   intersection of the sphere and the plane. The sphere and plane must
#'   intersect.
#'
#' @export
#'
#' @examples
#' ## 2 Dimensions
#'
#' point1 <- point(runif(5), runif(5))
#' point2 <- point(runif(5), runif(5))
#' point3 <- point(runif(5), runif(5))
#' number <- exact_numeric(1:5)
#'
#' # Construction with center and radius
#' circ <- circle(point1, number)
#' circ
#' plot(circ)
#'
#' # integers and numerics are converted automatically
#' circle(point1, 1:5)
#'
#' # You are free to name the input for readability
#' circle(center = point1, radius = number)
#'
#' # Construction with 2 points
#' circle(point1, point2)
#'
#' # Construction with 3 points
#' circle(point1, point2, point3)
#'
#' plot(circle(point1[1], point1[2], point1[3]))
#' euclid_plot(point1[1:3], col = "firebrick", pch = 16, cex = 3)
#'
#' ## 3 Dimensions
#'
#' point1 <- point(runif(5), runif(5), runif(5))
#' point2 <- point(runif(5), runif(5), runif(5))
#' point3 <- point(runif(5), runif(5), runif(5))
#'
#' circ <- circle(point1, point2, point3)
#'
#' circle(point1, number, as_vec(point2))
#'
#' # Conversion
#' as_plane(circ)
#'
#' as_sphere(circ)
#'
circle <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_circle_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  planes <- inputs[vapply(inputs, is_plane, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  spheres <- inputs[vapply(inputs, is_sphere, logical(1))]

  if (length(points) == 3) {
    new_circle_from_3_points(points[[1]], points[[2]], points[[3]])
  } else if (length(points) == 2) {
    new_circle_from_2_points(points[[1]], points[[2]])
  } else if (length(points) == 1 && length(numbers) == 1 && length(planes) == 1) {
    new_circle_from_point_number_plane(points[[1]], numbers[[1]], planes[[1]])
  } else if (length(points) == 1 && length(numbers) == 1 && length(vectors) == 1) {
    new_circle_from_point_number_vec(points[[1]], numbers[[1]], vectors[[1]])
  } else if (length(points) == 1 && length(numbers) == 1) {
    new_circle_from_point_number(points[[1]], numbers[[1]])
  } else if (length(spheres) == 2) {
    new_circle_from_2_spheres(spheres[[1]], spheres[[2]])
  } else if (length(spheres) == 1 && length(planes) == 1) {
    new_circle_from_sphere_plane(spheres[[1]], planes[[1]])
  } else {
    rlang::abort("Don't know how to construct circles from the given input")
  }
}
#' @rdname circle
#' @export
is_circle <- function(x) inherits(x, "euclid_circle")

# Conversion --------------------------------------------------------------

#' @rdname circle
#' @export
as_circle <- function(x) {
  UseMethod("as_circle")
}
#' @export
as_circle.default <- function(x) {
  rlang::abort("Don't know how to convert the input to circles")
}
#' @export
as_circle.euclid_circle <- function(x) x

#' @export
as_sphere.euclid_circle3 <- function(x) {
  sphere(x)
}
#' @export
as_plane.euclid_circle3 <- function(x) {
  plane(x)
}

# Internal Constructors ---------------------------------------------------

new_circle_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_circle_2_empty())
  } else {
    new_geometry_vector(create_circle_3_empty())
  }
}
new_circle_from_point_number <- function(center, r) {
  if (dim(center) != 2) {
    rlang::abort("Circles in 3 dimensions cannot be constructed from center and radius")
  }
  new_geometry_vector(create_circle_2_center_radius(get_ptr(center), get_ptr(r)))
}
new_circle_from_point_number_plane <- function(center, r, p) {
  new_geometry_vector(create_circle_3_center_radius_plane(get_ptr(center), get_ptr(r), get_ptr(p)))
}
new_circle_from_point_number_vec <- function(center, r, v) {
  new_geometry_vector(create_circle_3_center_radius_vec(get_ptr(center), get_ptr(r), get_ptr(v)))
}
new_circle_from_3_points <- function(p, q, r) {
  if (dim(p) == 2) {
    new_geometry_vector(create_circle_2_3_point(get_ptr(p), get_ptr(q), get_ptr(r)))
  } else {
    new_geometry_vector(create_circle_3_3_point(get_ptr(p), get_ptr(q), get_ptr(r)))
  }
}
new_circle_from_2_points <- function(p, q) {
  if (dim(p) != 2) {
    rlang::abort("Circles in 3 dimensions cannot be constructed from 2 points")
  }
  new_geometry_vector(create_circle_2_2_point(get_ptr(p), get_ptr(q)))
}
new_circle_from_2_spheres <- function(s1, s2) {
  new_geometry_vector(create_circle_3_sphere_sphere(get_ptr(s1), get_ptr(s2)))
}
new_circle_from_sphere_plane <- function(s, p) {
  new_geometry_vector(create_circle_3_sphere_plane(get_ptr(s), get_ptr(p)))
}
