#' Calculate intersections between geometries
#'
#' An intersection between two geometries is defined as the geometry that is
#' contained in both geometries. In other words all points laying on the
#' intersection is also part of the two incoming geometries. It follows that the
#' result of calculating intersections can be varied, even between the same
#' combination of geometries. For example, The intersection between a triangle
#' and a plane can be `NULL`, a point, a segment, or a triangle depending on
#' their relative position and orientation. Because of this, and to avoid
#' confusion around the return type `intersection()` always return a list of
#' scalar geometries or `NULL`s. Intersections can only be calculated between
#' geometries located in space, which rules out vectors and directions. Further,
#' not all combinations of geometries have exact intersections defined (circles
#' and spheres are especially limited).
#'
#' @param x,y Geometry vectors
#'
#' @return a list of scalar geometry vectors and `NULL`s depending on the result
#' of the intersection query.
#'
#' @export
#'
#' @examples
#' # Example of the difference in output
#' t <- triangle(point(0, 0), point(1, 1), point(0, 1))
#' l <- line(1, -1, c(0, 1, 2))
#' intersection(t, l)
#'
#' # Input is symmetric
#' intersection(l, t)
#'
intersection <- function(x, y) {
  if (!is_geometry(x) || !is_geometry(y)) {
    rlang::abort("intersection can only be calculated between two geometries")
  }
  lapply(geometry_intersection(get_ptr(x), get_ptr(y)), function(g) {
    if (is.null(g)) return(g)
    new_geometry_vector(g)
  })
}
