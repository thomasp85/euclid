#include "geometry_vector.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
int geometry_length(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->size();
}

[[cpp11::register]]
int geometry_dimension(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->dimensions();
}

[[cpp11::register]]
cpp11::external_pointer<geometry_vector_base> geometry_subset(cpp11::external_pointer<geometry_vector_base> geometries, cpp11::integers index) {
  return geometries->subset(index);
}

[[cpp11::register]]
cpp11::external_pointer<geometry_vector_base> geometry_copy(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->copy();
}

[[cpp11::register]]
cpp11::writable::doubles_matrix geometry_to_matrix(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->as_numeric();
}

[[cpp11::register]]
cpp11::writable::strings geometry_format(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->format();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_equal(cpp11::external_pointer<geometry_vector_base> geometries1,
                                            cpp11::external_pointer<geometry_vector_base> geometries2) {
  return (*geometries1) == (*geometries2);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_not_equal(cpp11::external_pointer<geometry_vector_base> geometries1,
                                                cpp11::external_pointer<geometry_vector_base> geometries2) {
  return (*geometries1) != (*geometries2);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_degenerate(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->is_degenerate();
}

