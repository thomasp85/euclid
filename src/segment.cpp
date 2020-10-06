#include "segment.h"
#include "point.h"
#include "vector.h"

#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
segment2_p create_segment_2_empty() {
  std::vector<Segment_2> vec;
  segment2 *result(new segment2(vec));
  return {result};
}

[[cpp11::register]]
segment2_p create_segment_2_p_q(point2_p p, point2_p q) {
  std::vector<Segment_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Segment_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  segment2 *result(new segment2(vec));

  return {result};
}

[[cpp11::register]]
segment2_p create_segment_2_p_v(point2_p p, vector2_p v) {
  std::vector<Segment_2> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Segment_2::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*p)[i] + (*v)[i]);
  }
  segment2 *result(new segment2(vec));

  return {result};
}

[[cpp11::register]]
segment2_p segment_2_negate(segment2_p x) {
  std::vector<Segment_2> vec = -(*x);
  segment2 *result(new segment2(vec));

  return {result};
}

[[cpp11::register]]
segment3_p create_segment_3_empty() {
  std::vector<Segment_3> vec;
  segment3 *result(new segment3(vec));
  return {result};
}

[[cpp11::register]]
segment3_p create_segment_3_p_q(point3_p p, point3_p q) {
  std::vector<Segment_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*q)[i]) {
      vec.push_back(Segment_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*q)[i]);
  }
  segment3 *result(new segment3(vec));

  return {result};
}

[[cpp11::register]]
segment3_p create_segment_3_p_v(point3_p p, vector3_p v) {
  std::vector<Segment_3> vec;
  vec.reserve(p->size());
  for (size_t i = 0; i < p->size(); ++i) {
    if (!(*p)[i] || !(*v)[i]) {
      vec.push_back(Segment_3::NA_value());
      continue;
    }
    vec.emplace_back((*p)[i], (*p)[i] + (*v)[i]);
  }
  segment3 *result(new segment3(vec));

  return {result};
}

[[cpp11::register]]
segment3_p segment_3_negate(segment3_p x) {
  std::vector<Segment_3> vec = -(*x);
  segment3 *result(new segment3(vec));

  return {result};
}
