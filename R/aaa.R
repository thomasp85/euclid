validate_constructor_input <- function(..., .convert_numerics = TRUE) {
  inputs <- lapply(list(...), function(x) {
    if (.convert_numerics && !is_geometry(x) && is.numeric(x)) {
      x <- as_exact_numeric(x)
    }
    x
  })
  dim <- unique(unlist(lapply(inputs, dim)))
  if (length(dim) > 1) {
    rlang::abort("Inputs must be of the same dimensionality")
  }
  input_lengths <- lengths(inputs)
  if (length(input_lengths) == 0 || any(lengths(input_lengths)) == 0) {
    return(list())
  }
  max_length <- max(input_lengths)
  if (any(input_lengths != 1 & input_lengths != max_length)) {
    rlang::abort("Inputs must be either scalar or of the same length")
  }
  inputs[input_lengths == 1] <- lapply(inputs[input_lengths == 1], function(x) {
    rep_len(x, max_length)
  })
  inputs
}
check_geometry_input <- function(..., .name) {
  input <- list(...)
  input <- input[!vapply(input, is.null, logical(1))]
  if (!all(vapply(input, is_geometry, logical(1)))) {
    rlang::abort(paste0("`", .name, "` is only defined for geometries"))
  }
  if (length(unique(vapply(input, dim, integer(1)))) != 1) {
    rlang::abort("Geometries must have the same dimensionality")
  }
  invisible(NULL)
}

get_ptr <- function(x) .subset2(x, 1L)

restore_euclid_vector <- function(x, old) {
  x <- list(x)
  attributes(x) <- attributes(old)
  x
}

# rep_len is broken on R < 4.0
rep_len <- function(x, length) {
  rep(x, length.out = length)
}
