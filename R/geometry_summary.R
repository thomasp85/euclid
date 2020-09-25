geometry_summary_sum <- function(x, na_rm) {
  UseMethod("geometry_summary_sum")
}
#' @export
geometry_summary_sum.default <- function(x, na_rm) {
  rlang::abort("The provided geometry does not support `sum()`")
}
geometry_summary_prod <- function(x, na_rm) {
  UseMethod("geometry_summary_prod")
}
#' @export
geometry_summary_prod.default <- function(x, na_rm) {
  rlang::abort("The provided geometry does not support `prod()`")
}
geometry_summary_min <- function(x, na_rm) {
  UseMethod("geometry_summary_min")
}
#' @export
geometry_summary_min.default <- function(x, na_rm) {
  rlang::abort("The provided geometry does not support `min()`")
}
geometry_summary_max <- function(x, na_rm) {
  UseMethod("geometry_summary_max")
}
#' @export
geometry_summary_max.default <- function(x, na_rm) {
  rlang::abort("The provided geometry does not support `max()`")
}

#' @export
Summary.euclid_geometry <- function(..., na.rm) {
  na.rm = isTRUE(na.rm)
  input <- do.call(c, list(...))
  res <- switch(.Generic,
    "sum" = geometry_summary_sum(input, na.rm),
    "prod" = geometry_summary_prod(input, na.rm),
    "min" = geometry_summary_min(input, na.rm),
    "max" = geometry_summary_max(input, na.rm)
  )
  restore_euclid_vector(res, input)
}
