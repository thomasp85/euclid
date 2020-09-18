new_geometry_vector <- function(x, class) {
  x <- list(x)
  class(x) <-  c(class, "euclid_geometry")
  x
}
restore_geometry_vector <- function(x, old) {
  x <- list(x)
  attributes(x) <- attributes(old)
  x
}

#' @export
is_geometry <- function(x) inherits(x, "euclid_geometry")

#' @export
format.euclid_geometry <- function(x, ...) {
  geometry_format(get_ptr(x))
}
#' @export
length.euclid_geometry <- function(x) {
  geometry_length(get_ptr(x))
}
#' @export
print.euclid_geometry <- function(x, ...) {
  cat("<Vector of ", sub("euclid_(.*)\\d", "\\1", class(x)[1]), "s in ", dim(x), " dimensions>\n", sep = "")
  print(format(x), quote = FALSE)
  invisible(x)
}
#' @export
dim.euclid_geometry <- function(x) {
  geometry_dimension(get_ptr(x))
}
#' @export
`[[.euclid_geometry` <- function(x, i) {
  index <- seq_along(x)[i]
  restore_geometry_vector(geometry_subset(get_ptr(x), index), x)
}
#' @export
`[.euclid_geometry` <- function(x, i, j, ..., drop = TRUE) {
  x[[i]]
}

get_ptr <- function(x) .subset2(x, 1L)
