#' Vector of geometries
#'
#' The base vector type for geometries in euclid is the `euclid_geometry` class.
#' While this is a virtual class (you cannot construct it, only its subclasses),
#' many of the common vector operations are defined here. Further it is possible
#' to check whether a vector is a geometry of any type using `is_geometry()`.
#' While most geometries are atomic, a few are defined by multiples of the same
#' geometry, e.g. segments and triangles which are defined by 2 and 3 points
#' respectively. The cardinality of each geometry in a vector can be queried
#' with `cardinality()`. The matrix conversion will place each sub-geometry of
#' a geometry on a new row, meaning that the final number of rows in a matrix
#' constructed from `x` is not `length(x)` but `sum(cardinality(x))`.
#'
#' @param x An `euclid_geometry` object
#'
#' @section Vector behaviour:
#' Geometry vectors in euclid are made to behave as closely as possible to what
#' you expect from normal R vectors. However, they are implemented as external
#' pointers to the exact C representation meaning that they cannot be restored
#' across sessions or saved to RData/RDS files. Despite being external pointers
#' they mimick R's copy-on-modify semantics so you should not worry about side
#' effects when changing a geometry vector. Further, since [exact_numeric]
#' vectors only supports finite values, geometry vectors do not have an `NA`
#' value.
#'
#' The following is a list of standard R methods defined for geometry
#' vectors:
#' - [as.matrix()] - converts the geometry to a standard R matrix of numerics
#' - [as.character()] - provides a textual representation of the geometry
#' - [format()] - as above
#' - [as.list()] - splits the vector into single elements in a list
#' - [str()] - provides a condensed view of the vector
#' - [length()] - gives the number of geometries in the vector
#' - [rep()] - replicates elements in the vector
#' - [dim()] - gives the dimensionality of the geometry (2 or 3)
#' - [`[`] and [`[[`] - extract elements from the vector
#' - [`[<-`] and [`[[<-`] - assigns elements into the vector. Since `NA` values
#'   are not supported it is not possible to assign past the length of the
#'   vector
#' - [`$`] and [`$<-`] - will throw an error since geometry vectors are unnamed
#' - [c()] - combine multiple geometries of the same type
#' - [unique()] - returns the unique elements of the vector keeping the order
#' - [duplicated()] - gives whether an element has been seen before in the
#'   vector
#' - [anyDuplicated()] - Tells if any element in the vector is a duplicate
#' - [`==`] and [`!=`] - Test for equality between elements.
#' - [transform()] - Transform geometries in the vector according to an
#'   [affine_transformation]
#'
#' Do note that since geometries with exact representation is not easily
#' hashable, the implementation of `unique()` and `duplicated()` is not very
#' efficient.
#'
#' @name euclid_geometry
#' @rdname euclid_geometry
#'
NULL

new_geometry_vector <- function(x, class) {
  x <- list(x)
  class(x) <-  c(class, "euclid_geometry")
  x
}

#' @rdname euclid_geometry
#' @export
is_geometry <- function(x) inherits(x, "euclid_geometry")

#' @rdname euclid_geometry
#' @export
cardinality <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("Cardinality can only be calculated for euclid geometry objects")
  }
  geometry_cardinality(get_ptr(x))
}
#' @rdname euclid_geometry
#' @export
definition_names <- function(x) {
  geometry_definition_names(get_ptr(x))
}
#' @export
as.matrix.euclid_geometry <- function(x, ...) {
  geometry_to_matrix(get_ptr(x))
}
#' @export
as.character.euclid_geometry <- function(x, ...) {
  format(x, ...)
}
#' @export
as.list.euclid_geometry <- function(x, ...) {
  lapply(seq_along(x), function(i) x[i])
}
#' @export
format.euclid_geometry <- function(x, ...) {
  geometry_format(get_ptr(x))
}
#' @export
print.euclid_geometry <- function(x, ...) {
  cat("<Vector of ", sub("euclid_(.*)\\d", "\\1", class(x)[1]), "s in ", dim(x), " dimensions>\n", sep = "")
  if (length(x) == 0) {
    cat("[empty]")
  } else {
    print(format(x), quote = FALSE)
  }
  invisible(x)
}
#' @importFrom utils str
#' @export
str.euclid_geometry <- function(object, ...) {
  show <- min(5, length(object))
  cat(
    sub("euclid_(.*)\\d", "\\1", class(object)[1]), "{", dim(object), "}",
    if (length(object) == 0) " [0]" else paste0(" [1:", length(object), "] "),
    if (length(object) == 0) "" else paste(format(object)[seq_len(show)], collapse = " "),
    if (show < length(object)) " ..." else "",
    sep = ""
  )
  invisible(object)
}
#' @export
length.euclid_geometry <- function(x) {
  geometry_length(get_ptr(x))
}
#' @export
rep.euclid_geometry <- function(x, ...) {
  index <- rep(seq_along(x), ...)
  x[index]
}
#' @export
dim.euclid_geometry <- function(x) {
  geometry_dimension(get_ptr(x))
}
#' @export
`[.euclid_geometry` <- function(x, i, j, ..., drop = TRUE) {
  index <- seq_along(x)[i]
  restore_euclid_vector(geometry_subset(get_ptr(x), index), x)
}
#' @export
`[[.euclid_geometry` <- function(x, i) {
  if (length(i) != 1) {
    rlang::abort("attempt to select more than one element in vector")
  }
  x[i]
}
#' @export
`[<-.euclid_geometry` <- function(x, i, j, ..., value) {
  if (!is_geometry(value)) {
    rlang::abort("Only geometries can be assigned to geometry vectors")
  }
  if (is.numeric(i) && all(i >= 0)) {
    index <- seq_len(max(i))[i]
  } else {
    index <- seq_along(x)[i]
  }
  if (length(index) == 0) {
    return(x)
  }
  if (anyNA(index)) {
    rlang::abort("Trying to assign to non-existing element")
  }
  value <- rep_len(value, length(index))
  restore_euclid_vector(geometry_assign(get_ptr(x), index, get_ptr(value)), x)
}
#' @export
`[[<-.euclid_geometry` <- function(x, i, value) {
  if (length(i) != 1) {
    rlang::abort("attempt to assign to more than one element in vector")
  }
  x[i] <- value
  x
}
#' @export
`$.euclid_geometry` <- function(x, name) {
  rlang::abort("`$` is not defined for geometries")
}
#' @export
`$<-.euclid_geometry` <- function(x, name, value) {
  rlang::abort("`$<-` is not defined for geometries")
}
#' @export
c.euclid_geometry <- function(..., recursive = FALSE) {
  input <- list(...)
  if (any(!vapply(input, inherits, logical(1), class(input[[1]])[1]))) {
    rlang::abort("Geometries can only be combined with other geometries of the same type")
  }
  input <- lapply(input, get_ptr)
  res <- geometry_combine(input[[1]], input[-1])
  restore_euclid_vector(res, ..1)
}
#' @export
is.na.euclid_geometry <- function(x) {
  geometry_is_na(get_ptr(x))
}
#' @export
`is.na<-.euclid_geometry` <- function(x, value) {
  x[is.na(x)] <- value
  x
}
#' @export
anyNA.euclid_geometry <- function(x, recursive) {
  geometry_any_na(get_ptr(x))
}
#' @export
as.data.frame.euclid_geometry <- function(x, row.names = NULL, optional = FALSE, ...) {
  df <- list(x)
  class(df) <- "data.frame"
  attr(df, "row.names") <- .set_row_names(length(x))
  df
}
#' @export
unique.euclid_geometry <- function(x, incomparables = FALSE, ...) {
  restore_euclid_vector(geometry_unique(get_ptr(x)), x)
}
#' @export
duplicated.euclid_geometry <- function(x, incomparables = FALSE, ...) {
  geometry_duplicated(get_ptr(x))
}
#' @export
anyDuplicated.euclid_geometry <- function(x, incomparables = FALSE, ...) {
  geometry_any_duplicated(get_ptr(x))
}
match_geometry <- function(x, table) {
  geometry_match(get_ptr(x), get_ptr(table))
}
#' @export
sort.euclid_geometry <- function(x, decreasing = FALSE, ...) {
  rlang::abort("Sorting is not supported for the geometry type")
}
#' @export
xtfrm.euclid_geometry <- function(x) {
  rlang::abort("Ranking is not supported for the geometry type")
}
#' @export
transform.euclid_geometry <- function(`_data`, transformation, ...) {
  transformation <- as_affine_transformation(transformation)
  restore_euclid_vector(geometry_transform(get_ptr(`_data`), get_ptr(transformation)), `_data`)
}
