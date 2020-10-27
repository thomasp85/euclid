#' Check if a geometry is degenerate
#'
#' Geometries can be ill-defined for several reasons, e.g. circles with a radius
#' of zero, segments that start and end at the same location, etc. See details
#' for a list of conditions that are considered degenerate.
#'
#' @param x A geometry vector
#'
#' @details
#' The following conditions are considered to produce degenerate geometries:
#' - A circle having a radius of zero
#' - An iso-rectangle with zero width or zero height
#' - An iso-cuboid with zero width, zero height, or zero depth
#' - A 2D line with the coefficients being zero
#' - A 3D line that is degenerated to a point
#' - A plane with the coefficients being zero
#' - A ray with the source and the second defining point being equal
#' - A segment with the source and target being equal
#' - A sphere with a radius of zero
#' - A tetrahedron with all vertices being co-planar
#' - A triangle with collinear vertices
#'
#' @return A logical vector
#'
#' @export
is_degenerate <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`is_degenerate` is only defined for geometries")
  }
  geometry_is_degenerate(get_ptr(x))
}

#' Query location of points relative to geometry
#'
#' Point predicates is at the heart of many geometry algorithms. These set of
#' functions allows you to query the location of points relative to a given
#' geometry vector. The functions are provided as both regular and binary
#' operators.
#'
#' @param x A geometry vector
#' @param y A points vector
#'
#' @details
#' There are two types of location predicates:
#'
#' ### Containment (inside and outside)
#' Queries whether a point is inside or outside the boundary defined by the
#' geometry. In 2D it is defined for geometries that have an area, In 3D it is
#' defined for geometries that has a volume. This means that containment is
#' defined for 2D circles but not 3D circles.
#'
#' ### Orientation (positive and negative)
#' Queries whether a point lies on the positive or negative side of a geometry.
#' It is defined for geometries that splits the dimensional space in two. This
#' means that it is not defined for rays, segments, etc with a finite length.
#'
#' For both types of predicates there are also the condition that the point lies
#' *on* the geometry. This predicate is equivalent for both types of predicates
#' and is defined for all geometries that has a location. This means that e.g.
#' directions and vectors do not define this predicate.
#'
#' @return A logical vector
#'
#' @rdname location_predicates
#' @name location_predicates
NULL

#' @rdname location_predicates
#' @export
has_on <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on%` <- function(y, x) has_on(x, y)

#' @rdname location_predicates
#' @export
has_inside <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_inside(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_inside%` <- function(y, x) has_inside(x, y)

#' @rdname location_predicates
#' @export
has_outside <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_outside(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_outside%` <- function(y, x) has_outside(x, y)

#' @rdname location_predicates
#' @export
has_on_positive_side <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on_positive(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on_positive_side%` <- function(y, x) has_on_positive_side(x, y)

#' @rdname location_predicates
#' @export
has_on_negative_side <- function(x, y) {
  y <- as_point(y)
  geometry_has_point_on_negative(get_ptr(x), get_ptr(y))
}
#' @rdname location_predicates
#' @export
`%is_on_negative_side%` <- function(y, x) has_on_negative_side(x, y)

#' Check geometries for axis alignment
#'
#' These predicate functions checks for whether a geometry varies along a given
#' axis. While it is common in 2 dimensions to ask whether something is vertical
#' or horizontal that notion does not scale well to 3 dimensions and euclid
#' instead elects to check for whether a given geometry is constant in a
#' specific coordinate value. As such, e.g. `has_constant_x()` is equivalent to
#' asking whether a given 2 dimensional geometry is vertical but also works for
#' 3 dimensional geometries.
#'
#' @param x A geometry vector
#' @param axis One or more specifications of the axes to check against as `"x"`,
#' `"y"`, `"z"` or `1`, `2`, `3`
#'
#' @return A logical vector
#'
#' @rdname constant_in
#' @name constant_in
#'
#' @examples
#' # Check for horizontal vector
#' v <- vec(1, -2:2)
#' has_constant_y(v)
#'
#' # Use recycling to check all axes
#' is_constant_in(vec(2, 0, -5), c("x", "y", "z"))
#'
NULL

#' @rdname constant_in
#' @export
is_constant_in <- function(x, axis) {
  if (!is_geometry(x)) {
    rlang::abort("`is_constant_in()` is only defined for geometries")
  }
  if (is.character(axis)) {
    axis <- match(axis, c("x", "y", "z"))
    if (anyNA(axis)) {
      rlang::abort("`axis` must be one of `x`, `y`, or `z`")
    }
  }
  axis <- as.integer(axis - 1)
  if (any(axis < 0 | axis >= dim(x))) {
    rlang::abort("`axis` must enumerate an axis in the geometries coordinate system")
  }
  geometry_constant_in(get_ptr(x), axis)
}
#' @rdname constant_in
#' @export
has_constant_x <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`has_constant_x()` is only defined for geometries")
  }
  geometry_constant_in(get_ptr(x), 0L)
}
#' @rdname constant_in
#' @export
has_constant_y <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`has_constant_y()` is only defined for geometries")
  }
  geometry_constant_in(get_ptr(x), 1L)
}
#' @rdname constant_in
#' @export
has_constant_z <- function(x) {
  if (!is_geometry(x)) {
    rlang::abort("`has_constant_z()` is only defined for geometries")
  }
  if (dim(x) != 3) {
    rlang::abort("`has_constant_z()` is only defined for 3 dimensional geometries")
  }
  geometry_constant_in(get_ptr(x), 2L)
}

#' Query geometry class
#'
#' While the geometry types provided by euclid are primitives, they can be
#' grouped based on their properties. Lines, rays, and segments are all curves
#' in space, with rays and segments being the semi-finite and finite version of
#' lines respectively. Circles, planes, triangles, and iso rectangles are all
#' surfaces in the sense that they define an area but doesn't have a volume.
#' Spheres and iso cubes are volumes. Vectors and directions are arrows. Points
#' and weighted points are locations. The class of geometry can be checked with
#' the given functions
#'
#' @param x A geometry vector
#'
#' @return a logical scalar
#'
#' @rdname geometry_class
#' @name geometry_class
#'
#' @examples
#' l <- line(3, 8, 1)
#' is_surface(l)
#' is_curve(l)
#' is_volume(l)
#'
NULL
#' @rdname geometry_class
#' @export
is_surface <- function(x) is_circle(x) || is_plane(x) || is_triangle(x) || is_iso_rect(x)
#' @rdname geometry_class
#' @export
is_volume <- function(x) is_sphere(x) || is_tetrahedron(x) || is_iso_cube(x)
#' @rdname geometry_class
#' @export
is_curve <- function(x) is_line(x) || is_ray(x) || is_segment(x)
#' @rdname geometry_class
#' @export
is_arrow <- function(x) is_vec(x) || is_direction(x)
#' @rdname geometry_class
#' @export
is_location <- function(x) is_point(x) || is_weighted_point(x)

#' Check geometries for parallelity
#'
#' If two geometries are parallel they have the same orientation. euclid allows
#' assessing parallelity of a broad range of geometries. If `x` and `y` are
#' surfaces the parallelity of their supporting plane is returned. If `x` and
#' `y` are curves, the parallelity of their supporting line is returned. If it
#' is a mix of surface and curve, the parallelity is calculated as whether the
#' supporting plane and supporting line intersects at a point.
#'
#' @param x,y vectors of geometries
#'
#' @return a logical vector giving the parallelity of the input
#'
#' @export
#'
#' @examples
#' # Are two triangles parallel (only meaningful in 3D)
#' p <- point(sample(20, 6), sample(20, 6), sample(20, 6))
#' t1 <- triangle(p[1], p[2], p[3])
#' t2 <- triangle(p[4], p[5], p[6])
#'
#' parallel(t1, t2)
#'
#' # Same as:
#' parallel(as_plane(t1), as_plane(t2))
#'
#' # Parallelity of surface and curve
#' parallel(t1, line(p[5], p[6]))
#'
parallel <- function(x, y) {
  check_geometry_input(x, y, .name = "parallel()")
  if (geometry_type(x) == geometry_type(y)) {
    if (is_surface(x)) {
      x <- as_plane(x)
      y <- as_plane(y)
    }
    geometry_parallel(get_ptr(x), get_ptr(y))
  } else {
    is_surface_x <- is_surface(x)
    x <- if (is_surface_x) as_plane(x) else as_line(x)
    is_surface_y <- is_surface(y)
    y <- if (is_surface_y) as_plane(y) else as_line(y)
    if (is_surface_x != is_surface_y) {
      is.na(intersection_point(x, y))
    } else {
      geometry_parallel(get_ptr(x), get_ptr(y))
    }
  }
}

#' Check geometries for whether they are collinear or coplanar
#'
#' Geometries are collinear if they lie on the same line and coplanar if they
#' lie on the same plane. collinearity can be tested between two curves or three
#' points, weighted points, circles, or spheres. coplanarity can be tested
#' between two surfaces or 4 points, weighted points, or spheres
#'
#' @param x,y,z,t Vector of geometries.
#'
#' @return A logical vector
#'
#' @export
#'
#' @examples
#' # Collinear points
#' collinear(point(0, 0), point(1, 1), point(2, 2))
#'
#' # Coplanar triangles
#' coplanar(
#'   triangle(point(0, 0, 0), point(1, 1, 1), point(1, 1, 0)),
#'   triangle(point(0, 0, 0), point(-1, -1, -1), point(-1, -1, 0))
#' )
#'
collinear <- function(x, y, z = NULL) {
  check_geometry_input(x, y, z, .name = "collinear()")
  if (is.null(z)) {
    x <- as_line(x)
    y <- as_line(y)
    has_intersection(x, vertex(y)) && parallel(x, y)
  } else {
    if (is_circle(x) || is_sphere(x) || is_weighted_point(x)) x <- vertex(x)
    if (is_circle(y) || is_sphere(y) || is_weighted_point(y)) y <- vertex(y)
    if (is_circle(z) || is_sphere(z) || is_weighted_point(z)) z <- vertex(z)
    point_collinear(get_ptr(x), get_ptr(y), get_ptr(z))
  }
}
#' @rdname collinear
#' @export
coplanar <- function(x, y, z = NULL, t = NULL) {
  check_geometry_input(x, y, z, t, .name = "coplanar()")
  if (is.null(z)) {
    x <- as_plane(x)
    y <- as_plane(y)
    has_intersection(x, vertex(y)) && parallel(x, y)
  }else {
    if (is_sphere(x) || is_weighted_point(x)) x <- vertex(x)
    if (is_sphere(y) || is_weighted_point(y)) y <- vertex(y)
    if (is_sphere(z) || is_weighted_point(z)) z <- vertex(z)
    if (is_sphere(t) || is_weighted_point(t)) t <- vertex(t)
    point_coplanar(get_ptr(x), get_ptr(y), get_ptr(z), get_ptr(t))
  }
}

#' Query the side of the turn constructed by three consecutive points
#'
#' In 2D the bend three consecutive points form can be oriented either to the
#' left or two the right. Asking whether it takes a left turn is equivalent to
#' asking whether `z` lies on the positive side of the supporting line of
#' `x`->`y`. euclid provides two predicate functions to check whether left or
#' right turns are constructed from three given point vectors (note that
#' collinear points will be `FALSE` for both predicates). It also provides a
#' function that calculate turn orientation along a single vector of points. The
#' result of this are given as: `1` (left), `0` (collinear), or `-1` (right).
#' Note that the output of `turn_along()` is two elements shorter than the
#' input.
#'
#' @param x,y,z Vectors of 2D points
#'
#' @return Either a logical vector or an integer vector (for `turn_along()`)
#'
#' @rdname geometry_turns
#' @name geometry_turns
#'
#' @examples
#' p <- point(sample(20, 12), sample(20, 12))
#'
#' turns_left(p[1:4], p[5:8], p[9:12])
#'
#' turn_along(p)
#'
NULL
#' @rdname geometry_turns
#' @export
turns_left <- function(x, y, z) {
  check_geometry_input(x, y, z, .name = "turns_left()")
  if (is_weighted_point(x)) x <- as_point(x)
  if (is_weighted_point(y)) y <- as_point(y)
  if (is_weighted_point(z)) z <- as_point(z)
  if (!is_point(x) || !is_point(y) || !is_point(z)) {
    rlang::abort("`turns_left()` is only defined for 2D points")
  }
  point_turns_left(get_ptr(x), get_ptr(y), get_ptr(z))
}
#' @rdname geometry_turns
#' @export
turns_right <- function(x, y, z) {
  check_geometry_input(x, y, z, .name = "turns_right()")
  if (is_weighted_point(x)) x <- as_point(x)
  if (is_weighted_point(y)) y <- as_point(y)
  if (is_weighted_point(z)) z <- as_point(z)
  if (!is_point(x) || !is_point(y) || !is_point(z) || dim(x) != 2) {
    rlang::abort("`turns_right()` is only defined for 2D points")
  }
  point_turns_right(get_ptr(x), get_ptr(y), get_ptr(z))
}
#' @rdname geometry_turns
#' @export
turn_along <- function(x) {
  if (is_weighted_point(x)) x <- as_point(x)
  if (!is_point(x) || dim(x) != 2) {
    rlang::abort("`turn_along()` is only defined for 2D points")
  }
  if (length(x) < 3) {
    rlang::abort("`turn_along()` needs at least 3 points")
  }
  point_turns(get_ptr(x))
}

#' Check whether points are collinear and ordered along the line
#'
#' If points are [collinear] it is possible to ask whether they are ordered
#' along the common line. This function is not strict, i.e. it is possible for
#' the middle point to coincide with either the first or last point and still be
#' regarded as ordered between them. This functionality comes in two versions,
#' one that access orderedness between three vectors of points and one that
#' assess it along a single vector. Note that for the later version the return
#' value is 2 elements shorter than the input vector.
#'
#' @param x,y,z Vectors of points
#'
#' @return A logical vector
#'
#' @export
#'
#' @examples
#' p <- point(1:30, 1:30)
#' p <- p[sample(30)]
#'
#' in_order(p[1:10], p[11:20], p[21:30])
#'
#' in_order_along(p)
#'
in_order <- function(x, y, z) {
  check_geometry_input(x, y, z, .name = "in_order()")
  if (is_weighted_point(x)) x <- as_point(x)
  if (is_weighted_point(y)) y <- as_point(y)
  if (is_weighted_point(z)) z <- as_point(z)
  if (!is_point(x) || !is_point(y) || !is_point(z)) {
    rlang::abort("`in_order()` is only defined for points")
  }
  point_ordered(get_ptr(x), get_ptr(y), get_ptr(z))
}
#' @rdname in_order
#' @export
in_order_along <- function(x) {
  if (is_weighted_point(x)) x <- as_point(x)
  if (!is_point(x)) {
    rlang::abort("`in_order_along()` is only defined for points")
  }
  if (length(x) < 3) {
    rlang::abort("`in_order_along()` needs at least 3 points")
  }
  point_ordered_along(get_ptr(x))
}
