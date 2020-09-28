#include "geometry_vector.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
int geometry_length(geometry_vector_base_p geometries) {
  return geometries->size();
}

[[cpp11::register]]
int geometry_dimension(geometry_vector_base_p geometries) {
  return geometries->dimensions();
}

[[cpp11::register]]
cpp11::writable::strings geometry_definition_names(geometry_vector_base_p geometries) {
  return geometries->def_names();
}

[[cpp11::register]]
exact_numeric_p geometry_definition(geometry_vector_base_p geometries, int which, cpp11::integers element) {
  exact_numeric* vec(new exact_numeric(geometries->definition(which, element)));
  return {vec};
}

[[cpp11::register]]
cpp11::writable::integers geometry_cardinality(geometry_vector_base_p geometries) {
  cpp11::writable::integers result;
  result.reserve(geometries->size());
  for (size_t i = 0; i < geometries->size(); ++i) {
    result.push_back(geometries->cardinality(i));
  }
  return result;
}

[[cpp11::register]]
geometry_vector_base_p geometry_subset(geometry_vector_base_p geometries, cpp11::integers index) {
  return geometries->subset(index);
}

[[cpp11::register]]
geometry_vector_base_p geometry_copy(geometry_vector_base_p geometries) {
  return geometries->copy();
}

[[cpp11::register]]
geometry_vector_base_p geometry_assign(geometry_vector_base_p geometries, cpp11::integers index, geometry_vector_base_p value) {
  return geometries->assign(index, *value);
}

[[cpp11::register]]
geometry_vector_base_p geometry_combine(geometry_vector_base_p geometries, cpp11::list_of< geometry_vector_base_p > extra) {
  return geometries->combine(extra);
}

[[cpp11::register]]
geometry_vector_base_p geometry_unique(geometry_vector_base_p geometries) {
  return geometries->unique();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_duplicated(geometry_vector_base_p geometries) {
  return geometries->duplicated();
}

[[cpp11::register]]
cpp11::writable::integers geometry_any_duplicated(geometry_vector_base_p geometries) {
  return {geometries->any_duplicated() + 1};
}

[[cpp11::register]]
cpp11::writable::integers geometry_match(geometry_vector_base_p geometries, geometry_vector_base_p table) {
  return geometries->match(*table);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_na(geometry_vector_base_p geometries) {
  return geometries->is_na();
}

[[cpp11::register]]
bool geometry_any_na(geometry_vector_base_p geometries) {
  return geometries->any_na();
}

[[cpp11::register]]
cpp11::writable::doubles_matrix geometry_to_matrix(geometry_vector_base_p geometries) {
  return geometries->as_numeric();
}

[[cpp11::register]]
cpp11::writable::strings geometry_format(geometry_vector_base_p geometries) {
  return geometries->format();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_equal(geometry_vector_base_p geometries1,
                                            geometry_vector_base_p geometries2) {
  return (*geometries1) == (*geometries2);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_not_equal(geometry_vector_base_p geometries1,
                                                geometry_vector_base_p geometries2) {
  return (*geometries1) != (*geometries2);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_degenerate(geometry_vector_base_p geometries) {
  return geometries->is_degenerate();
}

[[cpp11::register]]
geometry_vector_base_p geometry_transform(geometry_vector_base_p geometries, transform_vector_base_p affine) {
  return geometries->transform(*affine);
}
