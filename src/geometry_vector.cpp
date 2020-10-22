#include "geometry_vector.h"
#include "circle.h"
#include "direction.h"
#include "iso_cube.h"
#include "iso_rect.h"
#include "line.h"
#include "plane.h"
#include "point.h"
#include "point_w.h"
#include "ray.h"
#include "segment.h"
#include "sphere.h"
#include "tetrahedron.h"
#include "triangle.h"
#include "vector.h"

template<>
geometry_vector_base_p create_geometry_vector(std::vector<Circle_2>& input) {
  circle2* vec = new circle2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Circle_3>& input) {
  circle3* vec = new circle3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Direction_2>& input) {
  direction2* vec = new direction2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Direction_3>& input) {
  direction3* vec = new direction3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Iso_cuboid>& input) {
  iso_cube* vec = new iso_cube(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Iso_rectangle>& input) {
  iso_rect* vec = new iso_rect(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Line_2>& input) {
  line2* vec = new line2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Line_3>& input) {
  line3* vec = new line3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Plane>& input) {
  plane* vec = new plane(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Point_2>& input) {
  point2* vec = new point2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Point_3>& input) {
  point3* vec = new point3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Ray_2>& input) {
  ray2* vec = new ray2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Ray_3>& input) {
  ray3* vec = new ray3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Segment_2>& input) {
  segment2* vec = new segment2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Segment_3>& input) {
  segment3* vec = new segment3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Sphere>& input) {
  sphere* vec = new sphere(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Tetrahedron>& input) {
  tetrahedron* vec = new tetrahedron(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Triangle_2>& input) {
  triangle2* vec = new triangle2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Triangle_3>& input) {
  triangle3* vec = new triangle3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Vector_2>& input) {
  vector2* vec = new vector2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Vector_3>& input) {
  vector3* vec = new vector3(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Weighted_point_2>& input) {
  point_w2* vec = new point_w2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Weighted_point_3>& input) {
  point_w3* vec = new point_w3(input);
  return {vec};
}


template<>
const std::vector<Circle_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != CIRCLE || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional circles");
  }
  auto recast = dynamic_cast< const geometry_vector<Circle_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Circle_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != CIRCLE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional circles");
  }
  auto recast = dynamic_cast< const geometry_vector<Circle_3, 3, Circle_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Direction_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != DIRECTION || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional directions");
  }
  auto recast = dynamic_cast< const geometry_vector<Direction_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Direction_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != DIRECTION || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional directions");
  }
  auto recast = dynamic_cast< const geometry_vector<Direction_3, 3, Direction_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Iso_cuboid> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != ISOCUBE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain iso cubes");
  }
  auto recast = dynamic_cast< const geometry_vector<Iso_cuboid, 3>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Iso_rectangle> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != ISORECT || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain iso rectangles");
  }
  auto recast = dynamic_cast< const geometry_vector<Iso_rectangle, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Line_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != LINE || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional lines");
  }
  auto recast = dynamic_cast< const geometry_vector<Line_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Line_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != LINE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional lines");
  }
  auto recast = dynamic_cast< const geometry_vector<Line_3, 3, Line_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Plane> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != PLANE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain planes");
  }
  auto recast = dynamic_cast< const geometry_vector<Plane, 3>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Point_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != POINT || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional points");
  }
  auto recast = dynamic_cast< const geometry_vector<Point_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Point_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != POINT || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional points");
  }
  auto recast = dynamic_cast< const geometry_vector<Point_3, 3, Point_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Ray_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != RAY || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional rays");
  }
  auto recast = dynamic_cast< const geometry_vector<Ray_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Ray_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != RAY || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional rays");
  }
  auto recast = dynamic_cast< const geometry_vector<Ray_3, 3, Ray_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Segment_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != SEGMENT || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional segments");
  }
  auto recast = dynamic_cast< const geometry_vector<Segment_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Segment_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != SEGMENT || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional segments");
  }
  auto recast = dynamic_cast< const geometry_vector<Segment_3, 3, Segment_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Sphere> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != SPHERE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain spheres");
  }
  auto recast = dynamic_cast< const geometry_vector<Sphere, 3, Circle_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Tetrahedron> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != TETRAHEDRON || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain tetrahedrons");
  }
  auto recast = dynamic_cast< const geometry_vector<Tetrahedron, 3>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Triangle_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != TRIANGLE || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional triangles");
  }
  auto recast = dynamic_cast< const geometry_vector<Triangle_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Triangle_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != TRIANGLE || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional triangles");
  }
  auto recast = dynamic_cast< const geometry_vector<Triangle_3, 3, Triangle_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Vector_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != VECTOR || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional vectors");
  }
  auto recast = dynamic_cast< const geometry_vector<Vector_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Vector_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != VECTOR || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional vectors");
  }
  auto recast = dynamic_cast< const geometry_vector<Vector_3, 3, Vector_2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Weighted_point_2> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != WPOINT || geometries.dimensions() != 2) {
    cpp11::stop("Geometry must contain 2 dimensional weighted points");
  }
  auto recast = dynamic_cast< const geometry_vector<Weighted_point_2, 2>* >(&geometries);
  return recast->get_storage();
}
template<>
const std::vector<Weighted_point_3> get_vector_of_geo(const geometry_vector_base& geometries) {
  if (geometries.geometry_type() != WPOINT || geometries.dimensions() != 3) {
    cpp11::stop("Geometry must contain 3 dimensional weighted points");
  }
  auto recast = dynamic_cast< const geometry_vector<Weighted_point_3, 3, Weighted_point_2>* >(&geometries);
  return recast->get_storage();
}
