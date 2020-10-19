#include "geometry_vector.h"

#include <cpp11/logicals.hpp>

[[cpp11::register]]
cpp11::writable::logicals geometry_is_degenerate(geometry_vector_base_p geometries) {
  return geometries->is_degenerate();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_inside(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_inside(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_outside(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_outside(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on_positive(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on_positive(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on_negative(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on_negative(*points);
}
