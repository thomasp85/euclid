#' Vector of directions
#'
#' Directions are vectors where you have forgot about the length. They are used
#' mutch in the same way as normalised vectors (vectors with a magnitude of 1),
#' but since vectors cannot be normalized while maintaining exactness it is
#' preferable to simply have a data type where you ignore the magnitude. The
#' direction can be flipped by taking the negative. 2 dimensional directions can
#' be considered as angles and can thus be sorted and compared. The same is not
#' true for directions in 3 dimensions.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A direction vector or an object to convert to it
#' @param d1,d2 direction vectors to relate to
#'
#' @return a `euclid_direction` vector
#'
#' @section Constructors:
#' **2 and 3 dimensional directions**
#' - Providing 2 or 3 numerics will create directions with the given delta
#'   values. (2 numerics will give 2 dimensional directions, 3 will give 3
#'   dimensional directions).
#' - Providing vectors will construct directions as the direction of the given
#'   vectors.
#' - Providing lines will construct directions as the direction of the given
#'   lines.
#' - Providing rays will construct directions as the direction of the given
#'   rays.
#' - Providing segments will construct directions as the direction of the given
#'   segments.
#'
#' @export
#'
#' @examples
#' # Constructions
#' d <- direction(sample(10, 3), sample(10, 3))
#' d
#' plot(d, col = c("firebrick", "goldenrod", "steelblue"))
#'
#' # flipping the direction
#' -d
#'
#' # Relations
#' d[1] < d[2]
#'
#' min(d)
#'
#' sort(d)
#'
#' between(d[1], d[2], d[3])
#'
direction <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_direction_empty(default_dim))
  }

  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  lines <- inputs[vapply(inputs, is_line, logical(1))]
  rays <- inputs[vapply(inputs, is_ray, logical(1))]
  segments <- inputs[vapply(inputs, is_segment, logical(1))]

  if (length(numbers) == 3) {
    new_direction_from_x_y_z(numbers[[1]], numbers[[2]], numbers[[3]])
  } else if (length(numbers) == 2) {
    new_direction_from_x_y(numbers[[1]], numbers[[2]])
  } else if (length(vectors) == 1) {
    new_direction_from_vec(vectors[[1]])
  } else if (length(lines) == 1) {
    new_direction_from_line(lines[[1]])
  } else if (length(rays) == 1) {
    new_direction_from_ray(rays[[1]])
  } else if (length(segments) == 1) {
    new_direction_from_segment(segments[[1]])
  } else {
    rlang::abort("Don't know how to construct directions from the given input")
  }
}
#' @rdname direction
#' @export
is_direction <- function(x) inherits(x, "euclid_direction")

#' @rdname direction
#' @export
between <- function(x, d1, d2) {
  if (!is_direction(x) || !is_direction(d1) ||!is_direction(d2)) {
    rlang::abort("`between()` is only defined for directions")
  }
  if (dim(x) != 2 || dim(d1) != 2 || dim(d2) != 2) {
    rlang::abort("`between()` is only defined in 2 dimensions")
  }
  direction_2_between(get_ptr(x), get_ptr(d1), get_ptr(d2))
}

# Conversion --------------------------------------------------------------

#' @rdname direction
#' @export
as_direction <- function(x) {
  UseMethod("as_direction")
}
#' @export
as_direction.default <- function(x) {
  rlang::abort("Don't know how to convert the input to directions")
}
#' @export
as_direction.euclid_direction <- function(x) x

#' @export
as_vec.euclid_direction <- function(x) {
  vec(x)
}

# Operators ---------------------------------------------------------------

#' @export
geometry_op_minus.euclid_direction <- function(e1, e2) {
  if (!missing(e2)) {
    rlang::abort("Directions cannot be subtracted, only negated")
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(direction_2_negate(get_ptr(e1)), e1)
  } else {
    restore_euclid_vector(direction_3_negate(get_ptr(e1)), e1)
  }
}
#' @export
geometry_op_less.euclid_direction <- function(e1, e2) {
  if (!is_direction(e2)) {
    rlang::abort("`<` is only defined for directions")
  }
  if (dim(e1) != 2 || dim(e2) != 2) {
    rlang::abort("`<` is only defined in 2 dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(logical(0))
  }
  direction_2_less(get_ptr(e1), get_ptr(e2))
}
#' @export
geometry_op_greater.euclid_direction <- function(e1, e2) {
  if (!is_direction(e2)) {
    rlang::abort("`>` is only defined for directions")
  }
  if (dim(e1) != 2 || dim(e2) != 2) {
    rlang::abort("`>` is only defined in 2 dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(logical(0))
  }
  direction_2_greater(get_ptr(e1), get_ptr(e2))
}

# Summaries ---------------------------------------------------------------

#' @export
geometry_summary_min.euclid_direction <- function(x, na_rm) {
  if (dim(x) != 2) {
    rlang::abort("`min()` is only defined in 2 dimensions")
  }
  direction_2_min(get_ptr(x), na_rm)
}
#' @export
geometry_summary_max.euclid_direction <- function(x, na_rm) {
  if (dim(x) != 2) {
    rlang::abort("`max()` is only defined in 2 dimensions")
  }
  direction_2_max(get_ptr(x), na_rm)
}

# Math --------------------------------------------------------------------

#' @export
geometry_math_cummin.euclid_direction <- function(x) {
  if (dim(x) != 2) {
    rlang::abort("`cummin()` is only defined in 2 dimensions")
  }
  direction_2_cummin(get_ptr(x))
}
#' @export
geometry_math_cummax.euclid_direction <- function(x) {
  if (dim(x) != 2) {
    rlang::abort("`cummax()` is only defined in 2 dimensions")
  }
  direction_2_cummax(get_ptr(x))
}

# Miscellaneous vector support --------------------------------------------

#' @export
sort.euclid_direction <- function(x, decreasing = FALSE, na.last = NA, ...) {
  if (dim(x) != 2) {
    rlang::abort("`sort()` is only defined in 2 dimensions")
  }
  restore_euclid_vector(direction_2_sort(get_ptr(x), decreasing, na.last), x)
}
#' @export
xtfrm.euclid_direction <- function(x) {
  if (dim(x) != 2) {
    rlang::abort("ranking is only defined in 2 dimensions")
  }
  direction_2_rank(get_ptr(x))
}
#' @export
range.euclid_direction <- function(..., na.rm = FALSE) {
  input <- do.call(c, list(...))
  c(min(input, na.rm = na.rm), max(input, na.rm = na.rm))
}

# Internal Constructors ---------------------------------------------------

new_direction_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_direction_2_empty())
  } else {
    new_geometry_vector(create_direction_3_empty())
  }
}
new_direction_from_vec <- function(v) {
  if (dim(v) == 2) {
    new_geometry_vector(create_direction_2_vec(get_ptr(v)))
  } else {
    new_geometry_vector(create_direction_3_vec(get_ptr(v)))
  }
}
new_direction_from_line <- function(l) {
  if (dim(l) == 2) {
    new_geometry_vector(create_direction_2_line(get_ptr(l)))
  } else {
    new_geometry_vector(create_direction_3_line(get_ptr(l)))
  }
}
new_direction_from_ray <- function(r) {
  if (dim(r) == 2) {
    new_geometry_vector(create_direction_2_ray(get_ptr(r)))
  } else {
    new_geometry_vector(create_direction_3_ray(get_ptr(r)))
  }
}
new_direction_from_segment <- function(s) {
  if (dim(s) == 2) {
    new_geometry_vector(create_direction_2_segment(get_ptr(s)))
  } else {
    new_geometry_vector(create_direction_3_segment(get_ptr(s)))
  }
}
new_direction_from_x_y <- function(x, y) {
  new_geometry_vector(create_direction_2_xy(get_ptr(x), get_ptr(y)))
}
new_direction_from_x_y_z <- function(x, y, z) {
  new_geometry_vector(create_direction_3_xyz(get_ptr(x), get_ptr(y), get_ptr(z)))
}
