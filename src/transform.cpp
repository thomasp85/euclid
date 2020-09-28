#include "transform.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>

#include <CGAL/aff_transformation_tags.h>

#include "vector.h"

[[cpp11::register]]
transform2_p create_transform_2_identity(int n) {
  std::vector<Aff_transformation_2> vec;
  vec.reserve(n);
  for (int i = 0; i < n; ++i) {
    vec.emplace_back(CGAL::IDENTITY);
  }

  transform2 *result(new transform2(vec));

  return {result};
}

[[cpp11::register]]
transform2_p create_transform_2_matrix(cpp11::list_of<cpp11::doubles_matrix> matrices) {
  std::vector<Aff_transformation_2> vec;
  vec.reserve(matrices.size());
  for (int i = 0; i < matrices.size(); ++i) {
    if (R_finite(matrices[i](0, 0))) {
      vec.emplace_back(matrices[i](0, 0), matrices[i](0, 1), matrices[i](0, 2),
                       matrices[i](1, 0), matrices[i](1, 1), matrices[i](1, 2),
                                                             matrices[i](2, 2));
    } else {
      vec.push_back(Aff_transformation_2::NA_value());
    }
  }

  transform2 *result(new transform2(vec));

  return {result};
}

[[cpp11::register]]
transform2_p create_transform_2_translate(vector2_p trans) {
  std::vector<Aff_transformation_2> vec;
  vec.reserve(trans->size());
  for (int i = 0; i < trans->size(); ++i) {
    if (!(*trans)[i]) {
      vec.push_back(Aff_transformation_2::NA_value());
    } else {
      vec.emplace_back(CGAL::TRANSLATION, (*trans)[i]);
    }
  }

  transform2 *result(new transform2(vec));

  return {result};
}

[[cpp11::register]]
transform2_p create_transform_2_rotate(exact_numeric_p rho) {
  std::vector<Aff_transformation_2> vec;
  vec.reserve(rho->size());
  for (int i = 0; i < rho->size(); ++i) {
    if (!(*rho)[i]) {
      vec.push_back(Aff_transformation_2::NA_value());
    } else {
      double inexact_rho = CGAL::to_double((*rho)[i].exact());
      vec.emplace_back(CGAL::ROTATION, std::sin(inexact_rho), std::cos(inexact_rho));
    }
  }

  transform2 *result(new transform2(vec));

  return {result};
}

[[cpp11::register]]
transform2_p create_transform_2_scale(exact_numeric_p fac) {
  std::vector<Aff_transformation_2> vec;
  vec.reserve(fac->size());
  for (int i = 0; i < fac->size(); ++i) {
    if (!(*fac)[i]) {
      vec.push_back(Aff_transformation_2::NA_value());
    } else {
      vec.emplace_back(CGAL::SCALING, (*fac)[i]);
    }
  }

  transform2 *result(new transform2(vec));

  return {result};
}

[[cpp11::register]]
transform3_p create_transform_3_identity(int n) {
  std::vector<Aff_transformation_3> vec;
  vec.reserve(n);
  for (int i = 0; i < n; ++i) {
    vec.emplace_back(CGAL::IDENTITY);
  }

  transform3 *result(new transform3(vec));

  return {result};
}

[[cpp11::register]]
transform3_p create_transform_3_matrix(cpp11::list_of<cpp11::doubles_matrix> matrices) {
  std::vector<Aff_transformation_3> vec;
  vec.reserve(matrices.size());
  for (int i = 0; i < matrices.size(); ++i) {
    if (R_finite(matrices[i](0, 0))) {
      vec.emplace_back(matrices[i](0, 0), matrices[i](0, 1), matrices[i](0, 2), matrices[i](0, 3),
                       matrices[i](1, 0), matrices[i](1, 1), matrices[i](1, 2), matrices[i](1, 3),
                       matrices[i](2, 0), matrices[i](2, 1), matrices[i](2, 2), matrices[i](2, 3),
                                                                                matrices[i](3, 3));
    } else {
      vec.push_back(Aff_transformation_3::NA_value());
    }
  }

  transform3 *result(new transform3(vec));

  return {result};
}

[[cpp11::register]]
transform3_p create_transform_3_translate(vector3_p trans) {
  std::vector<Aff_transformation_3> vec;
  vec.reserve(trans->size());
  for (int i = 0; i < trans->size(); ++i) {
    if (!(*trans)[i]) {
      vec.push_back(Aff_transformation_3::NA_value());
    } else {
      vec.emplace_back(CGAL::TRANSLATION, (*trans)[i]);
    }
  }

  transform3 *result(new transform3(vec));

  return {result};
}

[[cpp11::register]]
transform3_p create_transform_3_scale(exact_numeric_p fac) {
  std::vector<Aff_transformation_3> vec;
  vec.reserve(fac->size());
  for (int i = 0; i < fac->size(); ++i) {
    if (!(*fac)[i]) {
      vec.push_back(Aff_transformation_3::NA_value());
    } else {
      vec.emplace_back(CGAL::SCALING, (*fac)[i]);
    }
  }

  transform3 *result(new transform3(vec));

  return {result};
}


[[cpp11::register]]
int transform_length(transform_vector_base_p transforms) {
  return transforms->size();
}

[[cpp11::register]]
int transform_dimension(transform_vector_base_p transforms) {
  return transforms->dimensions();
}

[[cpp11::register]]
exact_numeric_p transform_definition(transform_vector_base_p transforms, int i, int j) {
  exact_numeric* vec(new exact_numeric(transforms->definition(i, j)));
  return {vec};
}

[[cpp11::register]]
transform_vector_base_p transform_subset(transform_vector_base_p transforms, cpp11::integers index) {
  return transforms->subset(index);
}

[[cpp11::register]]
transform_vector_base_p transform_copy(transform_vector_base_p transforms) {
  return transforms->copy();
}

[[cpp11::register]]
transform_vector_base_p transform_assign(transform_vector_base_p transforms, cpp11::integers index, transform_vector_base_p value) {
  return transforms->assign(index, *value);
}

[[cpp11::register]]
transform_vector_base_p transform_combine(transform_vector_base_p transforms, cpp11::list_of< transform_vector_base_p > extra) {
  return transforms->combine(extra);
}

[[cpp11::register]]
transform_vector_base_p transform_unique(transform_vector_base_p transforms) {
  return transforms->unique();
}

[[cpp11::register]]
cpp11::writable::logicals transform_duplicated(transform_vector_base_p transforms) {
  return transforms->duplicated();
}

[[cpp11::register]]
cpp11::writable::integers transform_any_duplicated(transform_vector_base_p transforms) {
  return {transforms->any_duplicated() + 1};
}

[[cpp11::register]]
cpp11::writable::integers transform_match(transform_vector_base_p transforms, transform_vector_base_p table) {
  return transforms->match(*table);
}

[[cpp11::register]]
cpp11::writable::logicals transform_is_na(transform_vector_base_p transforms) {
  return transforms->is_na();
}

[[cpp11::register]]
bool transform_any_na(transform_vector_base_p transforms) {
  return transforms->any_na();
}

[[cpp11::register]]
cpp11::writable::doubles transform_to_array(transform_vector_base_p transforms) {
  return transforms->as_numeric();
}

[[cpp11::register]]
cpp11::writable::strings transform_format(transform_vector_base_p transforms) {
  return transforms->format();
}

[[cpp11::register]]
cpp11::writable::logicals transform_is_equal(transform_vector_base_p transforms1,
                                            transform_vector_base_p transforms2) {
  return (*transforms1) == (*transforms2);
}

[[cpp11::register]]
cpp11::writable::logicals transform_is_not_equal(transform_vector_base_p transforms1,
                                                transform_vector_base_p transforms2) {
  return (*transforms1) != (*transforms2);
}

[[cpp11::register]]
transform_vector_base_p transform_multiply(transform_vector_base_p transforms, transform_vector_base_p other) {
  return (*transforms) * (*other);
}

[[cpp11::register]]
transform_vector_base_p transform_inverse(transform_vector_base_p transforms) {
  return transforms->inverse();
}

[[cpp11::register]]
cpp11::writable::logicals transform_is_reflecting(transform_vector_base_p transforms) {
  return transforms->is_reflecting();
}
