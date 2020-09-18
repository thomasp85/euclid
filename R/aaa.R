validate_numeric_input <- function(...) {
  inputs <- list(...)
  inputs <- lapply(inputs, vec_cast, double())
  l <- lengths(inputs)
  l_max <- max(l)
  non_conform <- l != 1 & l != l_max
  if (any(non_conform)) {
    rlang::abort(paste0(
      "Inputs must be either scalars or the same length. `",
      paste(names(inputs)[non_conform], collapse = "`, `"),
      "` have fewer elements than the longest argument (", l_max, ")"
    ))
  }
  lapply(inputs, rep_len, l_max)
}
assert_lengths_are_equal <- function(...) {
  if (length(unique(lengths(list(...)))) != 1) {
    rlang::abort("All input vectors must by of equal length")
  }
}
