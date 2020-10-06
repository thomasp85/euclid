#include "triangle.h"
#include "point.h"

[[cpp11::register]]
triangle2_p create_triangle_2_empty() {
  std::vector<Triangle_2> vec;
  triangle2 *result(new triangle2(vec));
  return {result};
}

[[cpp11::register]]
triangle2_p create_triangle_2_3points(point2_p p, point2_p q, point2_p r) {
  std::vector<Triangle_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i]) {
      vec.push_back(Triangle_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  triangle2 *result(new triangle2(vec));

  return {result};
}

[[cpp11::register]]
triangle3_p create_triangle_3_empty() {
  std::vector<Triangle_3> vec;
  triangle3 *result(new triangle3(vec));
  return {result};
}

[[cpp11::register]]
triangle3_p create_triangle_3_3points(point3_p p, point3_p q, point3_p r) {
  std::vector<Triangle_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i]) {
      vec.push_back(Triangle_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i]);
  }
  triangle3 *result(new triangle3(vec));

  return {result};
}
