#include "geometry_vector.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
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
cpp11::writable::integers geometry_cardinality(cpp11::external_pointer<geometry_vector_base> geometries) {
  cpp11::writable::integers result;
  result.reserve(geometries->size());
  for (size_t i = 0; i < geometries->size(); ++i) {
    result.push_back(geometries->cardinality(i));
  }
  return result;
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
cpp11::external_pointer<geometry_vector_base> geometry_assign(cpp11::external_pointer<geometry_vector_base> geometries, cpp11::integers index, cpp11::external_pointer<geometry_vector_base> value) {
  return geometries->assign(index, *value);
}

[[cpp11::register]]
cpp11::external_pointer<geometry_vector_base> geometry_combine(cpp11::external_pointer<geometry_vector_base> geometries, cpp11::list_of< cpp11::external_pointer<geometry_vector_base> > extra) {
  return geometries->combine(extra);
}

[[cpp11::register]]
cpp11::external_pointer<geometry_vector_base> geometry_unique(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->unique();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_duplicated(cpp11::external_pointer<geometry_vector_base> geometries) {
  return geometries->duplicated();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_any_duplicated(cpp11::external_pointer<geometry_vector_base> geometries) {
  return {(Rboolean) geometries->any_duplicated()};
}

[[cpp11::register]]
cpp11::writable::integers geometry_match(cpp11::external_pointer<geometry_vector_base> geometries, cpp11::external_pointer<geometry_vector_base> table) {
  return geometries->match(*table);
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

