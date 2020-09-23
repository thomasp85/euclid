geometry_op_plus <- function(e1, e2) {
  UseMethod("geometry_op_plus")
}
#' @export
geometry_op_plus.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `+` operation")
  } else {
    geometry_op_plus(e2, e1)
  }
}
geometry_op_minus <- function(e1, e2) {
  UseMethod("geometry_op_minus")
}
#' @export
geometry_op_minus.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `-` operation")
  } else {
    geometry_op_minus(e2, e1)
  }
}
geometry_op_multiply <- function(e1, e2) {
  UseMethod("geometry_op_multiply")
}
#' @export
geometry_op_multiply.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `*` operation")
  } else {
    geometry_op_multiply(e2, e1)
  }
}
geometry_op_divide <- function(e1, e2) {
  UseMethod("geometry_op_divide")
}
#' @export
geometry_op_divide.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `/` operation")
  } else {
    geometry_op_divide(e2, e1)
  }
}
geometry_op_less <- function(e1, e2) {
  UseMethod("geometry_op_less")
}
#' @export
geometry_op_less.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `<` operation")
  } else {
    geometry_op_less(e2, e1)
  }
}
geometry_op_less_equal <- function(e1, e2) {
  UseMethod("geometry_op_less_equal")
}
#' @export
geometry_op_less_equal.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `<=` operation")
  } else {
    geometry_op_less_equal(e2, e1)
  }
}
geometry_op_greater <- function(e1, e2) {
  UseMethod("geometry_op_greater")
}
#' @export
geometry_op_greater.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `>` operation")
  } else {
    geometry_op_greater(e2, e1)
  }
}
geometry_op_greater_equal <- function(e1, e2) {
  UseMethod("geometry_op_greater_equal")
}
#' @export
geometry_op_greater_equal.default <- function(e1, e2) {
  if (is_geometry(e1)) {
    rlang::abort("The provided geometry does not define a `>=` operation")
  } else {
    geometry_op_greater_equal(e2, e1)
  }
}
#' @export
Ops.euclid_geometry <- function(e1, e2) {
  switch(.Generic,
    "==" = geometry_is_equal(get_ptr(e1), get_ptr(e2)),
    "!=" = geometry_is_not_equal(get_ptr(e1), get_ptr(e2)),
    "+" = geometry_op_plus(e1, e2),
    "-" = geometry_op_minus(e1, e2),
    "*" = geometry_op_multiply(e1, e2),
    "/" = geometry_op_divide(e1, e2),
    "<" = geometry_op_less(e1, e2),
    "<=" = geometry_op_less_equal(e1, e2),
    ">" = geometry_op_greater(e1, e2),
    ">=" = geometry_op_greater_equal(e1, e2),
    rlang::abort(paste0("The `", .Generic, "` operator is not defined for geometries"))
  )
}
