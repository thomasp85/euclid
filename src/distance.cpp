#include "geometry_vector.h"
#include "exact_numeric.h"
#include <cpp11/matrix.hpp>
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
exact_numeric_p geometry_squared_distance(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  std::vector<Exact_number> res = geo1->squared_distance(*geo2);
  exact_numeric* vec(new exact_numeric(res));
  return {vec};
}

[[cpp11::register]]
cpp11::writable::doubles_matrix geometry_distance_matrix(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  return geo1->distance_matrix(*geo2);
}
