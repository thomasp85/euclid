#' Create a vector of bounding boxes
#'
#' Bounding boxes denote the exten of geometries. It follows that bounding boxes
#' are only defined for geometries that are located in space and have finite
#' extent. Thus, vectors, lines, directions, rays, etc. does not have bounding
#' boxes, while e.g. spheres, circles, segments, etc has. Since the extent of
#' geometries cannot always be given exact (e.g. for circles), bounding boxes
#' are defined in regular floating point precision. Bounding boxes can be
#' compared for equality and be tested for whether they overlap. Adding bounding
#' boxes together will give the bounding box containing both.
#'
#' @param ... Either a vector of geometries or a range of numeric vectors (4 for
#' 2D bounding boxes and 6 for 3D) interpreted in the order xmin, ymin, zmin,
#' xmax, ymax, zmax.
#' @param x,y vectors of bounding boxes or geometries
#'
#' @return An `euclid_bbox` vector
#'
#' @export
#'
#' @examples
#' # Construction
#' bbox(10, -2, 15, 0)
#'
#' seg <- segment(point(sample(10, 4), sample(10, 4)),
#'                point(sample(10, 4), sample(10, 4)))
#'
#' boxes <- bbox(seg)
#' boxes
#'
#' plot(seg)
#' euclid_plot(boxes, fg = "firebrick")
#'
#' # Comparison
#' boxes[1] == boxes
#'
#' boxes[1:2] %overlaps% boxes[3:4]
#'
#' # Addition
#' boxes[1] + boxes[2]
#'
#' cumsum(boxes)
#'
#' plot(sum(boxes), bg = "grey", fg = NA)
#' euclid_plot(boxes)
#'
#' # Conversion
#' as.matrix(boxes)
#'
bbox <- function(...) {
  if (is_geometry(..1)) {
    bboxes <- geometry_bbox(get_ptr(..1))
    if (dim(..1) == 2) {
      return(new_bbox2(bboxes))
    } else {
      return(new_bbox3(bboxes))
    }
    create_bbox_2()
  }
  inputs <- validate_constructor_input(..., .convert_numerics = FALSE)
  inputs <- inputs[vapply(inputs, is.numeric, logical(1))]
  if (length(inputs) == 4) {
    new_bbox2(create_bbox_2(inputs[[1]], inputs[[2]], inputs[[3]], inputs[[4]]))
  } else if(length(inputs) == 6) {
    new_bbox3(create_bbox_3(inputs[[1]], inputs[[2]], inputs[[3]], inputs[[4]], inputs[[5]], inputs[[6]]))
  } else {
    rlang::abort("bbox vectors needs 4 or 6 coordinate inputs")
  }
}
#' @rdname bbox
#' @export
is_bbox <- function(x) inherits(x, "euclid_bbox")

# Conversion --------------------------------------------------------------

#' @rdname bbox
#' @export
as_bbox <- function(x) {
  UseMethod("as_bbox")
}
#' @export
as_bbox.euclid_bbox <- function(x) {
  x
}
#' @export
as.matrix.euclid_bbox <- function(x, ...) {
  bbox_to_matrix(get_ptr(x))
}
#' @export
as.character.euclid_bbox <- function(x, ...) {
  format(x, ...)
}

#' @export
as_iso_cube.euclid_bbox3 <- function(x) {
  iso_cube(x)
}
#' @export
as_iso_rect.euclid_bbox2 <- function(x) {
  iso_rect(x)
}

# Vector basic ------------------------------------------------------------

#' @export
format.euclid_bbox <- function(x, ...) {
  transform_format(get_ptr(x))
}
#' @export
print.euclid_bbox <- function(x, ...) {
  cat("<", dim(x), "D bounding boxes [", length(x), "]>\n", sep = "")
  if (length(x) == 0) {
    cat("[empty]")
  } else {
    print(format(x, ...), quote = FALSE)
  }
  invisible(x)
}
#' @importFrom utils str
#' @export
str.euclid_bbox <- function(object, ...) {
  show <- min(5, length(object))
  cat(
    "bounding box{", dim(object), "}",
    if (length(object) == 0) " [0]" else paste0(" [1:", length(object), "] "),
    if (length(object) == 0) "" else paste(format(object)[seq_len(show)], collapse = " "),
    if (show < length(object)) " ..." else "",
    sep = ""
  )
  invisible(object)
}
#' @export
length.euclid_bbox <- function(x) {
  bbox_length(get_ptr(x))
}
#' @export
rep.euclid_bbox <- function(x, ...) {
  index <- rep(seq_along(x), ...)
  x[index]
}
#' @export
dim.euclid_bbox <- function(x) {
  bbox_dimension(get_ptr(x))
}
#' @export
`[.euclid_bbox` <- function(x, i, j, ..., drop = TRUE) {
  index <- seq_along(x)[i]
  restore_euclid_vector(bbox_subset(get_ptr(x), index), x)
}
#' @export
`[[.euclid_bbox` <- function(x, i) {
  if (length(i) != 1) {
    rlang::abort("attempt to select more than one element in vector")
  }
  x[i]
}
#' @export
`[<-.euclid_bbox` <- function(x, i, j, ..., value) {
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
  value <- rep_len(as_bbox(value), length(index))
  restore_euclid_vector(bbox_assign(get_ptr(x), index, get_ptr(value)), x)
}
#' @export
`[[<-.euclid_bbox` <- function(x, i, value) {
  if (length(i) != 1) {
    rlang::abort("attempt to assign to more than one element in vector")
  }
  x[i] <- value
  x
}
#' @export
`$.euclid_bbox` <- function(x, name) {
  rlang::abort("`$` is not defined for bounding boxes")
}
#' @export
`$<-.euclid_bbox` <- function(x, name, value) {
  rlang::abort("`$<-` is not defined for bounding boxes")
}
#' @export
c.euclid_bbox <- function(..., recursive = FALSE) {
  input <- lapply(list(...), as_bbox)
  if (length(unique(vapply(input, dim, integer(1)))) != 1) {
    rlang::abort("Bounding boxes can only be combined with other bounding boxes of the same dimensionalities")
  }
  input <- lapply(input, get_ptr)
  res <- bbox_combine(input[[1]], input[-1])
  restore_euclid_vector(res, ..1)
}
#' @export
is.na.euclid_bbox <- function(x) {
  bbox_is_na(get_ptr(x))
}
#' @export
`is.na<-.euclid_bbox` <- function(x, value) {
  x[is.na(x)] <- value
  x
}
#' @export
anyNA.euclid_bbox <- function(x, recursive) {
  bbox_any_na(get_ptr(x))
}
#' @export
as.data.frame.euclid_bbox <- function(x, row.names = NULL, optional = FALSE, ...) {
  df <- list(x)
  class(df) <- "data.frame"
  attr(df, "row.names") <- .set_row_names(length(x))
  df
}
#' @export
unique.euclid_bbox <- function(x, incomparables = FALSE, ...) {
  restore_euclid_vector(bbox_unique(get_ptr(x)), x)
}
#' @export
duplicated.euclid_bbox <- function(x, incomparables = FALSE, ...) {
  bbox_duplicated(get_ptr(x))
}
#' @export
anyDuplicated.euclid_bbox <- function(x, incomparables = FALSE, ...) {
  bbox_any_duplicated(get_ptr(x))
}
match_bbox <- function(x, table) {
  bbox_match(get_ptr(x), get_ptr(table))
}

# Misc --------------------------------------------------------------------

#' @rdname bbox
#' @export
is_overlapping <- function(x, y) {
  x <- as_bbox(x)
  y <- as_bbox(y)
  bbox_overlaps(get_ptr(x), get_ptr(y))
}
#' @rdname bbox
#' @export
`%overlaps%` <- is_overlapping

# Group generics ----------------------------------------------------------

#' @export
Ops.euclid_bbox <- function(e1, e2) {
  if (!.Generic %in% c("+", "==", "!=")) {
    rlang::abort(paste0("The `", .Generic, "` operator is not defined for bounding boxes matrices"))
  }
  e1 <- as_bbox(e1)
  e2 <- as_bbox(e2)
  if (dim(e1) != dim(e2)) {
    rlang::abort("bounding boxes must be of the same dimensionality")
  }
  if (length(e1) == 0 || length(e2) == 0) {
    new_bbox_empty(dim(e1))
  }
  res <- switch(.Generic,
                "+" = bbox_plus(get_ptr(e1), get_ptr(e2)),
                "==" = bbox_is_equal(get_ptr(e1), get_ptr(e2)),
                "!=" = !bbox_is_equal(get_ptr(e1), get_ptr(e2))
  )
  if (.Generic %in% "+") {
    res <- restore_euclid_vector(res, e1)
  }
  res
}
#' @export
Math.euclid_bbox <- function(x, ...) {
  if (.Generic != "cumsum") {
    rlang::abort(paste0("`", .Generic, "` is not defined for bounding boxes"))
  }
  restore_euclid_vector(bbox_cumsum(get_ptr(x)), x)
}
#' @export
Summary.euclid_bbox <- function(..., na.rm) {
  na.rm = isTRUE(na.rm)
  input <- do.call(c, list(...))
  if (.Generic != "sum") {
    rlang::abort(paste0("`", .Generic, "` is not defined for bounding boxes"))
  }
  restore_euclid_vector(bbox_sum(get_ptr(input), na.rm), input)
}

# Internal constructors ---------------------------------------------------

new_bbox_empty <- function(dim) {
  if (dim == 2) {
    new_bbox2(create_bbox_2(numeric(0), numeric(0), numeric(0), numeric(0)))
  } else {
    new_bbox3(create_bbox_3(numeric(0), numeric(0), numeric(0), numeric(0), numeric(0), numeric(0)))
  }
}
new_bbox2 <- function(x) {
  x <- list(x)
  class(x) <- c("euclid_bbox2", "euclid_bbox")
  x
}
new_bbox3 <- function(x) {
  x <- list(x)
  class(x) <- c("euclid_bbox3", "euclid_bbox")
  x
}

