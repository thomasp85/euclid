new_geometry_vector <- function(x, class) {
  x <- list(x)
  class(x) <-  c(class, "euclid_geometry")
  x
}

# @export
is_geometry <- function(x) inherits(x, "euclid_geometry")

#' @export
format.euclid_geometry <- function(x, ...) {
  geometry_format(get_ptr(x))
}
#' @importFrom utils str
#' @export
str.euclid_geometry <- function(object, ...) {
  show <- max(5, length(object))
  cat(
    sub("euclid_(.*)\\d", "\\1", class(object)[1]),
    " [1:", length(object), "] ",
    paste(format(object)[seq_len(show)], collapse = " "),
    if (show > 5) " ..." else "",
    sep = ""
  )
  invisible(object)
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
