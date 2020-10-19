#include "geometry_vector.h"

#include <cpp11/doubles.hpp>

[[cpp11::register]]
cpp11::writable::doubles geometry_approx_length(geometry_vector_base_p geometries) {
  return geometries->length();
}
[[cpp11::register]]
cpp11::writable::doubles geometry_approx_area(geometry_vector_base_p geometries) {
  return geometries->area();
}
[[cpp11::register]]
cpp11::writable::doubles geometry_approx_volume(geometry_vector_base_p geometries) {
  return geometries->volume();
}
