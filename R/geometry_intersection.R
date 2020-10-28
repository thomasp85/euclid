#' Calculate intersections between geometries
#'
#' An intersection between two geometries is defined as the geometry that is
#' contained in both geometries. In other words all points laying on the
#' intersection is also part of the two incoming geometries. It follows that the
#' result of calculating intersections can be varied, even between the same
#' combination of geometries. For example, The intersection between a triangle
#' and a plane can be `NULL`, a point, a segment, or a triangle depending on
#' their relative position and orientation. Because of this, and to avoid
#' confusion around the return type `intersection()` always return a list of
#' scalar geometries or `NULL`s. Intersections can only be calculated between
#' geometries located in space, which rules out vectors and directions. Further,
#' not all combinations of geometries have exact intersections defined (circles
#' and spheres are especially limited). euclid also provides a list of type-safe
#' intersection functions that allways returns a vector of geometries of the
#' requested type. Intersections that doesn't match the requested type are
#' returned as `NA`, as are non-intersecting pairs. It is thus not possible to
#' determine if an intersection occurs using these functions.
#'
#' @param x,y Geometry vectors or bounding boxes
#'
#' @return a list of scalar geometry vectors and `NULL`s depending on the result
#' of the intersection query, or a vector of geometries as requested.
#'
#' @export
#'
#' @examples
#' # Example of the difference in output
#' t <- triangle(point(0, 0), point(1, 1), point(0, 1))
#' l <- line(1, -1, c(0, 1, 2))
#' i <- intersection(t, l)
#' i
#'
#' plot(t, col = "grey", border = NA, xlim= c(-0.5, 1), ylim = c(0, 1.5))
#' euclid_plot(l)
#' for (int in i) {
#'   euclid_plot(int, col = "firebrick", pch = 16, cex = 2, lwd = 3)
#' }
#'
#' # Input is symmetric
#' intersection(l, t)
#'
#' # Request only segment intersections
#' intersection_segment(l, t)
#'
intersection <- function(x, y) {
  if (is_bbox(x)) {
    if (dim(x) == 2) {
      x <- as_iso_rect(x)
    } else {
      x <- as_iso_cube(x)
    }
  }
  if (is_bbox(y)) {
    if (dim(y) == 2) {
      y <- as_iso_rect(y)
    } else {
      y <- as_iso_cube(y)
    }
  }
  if (!is_geometry(x) || !is_geometry(y)) {
    rlang::abort("intersection can only be calculated between two geometries")
  }
  lapply(geometry_intersection(get_ptr(x), get_ptr(y)), function(g) {
    if (is.null(g)) return(g)
    new_geometry_vector(g)
  })
}

intersection_type_safe <- function(x, y, pred, val) {
  overlaps <- intersection(x, y)
  res <- rep(val[NA], length.out = length(overlaps))
  keep <- vapply(overlaps, pred, logical(1))
  res[keep] <- do.call(c, overlaps[keep])
  res
}
#' @rdname intersection
#' @export
intersection_circle <- function(x, y) {
  intersection_type_safe(x, y, is_circle, circle(default_dim = dim(x)))
}
#' @rdname intersection
#' @export
intersection_iso_rect <- function(x, y) {
  intersection_type_safe(x, y, is_iso_rect, iso_rect())
}
#' @rdname intersection
#' @export
intersection_plane <- function(x, y) {
  intersection_type_safe(x, y, is_plane, plane())
}
#' @rdname intersection
#' @export
intersection_point <- function(x, y) {
  intersection_type_safe(x, y, is_point, point(default_dim = dim(x)))
}
#' @rdname intersection
#' @export
intersection_line <- function(x, y) {
  intersection_type_safe(x, y, is_line, line(default_dim = dim(x)))
}
#' @rdname intersection
#' @export
intersection_ray <- function(x, y) {
  intersection_type_safe(x, y, is_ray, ray(default_dim = dim(x)))
}
#' @rdname intersection
#' @export
intersection_segment <- function(x, y) {
  intersection_type_safe(x, y, is_segment, segment(default_dim = dim(x)))
}
#' @rdname intersection
#' @export
intersection_sphere <- function(x, y) {
  intersection_type_safe(x, y, is_sphere, sphere())
}
#' @rdname intersection
#' @export
intersection_triangle <- function(x, y) {
  intersection_type_safe(x, y, is_triangle, triangle(default_dim = dim(x)))
}

#' Query whether geometries intersect
#'
#' While it is sometimes necessary to get the actual intersection geometry, it
#' may other times only be necessary to query whether an intersection exists.
#' This is in general much faster than checking if [intersection()] returns
#' `NULL`. Further, it is not bounded by the same constraint that an exact
#' intersection must be constructable so a wider range of geometries are
#' supported for the predicate. If the query is not possible it will return `NA`
#' rather than an error
#'
#' @param x,y Geometry vectors or bounding boxes
#'
#' @return a logical vector
#'
#' @export
#'
#' @examples
#' # Example of the predicate
#' t <- triangle(point(0, 0), point(1, 1), point(0, 1))
#' l <- line(1, -1, c(0, 1, 2))
#' has_intersection(t, l)
#'
#' # Use binary operator instead
#' t %is_intersecting% l
#'
#' # 2 dimensional circles are better supported
#' l %is_intersecting% circle(point(7, 4), 9)
#'
has_intersection <- function(x, y) {
  if (is_bbox(x)) {
    if (dim(x) == 2) {
      x <- as_iso_rect(x)
    } else {
      x <- as_iso_cube(x)
    }
  }
  if (is_bbox(y)) {
    if (dim(y) == 2) {
      y <- as_iso_rect(y)
    } else {
      y <- as_iso_cube(y)
    }
  }
  if (!is_geometry(x) || !is_geometry(y)) {
    rlang::abort("intersection can only be calculated between two geometries")
  }
  if (is_weighted_point(x)) {
    x <- as_point(x)
  }
  if (is_weighted_point(y)) {
    y <- as_point(y)
  }
  geometry_do_intersect(get_ptr(x), get_ptr(y))
}
#' @rdname has_intersection
#' @export
`%is_intersecting%` <- function(x, y) {
  has_intersection(x, y)
}
