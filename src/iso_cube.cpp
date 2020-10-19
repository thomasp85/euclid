#include "iso_cube.h"
#include "point.h"
#include "exact_numeric.h"
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
iso_cube_p create_iso_cube_minmax(exact_numeric_p minx, exact_numeric_p miny, exact_numeric_p minz, exact_numeric_p maxx, exact_numeric_p maxy, exact_numeric_p maxz) {
  std::vector<Iso_cuboid> vec;
  vec.reserve(minx->size());
  for (size_t i = 0; i < minx->size(); ++i) {
    if (!(*minx)[i] || !(*miny)[i] || !(*minz)[i] || !(*maxx)[i] || !(*maxy)[i] || !(*maxz)[i]) {
      vec.push_back(Iso_cuboid::NA_value());
      continue;
    }
    vec.emplace_back((*minx)[i], (*miny)[i], (*minz)[i], (*maxx)[i], (*maxy)[i], (*maxz)[i]);
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
