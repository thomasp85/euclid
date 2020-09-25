#' Vector of vectors
#'
#' A geometrical vector is somewhat different from the concept of a vector in
#' programming hence the slightly confusing terminology. In geometry a vector is
#' a direction and a magnitude most often defined by a point in space where the
#' direction is defined as the direction from the origin to the point and the
#' magnitude is defined as the distance from the origin to the point.
#'
#' @param ... Various input. See the Constructor section.
#' @param default_dim The dimensionality when constructing an empty vector
#' @param x A vector of vectors or an object to convert to it
#'
#' @return An `euclid_vector` vector
#'
#' @section Constructors:
#' **2 dimensional vectors**
#' - Providing a point will construct vectors pointing to the points from the
#'   origin centered.
#' - Providing two exact numeric vectors will construct vectors pointing to the
#'   point defined by the coordinates given.
#'
#' **3 dimensional vectors**
#' - Providing a point will construct vectors pointing to the points from the
#'   origin centered.
#' - Providing three exact numeric vectors will construct vectors pointing to
#'   the point defined by the coordinates given.
#'
#' @export
vec <- function(..., default_dim = 2) {
  inputs <- validate_constructor_input(...)

  if (length(inputs) == 0) {
    return(new_vector_empty(default_dim))
  }

  points <- inputs[vapply(inputs, is_point, logical(1))]
  numbers <- inputs[vapply(inputs, is_exact_numeric, logical(1))]

  if (length(points) == 1) {
    new_vector_from_point(points[[1]])
  } else if (length(numbers) == 2) {
    new_vector_from_xy(numbers[[1]], numbers[[2]])
  } else if (length(numbers) == 3) {
    new_vector_from_xyz(numbers[[1]], numbers[[2]], numbers[[3]])
  } else {
    rlang::abort("Don't know how to construct vectors from the given input")
  }
}
#'
#' @rdname vec
#' @export
is_vec <- function(x) inherits(x, "euclid_vector")

# Conversion --------------------------------------------------------------

#' @rdname vec
#' @export
as_vec <- function(x) {
  UseMethod("as_vec")
}
#' @export
as_vec.default <- function(x) {
  rlang::abort("Don't know how to convert the input to vectors")
}
#' @export
as_vec.euclid_vector <- function(x) x

#' @export
as_point.euclid_vector <- function(x) {
  point(x)
}

# Operators ---------------------------------------------------------------

#' @export
geometry_op_plus.euclid_vector <- function(e1, e2) {
  if (!is_vec(e1) || !is_vec(e2)) {
    rlang::abort("`+` is only defined for addition with another vector")
  }
  if (dim(e1) != dim(e2)) {
    rlang::abort("`e1` and `e2` must have the same number of dimensions")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(new_vector_empty(dim(e1)))
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(vector_2_add_vector(get_ptr(e1), get_ptr(e2)), e1)
  } else {
    restore_euclid_vector(vector_3_add_vector(get_ptr(e1), get_ptr(e2)), e1)
  }
}
#' @export
geometry_op_minus.euclid_vector <- function(e1, e2) {
  if (missing(e2)) {
    if (dim(e1) == 2) {
      restore_euclid_vector(vector_2_negate(get_ptr(e1)), e1)
    } else {
      restore_euclid_vector(vector_3_negate(get_ptr(e1)), e1)
    }
  } else {
    if (!is_vec(e1) || !is_vec(e2)) {
      rlang::abort("`-` is only defined for subtraction with another vector")
    }
    if (dim(e1) != dim(e2)) {
      rlang::abort("`e1` and `e2` must have the same number of dimensions")
    }
    if (length(e1) == 0 || length(e2) == 0) {
      return(new_vector_empty(dim(e1)))
    }
    if (dim(e1) == 2) {
      restore_euclid_vector(vector_2_minus_vector(get_ptr(e1), get_ptr(e2)), e1)
    } else {
      restore_euclid_vector(vector_3_minus_vector(get_ptr(e1), get_ptr(e2)), e1)
    }
  }
}
#' @export
geometry_op_multiply.euclid_vector <- function(e1, e2) {
  if (length(e1) == 0 || length(e2) == 0) {
    return(new_vector_empty(dim(e1)))
  }
  if (is_vec(e1)) {
    vec <- e1
    number <- as_exact_numeric(e2)
  } else {
    vec <- e2
    number <- as_exact_numeric(e1)
  }
  if (dim(e1) == 2) {
    restore_euclid_vector(vector_2_times_numeric(get_ptr(vec), get_ptr(number)), vec)
  } else {
    restore_euclid_vector(vector_3_times_numeric(get_ptr(vec), get_ptr(number)), vec)
  }
}
#' @export
geometry_op_divide.euclid_vector <- function(e1, e2) {
  if (!is_vec(e1)) {
    rlang::abort("Vector must be the nominator in division")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    return(new_vector_empty(dim(e1)))
  }
  e2 <- as_exact_numeric(e2)
  if (dim(e1) == 2) {
    restore_euclid_vector(vector_2_divide_numeric(get_ptr(e1), get_ptr(e2)), vec)
  } else {
    restore_euclid_vector(vector_3_divide_numeric(get_ptr(e1), get_ptr(e2)), vec)
  }
}

# Summaries ---------------------------------------------------------------

#' @export
geometry_summary_sum.euclid_vector <- function(x, na_rm) {
  if (dim(x) == 2) {
    vector_2_sum(get_ptr(x), na_rm)
  } else {
    vector_3_sum(get_ptr(x), na_rm)
  }
}

# Math --------------------------------------------------------------------

#' @export
geometry_math_cumsum.euclid_vector <- function(x) {
  if (dim(x) == 2) {
    vector_2_cumsum(get_ptr(x))
  } else {
    vector_3_cumsum(get_ptr(x))
  }
}

# Internal Constructors ---------------------------------------------------

new_vector2 <- function(x) {
  new_geometry_vector(x, class = c("euclid_vector2", "euclid_vector"))
}
new_vector3 <- function(x) {
  new_geometry_vector(x, class = c("euclid_vector3", "euclid_vector"))
}
new_vector_empty <- function(dim) {
  if (dim == 2) {
    new_vector2(create_vector_2_empty())
  } else {
    new_vector3(create_vector_3_empty())
  }
}
new_vector_from_point <- function(p) {
  if (dim(p) == 2) {
    new_vector2(create_vector_2_point(get_ptr(p)))
  } else {
    new_vector3(create_vector_3_point(get_ptr(p)))
  }
}
new_vector_from_xy <- function(x, y) {
  new_vector2(create_vector_2_x_y(get_ptr(x), get_ptr(y)))
}
new_vector_from_xyz <- function(x, y, z) {
  new_vector3(create_vector_3_x_y_z(get_ptr(x), get_ptr(y), get_ptr(z)))
}
