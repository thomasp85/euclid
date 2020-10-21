#' Project geometries to lines and planes
#'
#' Projecting geometries to lines and planes transforms the geometries to lie on
#' the given line or plane by movement orthogonal to the line or plane. The
#' geometry of the result of the projection is the same as the input. Not all
#' geometries can be projected to lines and planes. Specifically, iso rectangles
#' and iso cubes cannot do either and only 3 dimensional geometries can be
#' projected to a plane. Circles and spheres are special in the sense that no
#' ellipse and ellipsoid primitives exist. Because of this, projections will
#' retain the radius and circularity of the primitives despite this not being
#' geometrically sound. Projecting a 3D circle to a line will keep the
#' orientation of the circle, while projecting it to a plane will adopt the
#' orientation of the plane.
#'
#' @param x A vector of geometries to project or map
#' @param target A vector of lines or planes
#'
#' @return A vector of geometries of the same class as `x`
#'
#' @export
#'
#' @examples
#' # Project a collection of segments to a line
#' p <- point(sample(10), sample(10))
#' s <- segment(p[1:5], p[6:10])
#'
#' project(s, line(3, 1, -6))
#'
#' # Project a line to the x plane
#' project(line(point(3, 7, -3), point(-2, 6, 0)),
#'         plane(point(0, 0, 0), vec(1, 0, 0)))
#'
project <- function(x, target) {
  if (!is_geometry(x)) {
    rlang::abort("Only geometries can be projected")
  }
  if (dim(x) != dim(target)) {
    rlang::abort("geometry must have the same dimensionality as the projection target")
  }
  if (is_line(target)) {
    restore_euclid_vector(geometry_project_to_line(get_ptr(x), get_ptr(target)), x)
  } else if (is_plane(target)) {
    restore_euclid_vector(geometry_project_to_plane(get_ptr(x), get_ptr(target)), x)
  } else {
    rlang::abort("projection target must either be lines or planes")
  }
}

#' Map 3D geometries to 2D based on plane
#'
#' 3 dimensional geometries can be converted to 2 dimensions by mapping them to
#' a plane. Not all 3 dimensional geometries can be converted to 2 dimensions as
#' it requires for them to have a 2 dimensional counterpart. This rules out iso
#' cubes, planes, and tetrahedrons. Spheres are a special case that will get
#' converted to circles with the same radius. As no ellipsoid geometry exist
#' the plane of circles is ignored and mapping a 3D circles thus creates a 2D
#' circle of the same radius irrespective of the supporting plane of the circle.
#'
#' @param x A vector of geometries to project or map
#' @param target A vector of planes
#'
#' @return A vector of geometries in 2 dimensions
#'
#' @export
#'
#' @examples
#' # Map a 3D point cloud to a plane defined by three random points
#' p <- point(sample(10), sample(10), sample(10))
#' support <- p[sample(10, 3)]
#' map_to(p, plane(support[1], support[2], support[3]))
#'
map_to <- function(x, target) {
  if (!is_geometry(x)) {
    rlang::abort("Only geometries can be mapped to planes")
  }
  if (dim(x) != 3) {
    rlang::abort("Only 3 dimensional geometries can be mapped to planes")
  }
  if (!is_plane(target)) {
    rlang::abort("Only planes can be used as mapping target")
  }
  new_geometry_vector(geometry_map_to_plane(get_ptr(x), get_ptr(target)))
}
