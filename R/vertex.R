#' Extract points from geometries
#'
#' Geometries located in space (all except directions and vectors), have one or
#' more points supporting it. Those can be extracted with `vertex()`. For
#' geometries with a cardinality above one there's a choice of which support
#' point to extract.
#'
#' @param x A vector of geometries
#' @param which An integer vector giving the vertex to extract in cases of
#' higher cardinality geometries
#'
#' @return A `euclid_point` vector matching the dimensionality of x
#'
#' @section Vertex definition:
#' For geometries that are defined exclusively by points the definition of the
#' output is straight forward, e.g. for triangles `vertex()` will extract one
#' of the corners depending on the value of `which`. For the other geometries
#' the output is defined according to the below:
#'
#' - **circles and spheres**: The vertex is the center
#' - **rays**: The vertex is the source
#' - **lines and planes**: The vertex is an arbitrary point on the geometry
#'
#' @export
#'
#' @examples
#' # Get the source vertex in a segment
#' s <- segment(point(3, 6), point(1, -7))
#' vertex(s, 1)
#'
#' # And the target
#' vertex(s, 2)
#'
#' # Arguments are recycled
#' vertex(s, c(1, 2))
#'
#' # Get a point on a line
#' vertex(line(4, 7, -1))
#'
vertex <- function(x, which = 1L) {
  if (!is_geometry(x)) {
    rlang::abort("`vertex()` is only defined for geometries")
  }
  which <- rep_len(as.integer(which), length(x))
  if (any(which > cardinality(x))) {
    rlang::abort("`which` cannot be larger than the cardinality of the geometry")
  }
  which <- which - 1L
  new_geometry_vector(geometry_vertex(get_ptr(x), which))
}
