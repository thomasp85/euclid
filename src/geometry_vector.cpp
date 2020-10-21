#include "geometry_vector.h"
#include "point.h"
#include "direction.h"

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
geometry_vector_base_p create_geometry_vector(std::vector<Direction_2>& input) {
  direction2* vec = new direction2(input);
  return {vec};
}
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Direction_3>& input) {
  direction3* vec = new direction3(input);
  return {vec};
}
