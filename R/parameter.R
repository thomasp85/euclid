#' Access the exact values that defines the geometries
#'
#' This function gives access to the underlying values defining the geometries
#' in a vector. As such they return the same information as calling
#' [as.matrix()] on a geometry vector except the return value is kept as an
#' exact numeric and that you can extract from single elements if the
#' cardinality of the geometry exceeds 1.
#'
#' @param x A geometry vector
#' @param which Either a name or the index of the definition to extract, as
#' matched to `definition_names(x)`
#' @param element For geometries with a cardinality above 1, which element of
#' the geometry should the definition be extracted for. If `NA` the definition
#' for all elements will be returned and the length of the returned vector will
#' be `sum(cardinality(x))` (matching the return of `as.matrix(x)`)
#' @param i,j The row and column of the cell in the transformation to fetch.
#' @param ... parameters to pass on
#'
#' @return An exact_numeric vector
#'
#' @export
#'
#' @examples
#' # Get squared radius of circle
#' circ <- circle(point(4, 7), 25)
#' parameter(circ, "r2")
#'
#' # Get all the x values from the source of segments
#' s <- segment(point(sample(10, 4), sample(10, 4)),
#'              point(sample(10, 4), sample(10, 4)))
#' parameter(s, "x", 1L)
#'
#' # Get y for all subelements
#' parameter(s, "y")
#'
#' # Extract cell values from transformation matrices
#' m <- affine_rotate(c(pi/2, pi/3))
#' parameter(m, 1, 2)
#'
parameter <- function(x, ...) {
  UseMethod("parameter")
}
#' @rdname parameter
#' @export
parameter.euclid_geometry <- function(x, which, element = NA, ...) {
  def_names <- definition_names(x)
  if (length(which) != 1) {
    rlang::abort("It is only possible to select a single parameter at a time")
  }
  if (is.character(which)) {
    index <- match(which, def_names)
    if (is.na(index)) {
      rlang::abort(paste0(which, " does not name a parameter in the geometry"))
    }
  } else {
    index <- as.integer(which)
    if (is.na(index)) {
      rlang::abort(paste0("`which` must be either a character or a value convertible to an integer"))
    }
  }
  if (index < 1 || index > length(def_names)) {
    rlang::abort("`which` must match one of the definitions of the geometry")
  }
  if (!anyNA(element)) {
    element <- rep_len(element, length(x))
    if (any(element > cardinality(x))) {
      rlang::abort("Trying to use an element index larger than the geometry cardinality")
    }
  }
  new_exact_numeric(geometry_definition(get_ptr(x), index - 1L, element - 1L))
}
#' @rdname parameter
#' @export
parameter.euclid_affine_transformation <- function(x, i, j, ...) {
  n <- max(length(x), length(i), length(j))
  if (length(x) == 1) {
    x <- rep_len(x, n)
  }
  if (length(i) == 1) {
    i <- rep_len(i, n)
  }
  if (length(j) == 1) {
    j <- rep_len(j, n)
  }
  if (length(x) != length(i) || length(x) != length(j)) {
    rlang::abort("`x`, `i`, and `j` must be either scalars or of the same length")
  }
  new_exact_numeric(transform_definition(get_ptr(x), as.integer(i) - 1L, as.integer(j) - 1L))
}
