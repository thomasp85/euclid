#' Plotting functions for geometries
#'
#' euclid provide interfaces for both base and grid graphics that allows you to
#' visualise the geometries you are working with. There is only functionality
#' for 2D geometries so 3D geometries will be mapped to the plane given by the
#' `mapping_plane` argument. The `plot` method for geometries will behave like
#' the base [`plot()`] method and set up a new plotting window based on the
#' given settings. `euclid_plot` will add to the existing plot and thus use the
#' coordinate system currently in effect. `euclid_grob` will create a grob that
#' can be rendered with [`grid.draw()`][grid::grid.draw].
#'
#' @param x A geometry vector
#' @param mapping_plane either `"x"`, `"y"`, `"z"`, or a scalar plane geometry
#' @param unit The [unit][grid::unit] the values in the geometry corresponds to.
#' @param name The name of the created grob
#' @param gp A [gpar][grid::gpar] object giving the graphical parameters to use
#' for rendering
#' @param vp A [viewport][grid::viewport] or `NULL`
#' @param ... Arguments passed along to the specific drawing method.
#' - points (and weighted points) use [`points()`][graphics::points] and
#'   [`pointsGrob()`][grid::pointsGrob]
#' - circles use [`symbols()`][graphics::symbols] and
#'   [`circleGrob()`][grid::circleGrob]
#' - directions and vectors use [`arrows()`][graphics::arrows] and
#'   [`segmentsGrob()`][grid::segmentsGrob]
#' - iso rectangles and bounding boxes use [`symbols()`][graphics::symbols] and
#'   [`rectGrob()`][grid::rectGrob]
#' - lines, rays, and segments use [`segments()`][graphics::segments] and
#'   [`segmentsGrob()`][grid::segmentsGrob]
#' - triangles use [polygon()][graphics::polygon] and
#'   [`polygonGrob()`][grid::polygonGrob]
#'
#' @return `euclid_plot` is called for its side effects, `euclid_grob` returns a
#' [grob][grid::grob]
#'
#' @export
#'
euclid_plot <- function(x, ..., mapping_plane = "z") {
  UseMethod("euclid_plot")
}
#' @export
euclid_plot.default <- function(x, ..., mapping_plane = "z") {
  if (!is.null(x)) {
    rlang::abort("No plotting method for this class")
  }
}
#' @rdname euclid_plot
#' @export
#' @importFrom grid gpar
euclid_grob <- function(x, ..., unit = "native", name = NULL, gp = gpar(), vp = NULL, mapping_plane = "z") {
  UseMethod("euclid_plot")
}
#' @export
euclid_grob.default <- function(x, ..., unit = "native", name = NULL, gp = gpar(), vp = NULL, mapping_plane = "z") {
  if (!is.null(x)) {
    rlang::abort("No plotting method for this class")
  }
  grid::nullGrob()
}

#' @rdname euclid_plot
#' @export
#' @importFrom graphics plot plot.new plot.window Axis title box
#' @importFrom grDevices dev.hold dev.flush
plot.euclid_geometry <- function(x, y, xlim = NULL, ylim = NULL, mapping_plane = "z", add = FALSE, axes = TRUE, frame.plot = axes, ...) {
  x <- ensure_2d(x, mapping_plane)

  dev.hold()
  on.exit(dev.flush())
  if (!add) {
    if (is.null(xlim) || is.null(ylim)) {
      if (is_vec(x)) {
        cbox <- bbox(c(point(0, 0), as_point(as_vec(x))))
      } else if (is_direction(x)) {
        cbox <- bbox(point(0, 0))
      } else if (is_line(x) || is_ray(x)) {
        cbox <- bbox(vertex(x))
      } else {
        cbox <- bbox(x)
      }
      cbox <- as.matrix(sum(cbox, na.rm = TRUE))
      if (is.null(xlim)) xlim <- cbox[c(1, 3)]
      if (is.null(ylim)) ylim <- cbox[c(2, 4)]
      if (xlim[1] == xlim[2]) xlim <- xlim + c(-0.5, 0.5)
      if (ylim[1] == ylim[2]) ylim <- ylim + c(-0.5, 0.5)
    }
    plot.new()
    plot.window(xlim, ylim, asp = 1)
  }
  euclid_plot(x, ...)
  if (axes) {
    Axis(xlim, side = 1)
    Axis(ylim, side = 2)
    title(xlab = "x", ylab = "y")
  }
  if (frame.plot) {
    box()
  }
  invisible(NULL)
}
#' @export
plot.exact_numeric <- function(x, y, ...) {
  plot(as.numeric(x), as.numeric(y), ...)
}
#' @export
plot.euclid_bbox <- function(x, y, ...) {
  if (dim(x) != 2) {
    rlang::abort("Only 2 dimensional bounding boxes can be plotted")
  }
  plot(as_iso_rect(x), ...)
}

#' @export
#' @importFrom graphics symbols
euclid_plot.euclid_circle <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  symbols(x[, 1], x[, 2], circles = sqrt(x[, 3]), inches = FALSE, ..., add = TRUE)
  invisible(NULL)
}
#' @export
#' @importFrom grid circleGrob
euclid_grob.euclid_circle <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  grid::circleGrob(x[, 1], x[, 2], sqrt(x[, 3]), default.units = unit, name = name, gp = gp, vp = vp)
}
#' @export
#' @importFrom graphics par arrows
euclid_plot.euclid_direction <- function(x, sep = 0.1, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  window <- par("usr")
  width <- window[2] - window[1]
  height <- window[4] - window[3]
  step <- min(width, height) * sep
  x_loc <- seq(window[1], window[2], by = step) + step * 0.2
  y_loc <- seq(window[3], window[4], by = step) + step * 0.2
  start <- expand.grid(x_loc, y_loc)
  n_vec <- nrow(start)
  start <- start[rep(seq_len(n_vec), each = length(x)), ]
  x <- as_vec(x)
  x <- x * step * 0.8 / approx_length(x)
  x <- as.matrix(rep(x, n_vec))
  end_x <- start[, 1] + x[, 1]
  end_y <- start[, 2] + x[, 2]
  arrows(start[, 1], start[, 2], start[, 1] + x[, 1], start[, 2] + x[, 2], ...)
  invisible(NULL)
}
#' @export
#' @importFrom grid unit
euclid_grob.euclid_direction <- function(x, sep = 0.1, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  loc <- unit(seq(sep/2, 1 + sep, by = sep), units = "snpc")
  start_x <- rep(rep(loc, length(loc)), each = length(x))
  start_y <- rep(rep(loc, each = length(loc)), each = length(x))
  x <- as_vec(x)
  x <- x / approx_length(x)

  warning("not implemented")
}
#' @export
#' @importFrom graphics symbols
euclid_plot.euclid_iso_rect <- function(x, ..., mapping_plane = "z") {
  x <- as.matrix(x)
  width <- x[c(FALSE, TRUE, FALSE, FALSE), 1] - x[c(TRUE, FALSE, FALSE, FALSE), 1]
  height <- x[c(FALSE, FALSE, TRUE, FALSE), 2] - x[c(FALSE, TRUE, FALSE, FALSE), 2]
  y <- x[c(TRUE, FALSE, FALSE, FALSE), 2] + height / 2
  x <- x[c(TRUE, FALSE, FALSE, FALSE), 1] + width / 2
  symbols(x, y, rectangles = cbind(width, height), inches = FALSE, ..., add = TRUE)
  invisible(NULL)
}
#' @export
#' @importFrom graphics symbols
euclid_grob.euclid_iso_rect <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- as.matrix(x)
  width <- x[c(FALSE, TRUE, FALSE, FALSE), 1] - x[c(TRUE, FALSE, FALSE, FALSE), 1]
  height <- x[c(FALSE, FALSE, TRUE, FALSE), 2] - x[c(FALSE, TRUE, FALSE, FALSE), 2]
  y <- x[c(TRUE, FALSE, FALSE, FALSE), 2] + height / 2
  x <- x[c(TRUE, FALSE, FALSE, FALSE), 1] + width / 2
  grid::rectGrob(x, y, width, height, default.units = unit, name = name, gp = gp, vp = vp)
}
#' @export
euclid_plot.euclid_bbox2 <- function(x, ..., mapping_plane = "z") {
  euclid_plot(as_iso_rect(x), ..., mapping_plane = mapping_plane)
}
#' @export
euclid_grob.euclid_bbox2 <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  euclid_plot(as_iso_rect(x), unit = unit, name = name, gp = gp, vp = vp, ..., mapping_plane = mapping_plane)
}
#' @export
#' @importFrom graphics abline
euclid_plot.euclid_line <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  window <- par("usr")
  window <- expand_rect(window[1], window[2], window[3], window[4], 2)
  x <- intersection_segment(x, iso_rect(window$xmin, window$ymin, window$xmax, window$ymax))
  euclid_plot(x, ...)
}
#' @export
euclid_grob.euclid_line <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  warning("not implemented")
}
#' @export
euclid_plot.euclid_point_w <- function(x, ..., mapping_plane = "z") {
  euclid_plot(as_point(x), ...)
}
#' @export
#' @importFrom grid unit
euclid_grob.euclid_point_w <- function(x, pch = 1, size = unit(1, "char"), unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  euclid_grob(as_point(x), pch = 1, size = size, unit = unit, name = name, gp = gp, vp = vp)
}
#' @export
#' @importFrom graphics points
euclid_plot.euclid_point <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  points(x[,1], x[,2], ...)
  invisible(NULL)
}
#' @export
#' @importFrom grid unit
euclid_grob.euclid_point <- function(x, pch = 1, size = unit(1, "char"), unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  grid::pointsGrob(x[,1], x[,2], pch = pch, size = size, default.units = unit, name = name, gp = gp, vp = vp)
}
#' @export
euclid_plot.euclid_ray <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  window <- par("usr")
  window <- expand_rect(window[1], window[2], window[3], window[4], 2)
  x <- intersection_segment(x, iso_rect(window$xmin, window$ymin, window$xmax, window$ymax))
  euclid_plot(x, ...)
}
#' @export
euclid_grob.euclid_ray <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  warning("not implemented")
}
#' @export
#' @importFrom graphics segments
euclid_plot.euclid_segment <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  segments(x[c(TRUE, FALSE), 1], x[c(TRUE, FALSE), 2], x[c(FALSE, TRUE), 1], x[c(FALSE, TRUE), 2], ...)
  invisible(NULL)
}
#' @export
euclid_grob.euclid_segment <- function(x, arrow = NULL, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  grid::segmentsGrob(
    x[c(TRUE, FALSE), 1], x[c(TRUE, FALSE), 2],
    x[c(FALSE, TRUE), 1], x[c(FALSE, TRUE), 2],
    arrow = arrow, default.units = unit, name = name, gp = gp, vp = vp
  )
}
#' @export
#' @importFrom graphics polygon
euclid_plot.euclid_triangle <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  y <- rbind(x[c(TRUE, FALSE, FALSE), 2], x[c(FALSE, TRUE, FALSE), 2], x[c(FALSE, FALSE, TRUE), 2], NA)
  x <- rbind(x[c(TRUE, FALSE, FALSE), 1], x[c(FALSE, TRUE, FALSE), 1], x[c(FALSE, FALSE, TRUE), 1], NA)
  polygon(x, y, ...)
  invisible(NULL)
}
#' @export
euclid_grob.euclid_triangle <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  grid::polygonGrob(x[, 1], x[, 2], id.lengths = 3, default.units = unit, name = name, gp = gp, vp = vp)
}
#' @export
#' @importFrom graphics arrows
euclid_plot.euclid_vector <- function(x, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  x <- as.matrix(x)
  arrows(rep_len(0, nrow(x)), rep_len(0, nrow(x)), x[, 1], x[, 2], ...)
  invisible(NULL)
}
#' @export
#' @importFrom graphics arrows
euclid_grob.euclid_vector <- function(x, unit = "native", name = NULL, gp = gpar(), vp = NULL, ..., mapping_plane = "z") {
  x <- ensure_2d(x, mapping_plane)
  warning("not implemented")
}

ensure_2d <- function(x, mapping_plane) {
  if (length(mapping_plane) != 1) {
    rlang::abort("`mapping_plane` must be a scalar")
  }
  if (dim(x) == 3) {
    mapping_plane <- switch(mapping_plane,
      x = plane(vec(1, 0, 0), point(0, 0, 0)),
      y = plane(vec(0, 1, 0), point(0, 0, 0)),
      z = plane(vec(0, 0, 1), point(0, 0, 0)),
      if (!is_plane(mapping_plane)) {
        rlang::abort("`mapping_plane` must be a plane or 'x', 'y', or 'z'")
      }
    )
    x <- map_to(x, mapping_plane)
  }
  x
}
expand_rect <- function(xmin, xmax, ymin, ymax, fac) {
  xexpand <- (xmax - xmin) * (fac- 1) / 2
  yexpand <- (ymax - ymin) * (fac- 1) / 2
  list(
    xmin = xmin - xexpand, xmax = xmax + xexpand,
    ymin = ymin - yexpand, ymax = ymax + yexpand
  )
}
