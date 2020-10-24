#' Calculate circumcenter of triangles, tetrahedrons, or sets of points
#'
#' The circumcenter is the center of the circle of sphere passing through the
#' vertices of a geometry (or the provided points).
#'
#' @param ... geometry vectors. Either a triangle or tetrahedron vector, or 2,
#' 3, or 4 point vectors. If 4 are provided they must be in 3D
#'
#' @return A points vector
#'
#' @export
#'
#' @examples
#' # Circumcenter of triangle
#' t <- triangle(point(1, 1), point(5, -2), point(6, 4))
#' circumcenter(t)
#'
#' # Same as providing the points directly
#' circumcenter(point(1, 1), point(5, -2), point(6, 4))
#'
#' # Same as getting the center of a circle constructed from the points
#' circ <- circle(point(1, 1), point(5, -2), point(6, 4))
#' vertex(circ)
#'
circumcenter <- function(...) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    rlang::abort("Geometries must be provided")
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  triangles <- inputs[vapply(inputs, is_triangle, logical(1))]
  tetrahedrons <- inputs[vapply(inputs, is_tetrahedron, logical(1))]

  if (length(triangles) == 1) {
    points <- list(
      vertex(triangles[[1]], 1),
      vertex(triangles[[1]], 2),
      vertex(triangles[[1]], 3)
    )
  } else if (length(tetrahedrons) == 1) {
    points <- list(
      vertex(tetrahedrons[[1]], 1),
      vertex(tetrahedrons[[1]], 2),
      vertex(tetrahedrons[[1]], 3),
      vertex(tetrahedrons[[1]], 4)
    )
  }
  if (length(points) == 2) {
    return(centroid(points[[1]], points[[1]]))
  } else if (length(points) == 3) {
    geo <- circle(points[[1]], points[[2]], points[[3]])
  } else if (length(points) == 4) {
    geo <- sphere(points[[1]], points[[2]], points[[3]], points[[4]])
  }
  vertex(geo)
}

#' Calculate barycenter of a set of weighted points
#'
#' The barycenter is the center of mass of 2 or more points. euclid supports
#' calculating the barycenter of up to 4 weighted points. If the weights are the
#' same between the points the barycenter corresponds to the centroid (or
#' midpoint in the case of two points).
#'
#' @param x,y,z,t vectors of weighted points. `z` and `t` are
#' optional
#'
#' @return A point vector
#'
#' @export
#'
#' @examples
#' barycenter(
#'   weighted_point(4, 2, 20),
#'   weighted_point(5, -4, 8),
#'   weighted_point(-3, 7, 13)
#' )
#'
barycenter <- function(x, y, z = NULL, t = NULL) {
  if (!is_weighted_point(x) || !is_weighted_point(y) ||
      (!is.null(z) && !is_weighted_point(z)) ||
      (!is.null(t) && !is_weighted_point(t))) {
    rlang::abort("Barycenter can only be calculated from weighted points")
  }
  if (is.null(z)) {
    new_geometry_vector(geometry_barycenter_2(get_ptr(x), get_ptr(y)))
  } else if (is.null(t)) {
    new_geometry_vector(geometry_barycenter_3(get_ptr(x), get_ptr(y), get_ptr(z)))
  } else {
    new_geometry_vector(geometry_barycenter_4(get_ptr(x), get_ptr(y), get_ptr(z), get_ptr(t)))
  }
}

#' Calculate the bisector of two geometries
#'
#' A bisector is a geometry that splits the space in two, i.e. a line in 2D and
#' a plane in 3D. Constructing a bisector from 2 geometries creates a split
#' where the edge at any given point has equal length to the two geometries.
#'
#' @param x,y Vector of points
#'
#' @return A vector of lines or planes depending on the dimensionality of x and
#' y
#'
#' @export
#'
#' @examples
#' bisector(point(4, -2), point(7, 5))
#'
bisector <- function(x, y) {
  new_geometry_vector(geometry_bisector(get_ptr(x), get_ptr(y)))
}

#' Calculate the centroid of a geometry or a set of points
#'
#' The centroid is the geometric mean of the vertices in a geometry. euclid
#' supports centroid calculations for triangles, tetrahedrons and 2-4 points
#'
#' @param x A vector of triangles or tetrahedrons, or points if `y`, `z`, or `t`
#' are provided
#' @param y,z,t Vector of points
#'
#' @return a vector of points
#'
#' @export
#'
#' @examples
#' # centroid of triangle
#' t <- triangle(point(1, 1), point(5, -2), point(6, 4))
#' centroid(t)
#'
#' # Same as providing the points directly
#' centroid(point(1, 1), point(5, -2), point(6, 4))
#'
centroid <- function(x, y = NULL, z = NULL, t = NULL) {
  if (is.null(y)) {
    new_geometry_vector(geometry_centroid_1(get_ptr(x)))
  } else if (is.null(z)) {
    if (!is_point(x) || !is_point(y)) {
      rlang::abort("`x` and `y` must be points")
    }
    x + (y - x) / 2
  } else if (is.null(t)) {
    if (!is_point(x) || !is_point(y) || !is_point(z)) {
      rlang::abort("`x`, `y`, and `z` must be points")
    }
    new_geometry_vector(geometry_centroid_3(get_ptr(x), get_ptr(y), get_ptr(z)))
  } else {
    if (!is_point(x) || !is_point(y) || !is_point(z) || !is_point(t)) {
      rlang::abort("`x`, `y`, `z`, and `t` must be points")
    }
    new_geometry_vector(geometry_centroid_4(get_ptr(x), get_ptr(y), get_ptr(z), get_ptr(t)))
  }
}

#' Construct the equidistant line of 2 or three points
#'
#' An equidistant line is a line that at any given point is the same distance to
#' the points that defines it. In 2 dimensions it is equivalent to the bisector
#' of the two points. In 3 dimensions it is defined for 3 points (2 points would
#' give a bisector plane).
#'
#' @param x,y,z Vector of points. If z is given they must be in 3D, otherwise in
#' 2D
#'
#' @return A vector of lines
#'
#' @export
#'
#' @examples
#' equidistant_line(
#'   point(3, 7, 2),
#'   point(6, -4, 9),
#'   point(2, 1, -5)
#' )
#'
#' # In 2D you get the bisector
#' equidistant_line(point(2, 5), point(3, 2)) == bisector(point(2, 5), point(3, 2))
#'
equidistant_line <- function(x, y, z = NULL) {
  if (is.null(z)) {
    if (!is_point(x) || !is_point(y) ||
        dim(x) != 2 || dim(y) != 2) {
      rlang::abort("`x` and `y` must be points in 2 dimensions")
    }
    bisector(x, y)
  } else {
    if (!is_point(x) || !is_point(y) || !is_point(z) ||
        dim(x) != 3 || dim(y) != 3 || dim(z) != 3) {
      rlang::abort("`x`, `y`, and `z` must be points in 3 dimensions")
    }
    new_geometry_vector(geometry_equidistant_line(get_ptr(x), get_ptr(y), get_ptr(z)))
  }
}

#' Calculate radical line of two circles or radical plane of two spheres
#'
#' The radical line or plane is the line (or plane) perpendicular to the line
#' connecting the two circles or spheres and positioned such that at any point
#' the tangent lines drawn to the two circles or spheres will have equal length.
#' If the circles or sphere cross the radical will be positioned at the crossing
#' points. It is not defined for cocentric circles and spheres. The radical
#' point is defined as the intersection point of the three radical lines of
#' three circles, or three radical planes of three spheres.
#'
#' @param x,y,z vector of circles in 2D or spheres. If `z` is given the radical
#' point will be computed
#'
#' @return A vector of lines or planes depending on the input
#'
#' @export
#'
#' @examples
#' # Radical line
#' radical(
#'   circle(point(3, 6), 12),
#'   circle(point(-6, 2), 3)
#' )
#'
#' # Radical plane
#' radical(
#'   sphere(point(3, 6, 3), 12),
#'   sphere(point(-6, 2, 7), 3)
#' )
#'
radical <- function(x, y, z = NULL) {
  r <- new_geometry_vector(geometry_radical_geometry(get_ptr(x), get_ptr(y)))
  if (is.null(z)) {
    return(r)
  }
  r2 <- new_geometry_vector(geometry_radical_geometry(get_ptr(x), get_ptr(z)))
  if (dim(x) == 2) {
    return(intersection_point(r, r2))
  }
  r3 <- new_geometry_vector(geometry_radical_geometry(get_ptr(y), get_ptr(z)))
  intersection_point(intersection_line(r, r2), r3)
}
