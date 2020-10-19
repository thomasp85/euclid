#include <cpp11/R.hpp>
#include "cgal_types.h"
#include <CGAL/enum.h>

// has_inside_impl -------------------------------------------------------------

template<typename T, typename Point>
inline int has_inside_impl(const T& geo, const Point& p) {
  return geo.bounded_side(p) == CGAL::ON_BOUNDED_SIDE;
}
template<>
inline int has_inside_impl<Circle_3, Point_3>(const Circle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Point_2, Point_2>(const Point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Point_3, Point_3>(const Point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Plane, Point_3>(const Plane& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Vector_2, Point_2>(const Vector_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Vector_3, Point_3>(const Vector_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Direction_2, Point_2>(const Direction_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Direction_3, Point_3>(const Direction_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Line_2, Point_2>(const Line_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Line_3, Point_3>(const Line_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Weighted_point_2, Point_2>(const Weighted_point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Weighted_point_3, Point_3>(const Weighted_point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Ray_2, Point_2>(const Ray_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Ray_3, Point_3>(const Ray_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Segment_2, Point_2>(const Segment_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Segment_3, Point_3>(const Segment_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_inside_impl<Triangle_3, Point_3>(const Triangle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}

// has_on_impl -----------------------------------------------------------------

template<typename T, typename Point>
inline int has_on_impl(const T& geo, const Point& p) {
  return geo.bounded_side(p) == CGAL::ON_BOUNDARY;
}
template<>
inline int has_on_impl<Circle_3, Point_3>(const Circle_3& geo, const Point_3& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Point_2, Point_2>(const Point_2& geo, const Point_2& p) {
  return geo == p;
}
template<>
inline int has_on_impl<Point_3, Point_3>(const Point_3& geo, const Point_3& p) {
  return geo == p;
}
template<>
inline int has_on_impl<Plane, Point_3>(const Plane& geo, const Point_3& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Vector_2, Point_2>(const Vector_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_impl<Vector_3, Point_3>(const Vector_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_impl<Direction_2, Point_2>(const Direction_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_impl<Direction_3, Point_3>(const Direction_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_impl<Line_2, Point_2>(const Line_2& geo, const Point_2& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Line_3, Point_3>(const Line_3& geo, const Point_3& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Weighted_point_2, Point_2>(const Weighted_point_2& geo, const Point_2& p) {
  return geo.point() == p;
}
template<>
inline int has_on_impl<Weighted_point_3, Point_3>(const Weighted_point_3& geo, const Point_3& p) {
  return geo.point() == p;
}
template<>
inline int has_on_impl<Ray_2, Point_2>(const Ray_2& geo, const Point_2& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Ray_3, Point_3>(const Ray_3& geo, const Point_3& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Segment_2, Point_2>(const Segment_2& geo, const Point_2& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Segment_3, Point_3>(const Segment_3& geo, const Point_3& p) {
  return geo.has_on(p);
}
template<>
inline int has_on_impl<Triangle_3, Point_3>(const Triangle_3& geo, const Point_3& p) {
  return geo.has_on(p);
}

// has_outside_impl ------------------------------------------------------------

template<typename T, typename Point>
inline int has_outside_impl(const T& geo, const Point& p) {
  return geo.bounded_side(p) == CGAL::ON_UNBOUNDED_SIDE;
}
template<>
inline int has_outside_impl<Circle_3, Point_3>(const Circle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Point_2, Point_2>(const Point_2& geo, const Point_2& p) {
  return geo != p;
}
template<>
inline int has_outside_impl<Point_3, Point_3>(const Point_3& geo, const Point_3& p) {
  return geo != p;
}
template<>
inline int has_outside_impl<Plane, Point_3>(const Plane& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Vector_2, Point_2>(const Vector_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Vector_3, Point_3>(const Vector_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Direction_2, Point_2>(const Direction_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Direction_3, Point_3>(const Direction_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Line_2, Point_2>(const Line_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Line_3, Point_3>(const Line_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Weighted_point_2, Point_2>(const Weighted_point_2& geo, const Point_2& p) {
  return geo.point() != p;
}
template<>
inline int has_outside_impl<Weighted_point_3, Point_3>(const Weighted_point_3& geo, const Point_3& p) {
  return geo.point() != p;
}
template<>
inline int has_outside_impl<Ray_2, Point_2>(const Ray_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Ray_3, Point_3>(const Ray_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Segment_2, Point_2>(const Segment_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Segment_3, Point_3>(const Segment_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_outside_impl<Triangle_3, Point_3>(const Triangle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}

// has_on_positive_impl --------------------------------------------------------

template<typename T, typename Point>
inline int has_on_positive_impl(const T& geo, const Point& p) {
  return geo.oriented_side(p) == CGAL::ON_POSITIVE_SIDE;
}
template<>
inline int has_on_positive_impl<Circle_3, Point_3>(const Circle_3& geo, const Point_3& p) {
  return has_on_positive_impl(geo.supporting_plane(), p);
}
template<>
inline int has_on_positive_impl<Point_2, Point_2>(const Point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Point_3, Point_3>(const Point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Vector_2, Point_2>(const Vector_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Vector_3, Point_3>(const Vector_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Direction_2, Point_2>(const Direction_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Direction_3, Point_3>(const Direction_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Iso_rectangle, Point_2>(const Iso_rectangle& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Iso_cuboid, Point_3>(const Iso_cuboid& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Line_3, Point_3>(const Line_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Weighted_point_2, Point_2>(const Weighted_point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Weighted_point_3, Point_3>(const Weighted_point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Ray_2, Point_2>(const Ray_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Ray_3, Point_3>(const Ray_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Segment_2, Point_2>(const Segment_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Segment_3, Point_3>(const Segment_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_positive_impl<Triangle_3, Point_3>(const Triangle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}

// has_on_negative_impl --------------------------------------------------------

template<typename T, typename Point>
inline int has_on_negative_impl(const T& geo, const Point& p) {
  return geo.oriented_side(p) == CGAL::ON_NEGATIVE_SIDE;
}
template<>
inline int has_on_negative_impl<Circle_3, Point_3>(const Circle_3& geo, const Point_3& p) {
  return has_on_negative_impl(geo.supporting_plane(), p);
}
template<>
inline int has_on_negative_impl<Point_2, Point_2>(const Point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Point_3, Point_3>(const Point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Vector_2, Point_2>(const Vector_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Vector_3, Point_3>(const Vector_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Direction_2, Point_2>(const Direction_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Direction_3, Point_3>(const Direction_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Iso_rectangle, Point_2>(const Iso_rectangle& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Iso_cuboid, Point_3>(const Iso_cuboid& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Line_3, Point_3>(const Line_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Weighted_point_2, Point_2>(const Weighted_point_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Weighted_point_3, Point_3>(const Weighted_point_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Ray_2, Point_2>(const Ray_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Ray_3, Point_3>(const Ray_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Segment_2, Point_2>(const Segment_2& geo, const Point_2& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Segment_3, Point_3>(const Segment_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
template<>
inline int has_on_negative_impl<Triangle_3, Point_3>(const Triangle_3& geo, const Point_3& p) {
  return NA_LOGICAL;
}
