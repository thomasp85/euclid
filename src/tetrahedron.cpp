#include "tetrahedron.h"
#include "point.h"

[[cpp11::register]]
tetrahedron_p create_tetrahedron_empty() {
  std::vector<Tetrahedron> vec;
  tetrahedron *result(new tetrahedron(vec));
  return {result};
}

[[cpp11::register]]
tetrahedron_p create_tetrahedron_4points(point3_p p, point3_p q, point3_p r, point3_p s) {
  std::vector<Tetrahedron> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i] || !(*r)[i] || !(*s)[i]) {
      vec.push_back(Tetrahedron::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i], (*r)[i], (*s)[i]);
  }
  tetrahedron *result(new tetrahedron(vec));

  return {result};
}
