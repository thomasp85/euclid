#include "geometry_vector.h"

#include <cpp11/doubles.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
cpp11::writable::doubles_matrix circle_2_to_matrix(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->as_numeric();
}
