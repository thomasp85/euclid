#include "iso_cube.h"
#include "point.h"
#include "bbox.h"

[[cpp11::register]]
iso_cube_p create_iso_cube_empty() {
  std::vector<Iso_cuboid> vec;
  iso_cube *result(new iso_cube(vec));
  return {result};
}

[[cpp11::register]]
iso_cube_p create_iso_cube_pq(point3_p p, point3_p q) {
  std::vector<Iso_cuboid> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Iso_cuboid::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  iso_cube *result(new iso_cube(vec));

  return {result};
}

[[cpp11::register]]
iso_cube_p create_iso_cube_lrbtfc(point3_p l, point3_p r, point3_p b, point3_p t, point3_p f, point3_p c) {
  std::vector<Iso_cuboid> vec;
  vec.reserve(l->size());
  for (size_t i = 0; i < l->size(); ++i) {
    if (!(*l)[i] || !(*r)[i] || !(*b)[i] || !(*t)[i] || !(*f)[i] || !(*c)[i]) {
      vec.push_back(Iso_cuboid::NA_value());
      continue;
    }
    vec.emplace_back((*l)[i], (*r)[i], (*b)[i], (*t)[i], (*f)[i], (*c)[i]);
  }
  iso_cube *result(new iso_cube(vec));

  return {result};
}

[[cpp11::register]]
iso_cube_p create_iso_cube_bbox(bbox3_p bbox) {
  std::vector<Iso_cuboid> vec;
  vec.reserve(bbox->size());
  for (size_t i = 0; i < bbox->size(); ++i) {
    if (!(*bbox)[i]) {
      vec.push_back(Iso_cuboid::NA_value());
      continue;
    }
    vec.emplace_back((*bbox)[i]);
  }
  iso_cube *result(new iso_cube(vec));

  return {result};
}
