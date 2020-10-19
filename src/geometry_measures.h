#include <cpp11/R.hpp>
#include "cgal_types.h"

// length_impl -----------------------------------------------------------------
template<typename T>
inline double length_impl(const T& geo) {
  return R_NaReal;
}
template<>
inline double length_impl<Circle_2>(const Circle_2& geo) {
  return 2.0 * CGAL::sqrt(CGAL::to_double(geo.squared_radius().exact())) * M_PI;
}
template<>
inline double length_impl<Circle_3>(const Circle_3& geo) {
  return 2.0 * CGAL::sqrt(CGAL::to_double(geo.squared_radius().exact())) * M_PI;
}
template<>
inline double length_impl<Iso_rectangle>(const Iso_rectangle& geo) {
  Exact_number x_diff = geo.xmax() - geo.xmin();
  Exact_number y_diff = geo.ymax() - geo.ymin();
  return CGAL::to_double((x_diff * 2.0 + y_diff * 2.0).exact());
}
template<>
inline double length_impl<Segment_2>(const Segment_2& geo) {
  return CGAL::sqrt(CGAL::to_double(geo.squared_length().exact()));
}
template<>
inline double length_impl<Segment_3>(const Segment_3& geo) {
  return CGAL::sqrt(CGAL::to_double(geo.squared_length().exact()));
}
template<>
inline double length_impl<Triangle_2>(const Triangle_2& geo) {
  return length_impl(Segment_2(geo[0], geo[1])) +
    length_impl(Segment_2(geo[1], geo[2])) +
    length_impl(Segment_2(geo[2], geo[0]));
}
template<>
inline double length_impl<Triangle_3>(const Triangle_3& geo) {
  return length_impl(Segment_3(geo[0], geo[1])) +
    length_impl(Segment_3(geo[1], geo[2])) +
    length_impl(Segment_3(geo[2], geo[0]));
}
template<>
inline double length_impl<Vector_2>(const Vector_2& geo) {
  return CGAL::sqrt(CGAL::to_double(geo.squared_length().exact()));
}
template<>
inline double length_impl<Vector_3>(const Vector_3& geo) {
  return CGAL::sqrt(CGAL::to_double(geo.squared_length().exact()));
}
template<>
inline double length_impl<Line_2>(const Line_2& geo) {
  return R_PosInf;
}
template<>
inline double length_impl<Line_3>(const Line_3& geo) {
  return R_PosInf;
}
template<>
inline double length_impl<Ray_2>(const Ray_2& geo) {
  return R_PosInf;
}
template<>
inline double length_impl<Ray_3>(const Ray_3& geo) {
  return R_PosInf;
}

// area_impl -------------------------------------------------------------------

template<typename T>
inline double area_impl(const T& geo) {
  return R_NaReal;
}
template<>
inline double area_impl<Circle_2>(const Circle_2& geo) {
  return CGAL::to_double(geo.squared_radius().exact()) * M_PI;
}
template<>
inline double area_impl<Circle_3>(const Circle_3& geo) {
  return CGAL::to_double(geo.squared_radius().exact()) * M_PI;
}
template<>
inline double area_impl<Iso_rectangle>(const Iso_rectangle& geo) {
  return CGAL::to_double(geo.area().exact());
}
template<>
inline double area_impl<Iso_cuboid>(const Iso_cuboid& geo) {
  Exact_number x_diff = geo.xmax() - geo.xmin();
  Exact_number y_diff = geo.ymax() - geo.ymin();
  Exact_number z_diff = geo.zmax() - geo.zmin();
  return CGAL::to_double((x_diff * y_diff * 2.0 + y_diff * z_diff * 2.0 + z_diff * x_diff * 2.0).exact());
}
template<>
inline double area_impl<Sphere>(const Sphere& geo) {
  return CGAL::to_double(geo.squared_radius() * 4.0 * M_PI);
}
template<>
inline double area_impl<Triangle_2>(const Triangle_2& geo) {
  return CGAL::to_double(geo.area().exact());
}
template<>
inline double area_impl<Triangle_3>(const Triangle_3& geo) {
  return CGAL::sqrt(CGAL::to_double(geo.squared_area().exact()));
}
template<>
inline double area_impl<Tetrahedron>(const Tetrahedron& geo) {
  return area_impl(Triangle_3(geo[0], geo[1], geo[2])) +
    area_impl(Triangle_3(geo[0], geo[1], geo[3])) +
    area_impl(Triangle_3(geo[0], geo[2], geo[3])) +
    area_impl(Triangle_3(geo[1], geo[2], geo[3]));
}
template<>
inline double area_impl<Plane>(const Plane& geo) {
  return R_PosInf;
}

// volume_impl -----------------------------------------------------------------

template<typename T>
inline double volume_impl(const T& geo) {
  return R_NaReal;
}
template<>
inline double volume_impl<Iso_cuboid>(const Iso_cuboid& geo) {
  return CGAL::to_double(geo.volume().exact());
}
template<>
inline double volume_impl<Sphere>(const Sphere& geo) {
  double r = CGAL::sqrt(CGAL::to_double(geo.squared_radius().exact()));
  return r*r*r * M_PI * 4.0 / 3.0;
}
template<>
inline double volume_impl<Tetrahedron>(const Tetrahedron& geo) {
  return CGAL::to_double(geo.volume().exact());
}
