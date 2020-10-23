#' Exact numeric representation
#'
#' In order to have exact geometric computations it is necessary to avoid the
#' issues of floating point arithmetic. CGAL can work with a range of different
#' exact kernels, where euclid uses the `Exact_predicates_exact_constructions`
#' predifined kernel. Moving values in and out of R would force a conversion to
#' double thus destroying the exactness of computation, so euclid provides a new
#' numeric vector class that simply maps to the underlying exact representation.
#' While the exact numeric class generally behaves as a standard numeric there
#' are operations that are not possible because it will loose the exactness,
#' e.g. trigonometric functions, roots, etc. If any unsupported function is
#' needed it is necessary to convert back to numeric (thus loosing exactness).
#' Anywhere euclid takes a numeric input it will convert it to an exact numeric
#' before use.
#'
#' @param x An object coercible to `numeric`
#'
#' @return An `euclid_exact_numeric` vector
#'
#' @note Exact numeric only have one form of non-finite value: `NA`. Any other
#' non-finite value will be converted to that.
#'
#' @export
#'
#' @examples
#' # Standard use
#' exact_numeric(runif(5))
#'
#' # Non-finite numbers are all converted to NA
#' exact_numeric(NaN)
#'
#' # this is also true for division by zero
#' exact_numeric(runif(5)) / 0
#'
#' # Exact numerics are more limited on operations but doesn't have the
#' # weirdness of floating point arithmetic:
#' float <- c(1, 2, 3)
#' identical(float[1] + float[2], float[3])
#' float <- float / 10
#' identical((float[1] + float[2]) * 10, float[3] * 10)
#'
#' exact <- exact_numeric(c(1, 2, 3))
#' identical(as.numeric(exact[1] + exact[2]), as.numeric(exact[3]))
#' exact <- exact / 10
#' identical(as.numeric((exact[1] + exact[2]) * 10), as.numeric(exact[3] * 10))
#'
#' # This only holds if the input are exact to begin with
#' identical(
#'   as.numeric(exact_numeric(1/10 + 2/10)),
#'   as.numeric(exact_numeric(3/10))
#' )
#'
exact_numeric <- function(x = numeric(0)) {
  new_exact_numeric(create_exact_numeric(as.numeric(x)))
}
new_exact_numeric <- function(x) {
  x <- list(x)
  class(x) <- "euclid_exact_numeric"
  x
}
#' @rdname exact_numeric
#' @export
is_exact_numeric <- function(x) inherits(x, "euclid_exact_numeric")
#' @rdname exact_numeric
#' @export
as_exact_numeric <- function(x) {
  if (is_exact_numeric(x)) return(x)
  exact_numeric(x)
}
#' @export
as.double.euclid_exact_numeric <- function(x, ...) {
  exact_numeric_to_numeric(get_ptr(x))
}
#' @export
as.character.euclid_exact_numeric <- function(x, ...) {
  format(x, ...)
}
#' @export
as.list.euclid_exact_numeric <- function(x, ...) {
  lapply(seq_along(x), function(i) x[i])
}
#' @export
format.euclid_exact_numeric <- function(x, ...) {
  format(as.double(x), ...)
}
#' @export
print.euclid_exact_numeric <- function(x, ...) {
  cat("<Vector of exact numerics>\n")
  if (length(x) == 0) {
    cat("[empty]")
  } else {
    print(format(x, ...), quote = FALSE)
  }
  invisible(x)
}
#' @importFrom utils str
#' @export
str.euclid_exact_numeric <- function(object, ...) {
  show <- min(5, length(object))
  if (length(object) == 0) {
    cat("exact num [0]")
  } else {
    cat(
      "exact num [1:", length(object), "] ",
      paste(format(object)[seq_len(show)], collapse = " "),
      if (show < length(object)) " ..." else "",
      sep = ""
    )
  }
  invisible(object)
}
#' @export
length.euclid_exact_numeric <- function(x) {
  exact_numeric_length(get_ptr(x))
}
#' @export
rep.euclid_exact_numeric <- function(x, ...) {
  index <- rep(seq_along(x), ...)
  x[index]
}
#' @export
diff.euclid_exact_numeric <- function(x, lag = 1L, difference = 1L, ...) {
  result <- exact_numeric_diff(get_ptr(x), as.integer(lag)[1])
  for (i in seq_len(difference - 1L)) {
    result <- exact_numeric_diff(result, as.integer(lag)[1])
  }
  restore_euclid_vector(result, x)
}
#' @export
sort.euclid_exact_numeric <- function(x, decreasing = FALSE, na.last = NA, ...) {
  restore_euclid_vector(exact_numeric_sort(get_ptr(x), decreasing, na.last), x)
}
#' @export
`[.euclid_exact_numeric` <- function(x, i, j, ..., drop = TRUE) {
  index <- seq_along(x)[i]
  restore_euclid_vector(exact_numeric_subset(get_ptr(x), index), x)
}
#' @export
`[[.euclid_exact_numeric` <- function(x, i) {
  if (length(i) != 1) {
    rlang::abort("attempt to select more than one element in vector")
  }
  x[i]
}
#' @export
`[<-.euclid_exact_numeric` <- function(x, i, j, ..., value) {
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
  value <- rep_len(as_exact_numeric(value), length(index))
  restore_euclid_vector(exact_numeric_assign(get_ptr(x), index, get_ptr(value)), x)
}
#' @export
`[[<-.euclid_exact_numeric` <- function(x, i, value) {
  if (length(i) != 1) {
    rlang::abort("attempt to assign to more than one element in vector")
  }
  x[i] <- value
  x
}
#' @export
`$.euclid_exact_numeric` <- function(x, name) {
  rlang::abort("`$` is not defined for exact numerics")
}
#' @export
`$<-.euclid_exact_numeric` <- function(x, name, value) {
  rlang::abort("`$<-` is not defined for exact numerics")
}
#' @export
c.euclid_exact_numeric <- function(..., recursive = FALSE) {
  input <- lapply(list(...), function(x) get_ptr(as_exact_numeric(x)))
  res <- exact_numeric_combine(input[[1]], input[-1])
  restore_euclid_vector(res, ..1)
}
#' @export
is.na.euclid_exact_numeric <- function(x) {
  exact_numeric_is_na(get_ptr(x))
}
#' @export
`is.na<-.euclid_exact_numeric` <- function(x, value) {
  x[is.na(x)] <- value
  x
}
#' @export
anyNA.euclid_exact_numeric <- function(x, recursive) {
  exact_numeric_any_na(get_ptr(x))
}
#' @export
as.data.frame.euclid_exact_numeric <- function(x, row.names = NULL, optional = FALSE, ...) {
  df <- list(x)
  class(df) <- "data.frame"
  attr(df, "row.names") <- .set_row_names(length(x))
  df
}
#' @export
unique.euclid_exact_numeric <- function(x, incomparables = FALSE, ...) {
  restore_euclid_vector(exact_numeric_unique(get_ptr(x)), x)
}
#' @export
duplicated.euclid_exact_numeric <- function(x, incomparables = FALSE, ...) {
  exact_numeric_duplicated(get_ptr(x))
}
#' @export
anyDuplicated.euclid_exact_numeric <- function(x, incomparables = FALSE, ...) {
  exact_numeric_any_duplicated(get_ptr(x))
}
#' @export
xtfrm.euclid_exact_numeric <- function(x) {
  exact_numeric_rank(get_ptr(x))
}
match_exact_numeric <- function(x, table) {
  exact_numeric_match(get_ptr(x), get_ptr(as_exact_numeric(table)))
}
#' @export
range.euclid_exact_numeric <- function(..., na.rm = FALSE) {
  input <- do.call(c, list(...))
  c(min(input, na.rm = na.rm), max(input, na.rm = na.rm))
}

#' @export
Ops.euclid_exact_numeric <- function(e1, e2) {
  if (.Generic == "/" && (is_vec(e1) || is_vec(e2))) {
    return(geometry_op_divide(e1, e2))
  }
  e1 <- as_exact_numeric(e1)
  if (!missing(e2)) e2 <- as_exact_numeric(e2)
  if ((length(e1) == 0 && missing(e2)) || (length(e1) == 0 || (!missing(e2) && length(e2) == 0))) {
    if (.Generic %in% c("+", "-", "*", "/")) {
      return(exact_numeric())
    } else {
      return(logical(0))
    }
  }
  res <- switch(.Generic,
    "+" = exact_numeric_plus(get_ptr(e1), get_ptr(e2)),
    "-" = if (missing(e2)) exact_numeric_uni_minus(get_ptr(e1)) else exact_numeric_minus(get_ptr(e1), get_ptr(e2)),
    "*" = exact_numeric_times(get_ptr(e1), get_ptr(e2)),
    "/" = exact_numeric_divided(get_ptr(e1), get_ptr(e2)),
    "==" = exact_numeric_is_equal(get_ptr(e1), get_ptr(e2)),
    "!=" = !exact_numeric_is_equal(get_ptr(e1), get_ptr(e2)),
    "<" = exact_numeric_less(get_ptr(e1), get_ptr(e2)),
    "<=" = !exact_numeric_greater(get_ptr(e1), get_ptr(e2)),
    ">" = exact_numeric_greater(get_ptr(e1), get_ptr(e2)),
    ">=" = !exact_numeric_less(get_ptr(e1), get_ptr(e2)),
    rlang::abort(paste0("The `", .Generic, "` operator is not defined for exact numerics"))
  )
  if (.Generic %in% c("+", "-", "*", "/")) {
    res <- restore_euclid_vector(res, e1)
  }
  res
}

#' @export
Math.euclid_exact_numeric <- function(x, ...) {
  res <- switch(.Generic,
    "abs" = exact_numeric_abs(get_ptr(x)),
    "sign" = exact_numeric_sign(get_ptr(x)),
    "cumsum" = exact_numeric_cumsum(get_ptr(x)),
    "cumprod" = exact_numeric_cumprod(get_ptr(x)),
    "cummin" = exact_numeric_cummin(get_ptr(x)),
    "cummax" = exact_numeric_cummax(get_ptr(x)),
    rlang::abort(paste0("The `", .Generic, "()` function is not defined for exact numerics"))
  )
  if (.Generic != "sign") {
    res <- restore_euclid_vector(res, x)
  }
  res
}

#' @export
Summary.euclid_exact_numeric <- function(..., na.rm) {
  na.rm = isTRUE(na.rm)
  input <- do.call(c, lapply(list(...), as_exact_numeric))
  res <- switch(.Generic,
    "sum" = exact_numeric_sum(get_ptr(input), na.rm),
    "prod" = exact_numeric_prod(get_ptr(input), na.rm),
    "min" = exact_numeric_min(get_ptr(input), na.rm),
    "max" = exact_numeric_max(get_ptr(input), na.rm)
  )
  restore_euclid_vector(res, input)
}
