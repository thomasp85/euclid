#' Vector of points
#'
#' Points are the fundamental unit in geometry, from which other geometric
#' primitives can be constructed. Points support less than and greater than
#' operations which are handled lexicographically. This means that point vectors
#' can also be sorted and ranked. Subtracking a point from a point gives a
#' vector. Adding and subtracting a vector to a point translates the point by
#' the vector.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A point vector or an object to convert to it
#'
#' @return a `euclid_point` vector
#'
#' @section Constructors:
#' **2 dimensional points**
#' - Providing two numeric vector will construct points with those x and y
#'   coordinate.
#' - Providing a vector will construct a point at the location the vector
#'   points to.
#' - Providing a weighted point vector will create a points at the same
#'   locations without weights.
#'
#' **3 dimensional points**
#' - Providing three numeric vector will construct points with those x, y, and z
#'   coordinate.
#' - Providing a vector will construct a point at the location the vector
#'   points to.
#' - Providing a weighted point vector will create a points at the same
#'   locations without weights.
#'
#' @export
#'
#' @examples
#' num1 <- exact_numeric(runif(5))
#' num2 <- exact_numeric(runif(5))
#' num3 <- exact_numeric(runif(5))
#'
#' # 2 dimensions
#' p <- point(num1, num2)
#' p
#'
#' plot(p)
#'
#' # 3 dimensions
#' point(num1, num2, num3)
#'
#' # Standard R vectors are automatically converted to exact_numeric vectors
#' point(runif(5), runif(5))
#'
#' # Convert points to vectors
#' as_vec(p)
#'
#' # Arithmetic
#' # Translate by adding vector
#' p + vec(3, 7)
#'
#' # Create vector by subtracting points
#' p[1:2] - p[3:4]
#'
#' # Sorting etc.
#' sort(p)
#' min(p)
#' cummax(p)
#' rank(p)
#' p[1:2] < p[3:4]
#'
point <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_point_empty(default_dim))
  }

  vectors <- inputs[vapply(inputs, is_vec, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]
  w_points <- inputs[vapply(inputs, is_weighted_point, logical(1))]

  if (length(vectors) == 1) {
    new_point_from_vec(vectors[[1]])
  } else if (length(w_points) == 1) {
    new_point_from_wp(w_points[[1]])
  } else if (length(numbers) == 2) {
    new_point_from_xy(numbers[[1]], numbers[[2]])
  } else if (length(numbers) == 3) {
    new_point_from_xyz(numbers[[1]], numbers[[2]], numbers[[3]])
  } else {
    rlang::abort("Don't know how to construct points from the given input")
  }
}
#' @rdname point
#' @export
is_point <- function(x) inherits(x, "euclid_point")


# Conversion --------------------------------------------------------------

#' @rdname point
#' @export
as_point <- function(x) {
  UseMethod("as_point")
}
#' @export
as_point.default <- function(x) {
  rlang::abort("Don't know how to convert the input to points")
}
#' @export
as_point.euclid_point <- function(x) x

#' @export
as_vec.euclid_point <- function(x) {
  vec(x)
}

# Operators ---------------------------------------------------------------

#' @export
geometry_op_plus.euclid_point <- function(e1, e2) {
  if (!is_vec(e2)) {
    rlang::abort("`+` is only defined for vectors")
  }
  if (dim(e1) != dim(e2)) {
    rlang::abort("`e1` and `e2` must have the same number of dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(new_point_empty(dim(e1)))
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(point_2_add_vector(get_ptr(e1), get_ptr(e2)), e1)
  } else {
    restore_euclid_vector(point_3_add_vector(get_ptr(e1), get_ptr(e2)), e1)
  }
}
#' @export
geometry_op_minus.euclid_point <- function(e1, e2) {
  if (!is_vec(e2) && !is_point(e2)) {
    rlang::abort("`-` is only defined for vectors and points")
  }
  if (dim(e1) != dim(e2)) {
    rlang::abort("`e1` and `e2` must have the same number of dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    if (is_point(e2)) {
      return(new_vector_empty(dim(e1)))
    } else {
      return(new_point_empty(dim(e1)))
    }
  }
  if (dim(e1) == 2) {
    if (is_point(e2)) {
      new_geometry_vector(point_2_sub_point(get_ptr(e1), get_ptr(e2)))
    } else {
      restore_euclid_vector(point_2_sub_vector(get_ptr(e1), get_ptr(e2)), e1)
    }
  } else {
    if (is_point(e2)) {
      new_geometry_vector(point_3_sub_point(get_ptr(e1), get_ptr(e2)))
    } else {
      restore_euclid_vector(point_3_sub_vector(get_ptr(e1), get_ptr(e2)), e1)
    }
  }
}
#' @export
geometry_op_less.euclid_point <- function(e1, e2) {
  if (!is_point(e2)) {
    rlang::abort("`<` is only defined for points")
  }
  if (dim(e1) != dim(e2)) {
    rlang::abort("`e1` and `e2` must have the same number of dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(logical(0))
  }
  if (dim(e1) == 2) {
    point_2_less(get_ptr(e1), get_ptr(e2))
  } else {
    point_3_less(get_ptr(e1), get_ptr(e2))
  }
}
#' @export
geometry_op_greater.euclid_point <- function(e1, e2) {
  if (!is_point(e2)) {
    rlang::abort("`>` is only defined for points")
  }
  if (dim(e1) != dim(e2)) {
    rlang::abort("`e1` and `e2` must have the same number of dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(logical(0))
  }
  if (dim(e1) == 2) {
    point_2_greater(get_ptr(e1), get_ptr(e2))
  } else {
    point_3_greater(get_ptr(e1), get_ptr(e2))
  }
}

# Summaries ---------------------------------------------------------------

#' @export
geometry_summary_min.euclid_point <- function(x, na_rm) {
  if (dim(x) == 2) {
    point_2_min(get_ptr(x), na_rm)
  } else {
    point_3_min(get_ptr(x), na_rm)
  }
}
#' @export
geometry_summary_max.euclid_point <- function(x, na_rm) {
  if (dim(x) == 2) {
    point_2_max(get_ptr(x), na_rm)
  } else {
    point_3_max(get_ptr(x), na_rm)
  }
}

# Math --------------------------------------------------------------------

#' @export
geometry_math_cummin.euclid_point <- function(x) {
  if (dim(x) == 2) {
    point_2_cummin(get_ptr(x))
  } else {
    point_3_cummin(get_ptr(x))
  }
}
#' @export
geometry_math_cummax.euclid_point <- function(x) {
  if (dim(x) == 2) {
    point_2_cummax(get_ptr(x))
  } else {
    point_3_cummax(get_ptr(x))
  }
}

# Miscellaneous vector support --------------------------------------------

#' @export
sort.euclid_point <- function(x, decreasing = FALSE, na.last = NA, ...) {
  if (dim(x) == 2) {
    restore_euclid_vector(point_2_sort(get_ptr(x), decreasing, na.last), x)
  } else {
    restore_euclid_vector(point_3_sort(get_ptr(x), decreasing, na.last), x)
  }
}
#' @export
xtfrm.euclid_point <- function(x) {
  if (dim(x) == 2) {
    point_2_rank(get_ptr(x))
  } else {
    point_3_rank(get_ptr(x))
  }
}
#' @export
range.euclid_point <- function(..., na.rm = FALSE) {
  input <- do.call(c, list(...))
  c(min(input, na.rm = na.rm), max(input, na.rm = na.rm))
}

# Internal constructors ---------------------------------------------------

new_point_empty <- function(dim) {
  if (dim == 2) {
    new_geometry_vector(create_point_2_empty())
  } else {
    new_geometry_vector(create_point_3_empty())
  }
}
new_point_from_xy <- function(x, y) {
  new_geometry_vector(create_point_2_x_y(get_ptr(x), get_ptr(y)))
}
new_point_from_xyz <- function(x, y, z) {
  new_geometry_vector(create_point_3_x_y_z(get_ptr(x), get_ptr(y), get_ptr(z)))
}
new_point_from_vec <- function(p) {
  if (dim(p) == 2) {
    new_geometry_vector(create_point_2_vec(get_ptr(p)))
  } else {
    new_geometry_vector(create_point_3_vec(get_ptr(p)))
  }
}
new_point_from_wp <- function(p) {
  if (dim(p) == 2) {
    new_geometry_vector(create_point_2_wp(get_ptr(p)))
  } else {
    new_geometry_vector(create_point_3_wp(get_ptr(p)))
  }
}
