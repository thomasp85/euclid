#include "iso_rect.h"
#include "point.h"
#include "bbox.h"

[[cpp11::register]]
iso_rect_p create_iso_rect_empty() {
  std::vector<Iso_rectangle> vec;
  iso_rect *result(new iso_rect(vec));
  return {result};
}

[[cpp11::register]]
iso_rect_p create_iso_rect_pq(point2_p p, point2_p q) {
  std::vector<Iso_rectangle> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Iso_rectangle::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  iso_rect *result(new iso_rect(vec));

  return {result};
}

[[cpp11::register]]
iso_rect_p create_iso_rect_lrbt(point2_p l, point2_p r, point2_p b, point2_p t) {
  std::vector<Iso_rectangle> vec;
  vec.reserve(l->size());
  for (size_t i = 0; i < l->size(); ++i) {
    if (!(*l)[i] || !(*r)[i] || !(*b)[i] || !(*t)[i]) {
      vec.push_back(Iso_rectangle::NA_value());
      continue;
    }
    vec.emplace_back((*l)[i], (*r)[i], (*b)[i], (*t)[i]);
  }
  iso_rect *result(new iso_rect(vec));

  return {result};
}

[[cpp11::register]]
iso_rect_p create_iso_rect_bbox(bbox2_p bbox) {
  std::vector<Iso_rectangle> vec;
  vec.reserve(bbox->size());
  for (size_t i = 0; i < bbox->size(); ++i) {
    if (!(*bbox)[i]) {
      vec.push_back(Iso_rectangle::NA_value());
      continue;
    }
    vec.emplace_back((*bbox)[i]);
  }
  iso_rect *result(new iso_rect(vec));

  return {result};
}
