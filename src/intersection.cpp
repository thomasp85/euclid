#include "geometry_vector.h"
#include <cpp11/list.hpp>

[[cpp11::register]]
cpp11::writable::list geometry_intersection(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  return geo1->intersection(*geo2);
}
