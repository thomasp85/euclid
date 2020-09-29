#' Create affine transformation matrices
#'
#' These functions allow you to create vectors of transformation matrices for
#' affine transformation in 2 or 3 dimensions. Transformation matrices are used
#' to apply transformations to geometries using [transform()]. Transformations
#' can be stacked by multiplying them together. This is generally more
#' performant than applying transformations one by one to geometries.
#' Transformations can be reversed by applying the inverse transformation to a
#' geometry. The inverse transformation matrix can be obtained using
#' `inverse()`. Affine transformation matrices have an additional column and row
#' compared to linear transformation matrices. This means that matrices for 2
#' dimensional transformations are 3x3 and matrices for 2 dimensional
#' transformations are 4x4. In both cases the last row will consist of 0's and a
#' final scaling factor (usually 1). Rotation is generally not possible to do
#' while maintaining exactness as sine and cosine cannot be calculate to
#' exactness. 3 dimensional rotation can either be done around an axis, around
#' a direction, or be defining specific angles of rotation for yaw, pitch, and
#' roll.
#'
#' @param dim The dimensionality of the transformation matrix
#' @param x An object that can be converted to an affine transformation matrix
#' vector. Matrices and arrays can be converted provided they have the correct
#' dimensions. List of matrices can be converted provided that all matrices have
#' the same dimensions and that the dimensions is correct
#' @param vec A vector of vectors or an object convertible to one
#' @param fac A scaling factor to apply
#' @param rho An angle in radians to rotate (counterclockwise)
#' @param axis For 3 dimensional rotation, which axis to rotate around
#' @param direction A direction vector or an object convertible to one
#' @param yaw,pitch,roll Angles in radians for yaw, pitch, and roll rotation.
#'
#' @return An `euclid_affine_transformation` vector
#'
#' @rdname affine_transformation
#' @name affine_transformation
NULL

#' @rdname affine_transformation
#' @export
affine_identity <- function(dim = 2L) {
  if (dim == 2) {
    new_affine_transformation2(create_transform_2_identity(1L))
  } else {
    new_affine_transformation3(create_transform_3_identity(1L))
  }
}
#' @rdname affine_transformation
#' @export
affine_matrix <- function(x) {
  if (is.matrix(x)) {
    x <- list(x)
  } else if (is.array(x)) {
    x_dim <- dim(x)
    if (length(dim) == 2) {
      x <- list(as.matrix(x))
    } else {
      if (length(x_dim) != 3) {
        rlang::abort("Only 3-dimensional arrays can be converted to transformation matrices")
      }
      m_size <- prod(x_dim[1:2])
      n <- length(x) / m_size
      x <- split(x, rep(n, each = m_size))
      x <- lapply(x, matrix, nrow = x_dim[1], ncol = x_dim[2])
    }
  }
  if (!all(vapply(x, is.matrix, logical(1)) || vapply(x, anyNA, logical(1)))) {
    rlang::abort("`x` must be a list of matrices or an object convertible to it")
  }
  dimensionality <- max(vapply(x, ncol, integer(1)))
  x <- lapply(x, function(x) {
    mode(x) <- "numeric"
    if (anyNA(x)) {
      return(matrix(NA_real_, ncol = dimensionality, nrow = dimensionality))
    }
    n_cols <- ncol(x)
    if (n_cols != dimensionality) {
      rlang::abort("Cannot provide a mix of dimensionalities")
    }
    if (n_cols != 3 && n_cols != 4) {
      rlang::abort("Only 2 and 3 dimensional transformation matrices supported")
    }
    if (nrow(x) == ncol(x) - 1) {
      x <- rbind(x, 0)
      x[length(x)] <- 1
    }
    if (ncol(x) != nrow(x)) {
      rlang::abort("Malformed transformation matrix")
    }
    x
  })
  if (dimensionality == 3) {
    new_affine_transformation2(create_transform_2_matrix(x))
  } else {
    new_affine_transformation3(create_transform_3_matrix(x))
  }
}
#' @rdname affine_transformation
#' @export
affine_translate <- function(vec) {
  vec <- as_vec(vec)
  if (dim(vec) == 2) {
    new_affine_transformation2(create_transform_2_translate(get_ptr(vec)))
  } else {
    new_affine_transformation3(create_transform_3_translate(get_ptr(vec)))
  }
}
#' @rdname affine_transformation
#' @export
affine_scale <- function(fac, dim = 2L) {
  fac <- as_exact_numeric(fac)
  if (dim == 2) {
    new_affine_transformation2(create_transform_2_scale(get_ptr(fac)))
  } else {
    new_affine_transformation3(create_transform_3_scale(get_ptr(fac)))
  }
}
#' @rdname affine_transformation
#' @export
affine_rotate <- function(rho, axis = NA, direction = NA, yaw = NA, pitch = NA, roll = NA) {
  if (isTRUE(is.na(axis)) && isTRUE(is.na(direction)) && isTRUE(is.na(yaw)) && isTRUE(is.na(pitch)) && isTRUE(is.na(roll))) {
    rho <- as_exact_numeric(rho)
    new_affine_transformation2(create_transform_2_rotate(get_ptr(rho)))
  } else {
    if (!isTRUE(is.na(axis))) {
      affine_rotate_axis(rho, axis)
    } else if (!isTRUE(is.na(direction))) {
      affine_rotate_direction(rho, direction)
    } else {
      affine_rotate_ypr(yaw, pitch, roll)
    }
  }
}
#' @rdname affine_transformation
#' @export
is_affine_transformation <- function(x) inherits(x, "euclid_affine_transformation")

# Conversion --------------------------------------------------------------

#' @rdname affine_transformation
#' @export
as_affine_transformation <- function(x) {
  UseMethod("as_affine_transformation")
}
#' @export
as_affine_transformation.euclid_affine_transformation <- function(x) {
  x
}
#' @export
as_affine_transformation.arrays <- function(x) {
  affine_matrix(x)
}
#' @export
as_affine_transformation.list <- function(x) {
  affine_matrix(x)
}
#' @export
as.array.euclid_affine_transformation <- function(x) {
  transform_to_array(get_ptr(x))
}
#' @export
as.character.euclid_affine_transformation <- function(x, ...) {
  format(x, ...)
}
#' @export
as.list.euclid_affine_transformation <- function(x) {
  array <- transform_to_array(get_ptr(x))
  x_dim <- dim(array)
  m_size <- prod(x_dim[1:2])
  n <- length(x) / m_size
  x <- split(x, rep(n, each = m_size))
  lapply(x, matrix, nrow = x_dim[1], ncol = x_dim[2])
}

# Vector basic ------------------------------------------------------------

#' @export
format.euclid_affine_transformation <- function(x, ...) {
  transform_format(get_ptr(x))
}
#' @export
print.euclid_affine_transformation <- function(x, ...) {
  cat("<Vector of affine transformation matrices in ", dim(x), " dimensions>\n", sep = "")
  if (length(x) == 0) {
    cat("[empty]")
  } else {
    print(format(x, ...), quote = FALSE)
  }
  invisible(x)
}
#' @importFrom utils str
#' @export
str.euclid_affine_transformation <- function(object, ...) {
  show <- min(5, length(object))
  cat(
    "affine transformation{", dim(object), "}",
    if (length(object) == 0) " [0]" else paste0(" [1:", length(object), "] "),
    if (length(object) == 0) "" else paste(format(object)[seq_len(show)], collapse = " "),
    if (show < length(object)) " ..." else "",
    sep = ""
  )
  invisible(object)
}
#' @export
length.euclid_affine_transformation <- function(x) {
  transform_length(get_ptr(x))
}
#' @export
rep.euclid_affine_transformation <- function(x, ...) {
  index <- rep(seq_along(x), ...)
  x[index]
}
#' @export
dim.euclid_affine_transformation <- function(x) {
  transform_dimension(get_ptr(x))
}
#' @export
`[.euclid_affine_transformation` <- function(x, i, j, ..., drop = TRUE) {
  index <- seq_along(x)[i]
  restore_euclid_vector(transform_subset(get_ptr(x), index), x)
}
#' @export
`[[.euclid_affine_transformation` <- function(x, i) {
  if (length(i) != 1) {
    rlang::abort("attempt to select more than one element in vector")
  }
  x[i]
}
#' @export
`[<-.euclid_affine_transformation` <- function(x, i, j, ..., value) {
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
  value <- rep_len(as_affine_transformation(value), length(index))
  restore_euclid_vector(transform_assign(get_ptr(x), index, get_ptr(value)), x)
}
#' @export
`[[<-.euclid_affine_transformation` <- function(x, i, value) {
  if (length(i) != 1) {
    rlang::abort("attempt to assign to more than one element in vector")
  }
  x[i] <- value
  x
}
#' @export
`$.euclid_affine_transformation` <- function(x, name) {
  rlang::abort("`$` is not defined for transformations")
}
#' @export
`$<-.euclid_affine_transformation` <- function(x, name, value) {
  rlang::abort("`$<-` is not defined for transformations")
}
#' @export
c.euclid_affine_transformation <- function(..., recursive = FALSE) {
  input <- lapply(list(...), as_affine_transformation)
  if (length(unique(vapply(input, dim, integer(1)))) != 1) {
    rlang::abort("Transformations can only be combined with other transformations of the same dimensionalities")
  }
  input <- lapply(input, get_ptr)
  res <- transform_combine(input[[1]], input[-1])
  restore_euclid_vector(res, ..1)
}
#' @export
is.na.euclid_affine_transformation <- function(x) {
  transform_is_na(get_ptr(x))
}
#' @export
`is.na<-.euclid_affine_transformation` <- function(x, value) {
  x[is.na(x)] <- value
  x
}
#' @export
anyNA.euclid_affine_transformation <- function(x, recursive) {
  transform_any_na(get_ptr(x))
}
#' @export
as.data.frame.euclid_affine_transformation <- function(x, row.names = NULL, optional = FALSE, ...) {
  df <- list(x)
  class(df) <- "data.frame"
  attr(df, "row.names") <- .set_row_names(length(x))
  df
}
#' @export
unique.euclid_affine_transformation <- function(x, incomparables = FALSE, ...) {
  restore_euclid_vector(transform_unique(get_ptr(x)), x)
}
#' @export
duplicated.euclid_affine_transformation <- function(x, incomparables = FALSE, ...) {
  transform_duplicated(get_ptr(x))
}
#' @export
anyDuplicated.euclid_affine_transformation <- function(x, incomparables = FALSE, ...) {
  transform_any_duplicated(get_ptr(x))
}
match_transform <- function(x, table) {
  transform_match(get_ptr(x), get_ptr(table))
}

# Misc --------------------------------------------------------------------

#' @rdname affine_transformation
#' @export
inverse <- function(x) {
  if (!is_affine_transformation(x)) {
    rlang::abort("`x` must be an affine transformation vector")
  }
  restore_euclid_vector(transform_inverse(get_ptr(x)), x)
}
#' @rdname affine_transformation
#' @export
is_reflecting <- function(x) {
  if (!is_affine_transformation(x)) {
    rlang::abort("`x` must be an affine transformation vector")
  }
  transform_is_reflecting(get_ptr(x))
}

# Group generics ----------------------------------------------------------

#' @export
Ops.euclid_affine_transformation <- function(e1, e2) {
  if (!.Generic %in% c("*", "==", "!=")) {
    rlang::abort(paste0("The `", .Generic, "` operator is not defined for transformation matrices"))
  }
  e1 <- as_affine_transformation(e1)
  e2 <- as_affine_transformation(e2)
  if (dim(e1) != dim(e2)) {
    rlang::abort("transformations must be of the same dimensionality")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    new_affine_transformation_empty(dim(e1))
  }
  res <- switch(.Generic,
    "*" = transform_multiply(get_ptr(e1), get_ptr(e2)),
    "==" = transform_is_equal(get_ptr(e1), get_ptr(e2)),
    "!=" = transform_is_not_equal(get_ptr(e1), get_ptr(e2)),
  )
  if (.Generic %in% "*") {
    res <- restore_euclid_vector(res, e1)
  }
  res
}
#' @export
Math.euclid_affine_transformation <- function(x) {
  if (.Generic != "cumprod") {
    rlang::abort(paste0("`", .Generic, "` is not defined for transformation matrices"))
  }
  restore_euclid_vector(transform_cumprod(get_ptr(x)), x)
}
#' @export
Ops.euclid_affine_transformation <- function(..., na.rm) {
  na.rm = isTRUE(na.rm)
  input <- do.call(c, list(...))
  if (.Generic != "prod") {
    rlang::abort(paste0("`", .Generic, "` is not defined for transformation matrices"))
  }
  restore_euclid_vector(transform_prod(get_ptr(input), na.rm), input)
}

# Internal constructors ---------------------------------------------------

affine_rotate_axis <- function(rho, axis) {
  rho <- as.numeric(rho)
  n <- max(length(rho), length(axis))
  sinr <- sin(rho)
  cosr <- cos(rho)
  if (length(rho) == 1) {
    sinr <- rep_len(sinr, n)
    cosr <- rep_len(cosr, n)
  }
  if (length(axis) == 1) {
    axis <- rep_len(axis, n)
  }
  if (length(cosr) != length(axis)) {
    rlang::abort("`rho` and `axis` must be either scalar or equal length")
  }
  is_na <- !is.finite(cosr) || !is.finite(sinr) || is.na(axis)
  matrices <- lapply(seq_len(n), function(i) {
    if (is_na[i]) {
      return(matrix(NA_real_, ncol = 4, nrow = 4))
    }
    switch(axis[i],
      x = matrix(
        c(1,       0,        0, 0,
          0, cosr[i], -sinr[i], 0,
          0, sinr[i],  cosr[i], 0,
          0,       0,        0, 1),
        nrow = 4, ncol = 4
      ),
      y = matrix(
        c( cosr[i], 0, sinr[i], 0,
                 0, 1,       0, 0,
          -sinr[i], 0, cosr[i], 0,
                 0, 0,       0, 1),
        nrow = 4, ncol = 4
      ),
      z = matrix(
        c(cosr[i], -sinr[i], 0, 0,
          sinr[i],  cosr[i], 0, 0,
                0,        0, 1, 0,
                0,        0, 0, 1),
        nrow = 4, ncol = 4
      ),
      rlang::abort(paste0("Unknown axis: `", axis[i], "`"))
    )
  })
  new_affine_transformation3(create_transform_3_matrix(matrices))
}

affine_rotate_direction <- function(rho, direction) {
  direction <- as_vec(direction)
  if (dim(direction) != 3) {
    rlang::abort("Need a 3-dimensional vector for affine rotation around vector")
  }
  n <- max(length(rho), length(direction))
  rho <- as.numeric(rho)
  sinr <- sin(rho)
  cosr <- cos(rho)
  if (length(rho) == 1) {
    sinr <- rep_len(sinr, n)
    cosr <- rep_len(cosr, n)
  }
  if (length(direction) == 1) {
    direction <- rep_len(direction, n)
  }
  if (length(cosr) != length(direction)) {
    rlang::abort("`rho` and `direction` must be either scalar or equal length")
  }
  is_na <- !is.finite(cosr) || !is.finite(sinr) || is.na(direction)
  direction <- as.matrix(direction)
  l <- sqrt(direction[,1]^2 + direction[,2]^2 + direction[,3]^2)
  direction <- direction / cbind(l, l, l)
  m11 <- cosr + direction[,1]^2 * (1 - cosr)
  m12 <- direction[,1] * direction[,2] * (1 - cosr) - direction[,3]*sinr
  m13 <- direction[,1] * direction[,3] * (1 - cosr) + direction[,2]*sinr
  m21 <- direction[,1] * direction[,2] * (1 - cosr) + direction[,3]*sinr
  m22 <- cosr + direction[,2]^2 * (1 - cosr)
  m23 <- direction[,2] * direction[,3] * (1 - cosr) - direction[,1]*sinr
  m31 <- direction[,1] * direction[,3] * (1 - cosr) - direction[,2]*sinr
  m32 <- direction[,2] * direction[,3] * (1 - cosr) + direction[,1]*sinr
  m33 <- cosr + direction[,3]^2 * (1 - cosr)
  matrices <- lapply(seq_len(n), function(i) {
    if (is_na[i]) {
      return(matrix(NA_real_, ncol = 4, nrow = 4))
    }
    matrix(c(
      m11, m12, m13, 0,
      m21, m22, m23, 0,
      m31, m32, m33, 0,
        0,   0,   0, 1
    ), ncol = 4, nrow = 4)
  })
  new_affine_transformation3(create_transform_3_matrix(matrices))
}

affine_rotate_ypr <- function(yaw, pitch, roll) {
  yaw <- as.numeric(yaw)
  cosy <- cos(yaw)
  siny <- sin(yaw)
  pitch <- as.numeric(pitch)
  cosp <- cos(pitch)
  sinp <- sin(pitch)
  roll <- as.numeric(roll)
  cosr <- cos(roll)
  sinr <- sin(roll)
  n <- max(length(yaw), length(pitch), length(roll))
  if (length(yaw) == 1) {
    cosy <- rep_len(cosy, n)
    siny <- rep_len(siny, n)
  }
  if (length(pitch) == 1) {
    cosp <- rep_len(cosp, n)
    sinp <- rep_len(sinp, n)
  }
  if (length(roll) == 1) {
    cosr <- rep_len(cosr, n)
    sinr <- rep_len(sinr, n)
  }
  if (length(cosy) != length(cosp) || length(cosy) != length(cosr)) {
    rlang::abort("`yaw`, `pitch`, and `roll` must either be scalars or of the same length")
  }
  is_na <- !is.finite(cosy) || !is.finite(siny) || !is.finite(cosp) || !is.finite(sinp) || !is.finite(cosr) || !is.finite(sinr)
  m11 <- cosy * cosp
  m12 <- cosy * sinp * sinr - siny * cosr
  m13 <- cosy * sinp * cosr + siny * sinr
  m21 <- siny * cosp
  m22 <- siny * sinp * sinr + cosy * cosr
  m23 <- siny * sinp * cosr - cosy * sinr
  m31 <- -sinp
  m32 <- cosp * sinr
  m33 <- cosp * cosr
  matrices <- lapply(seq_len(n), function(i) {
    if (is_na[i]) {
      return(matrix(NA_real_, ncol = 4, nrow = 4))
    }
    matrix(c(
      m11, m12, m13, 0,
      m21, m22, m23, 0,
      m31, m32, m33, 0,
        0,   0,   0, 1
    ), ncol = 4, nrow = 4)
  })
  new_affine_transformation3(create_transform_3_matrix(matrices))
}

new_affine_transformation2 <- function(x) {
  x <- list(x)
  class(x) <- c("euclid_affine_transformation2", "euclid_affine_transformation")
  x
}
new_affine_transformation3 <- function(x) {
  x <- list(x)
  class(x) <- c("euclid_affine_transformation3", "euclid_affine_transformation")
  x
}

new_affine_transformation_empty <- function(dim) {
  if (dim == 2) {
    new_affine_transformation2(create_transform_2_identity(0L))
  } else {
    new_affine_transformation3(create_transform_3_identity(0L))
  }
}
