#include "bbox.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>

template<>
bbox_vector_base_p create_bbox_vector(std::vector<Bbox_2>& input) {
  bbox2* vec = new bbox2(input);
  return {vec};
}
template<>
bbox_vector_base_p create_bbox_vector(std::vector<Bbox_3>& input) {
  bbox3* vec = new bbox3(input);
  return {vec};
}
template<>
const std::vector<Bbox_2> get_vector_of_bbox(const bbox_vector_base& bboxes) {
  if (bboxes.dimensions() != 2) {
    cpp11::stop("Bounding boxes must be in 2 dimensions");
  }
  auto recast = dynamic_cast< const bbox_vector<Bbox_2, 2>* >(&bboxes);
  return recast->get_storage();
}
template<>
const std::vector<Bbox_3> get_vector_of_bbox(const bbox_vector_base& bboxes) {
  if (bboxes.dimensions() != 3) {
    cpp11::stop("Bounding boxes must be in 3 dimensions");
  }
  auto recast = dynamic_cast< const bbox_vector<Bbox_3, 3>* >(&bboxes);
  return recast->get_storage();
}

[[cpp11::register]]
bbox2_p create_bbox_2(cpp11::doubles xmin, cpp11::doubles ymin, cpp11::doubles xmax, cpp11::doubles ymax) {
  std::vector<Bbox_2> vec;
  vec.reserve(xmin.size());
  for (int i = 0; i < xmin.size(); ++i) {
    vec.emplace_back(xmin[i], ymin[i], xmax[i], ymax[i]);
  }

  bbox2 *result(new bbox2(vec));

  return {result};
}

[[cpp11::register]]
bbox3_p create_bbox_3(cpp11::doubles xmin, cpp11::doubles ymin, cpp11::doubles zmin, cpp11::doubles xmax, cpp11::doubles ymax, cpp11::doubles zmax) {
  std::vector<Bbox_3> vec;
  vec.reserve(xmin.size());
  for (int i = 0; i < xmin.size(); ++i) {
    vec.emplace_back(xmin[i], ymin[i], zmin[i], xmax[i], ymax[i], zmax[i]);
  }

  bbox3 *result(new bbox3(vec));

  return {result};
}

[[cpp11::register]]
int bbox_length(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    return 0;
  }
  return bboxes->size();
}

[[cpp11::register]]
int bbox_dimension(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    return 0;
  }
  return bboxes->dimensions();
}

[[cpp11::register]]
bbox_vector_base_p bbox_subset(bbox_vector_base_p bboxes, cpp11::integers index) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->subset(index);
}

[[cpp11::register]]
bbox_vector_base_p bbox_copy(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->copy();
}

[[cpp11::register]]
bbox_vector_base_p bbox_assign(bbox_vector_base_p bboxes, cpp11::integers index, bbox_vector_base_p value) {
  if (bboxes.get() == nullptr || value.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->assign(index, *value);
}

[[cpp11::register]]
bbox_vector_base_p bbox_combine(bbox_vector_base_p bboxes, cpp11::list_of< bbox_vector_base_p > extra) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->combine(extra);
}

[[cpp11::register]]
bbox_vector_base_p bbox_unique(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->unique();
}

[[cpp11::register]]
cpp11::writable::logicals bbox_duplicated(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->duplicated();
}

[[cpp11::register]]
cpp11::writable::integers bbox_any_duplicated(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return {bboxes->any_duplicated() + 1};
}

[[cpp11::register]]
cpp11::writable::integers bbox_match(bbox_vector_base_p bboxes, bbox_vector_base_p table) {
  if (bboxes.get() == nullptr || table.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->match(*table);
}

[[cpp11::register]]
cpp11::writable::logicals bbox_is_na(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->is_na();
}

[[cpp11::register]]
bool bbox_any_na(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->any_na();
}

[[cpp11::register]]
cpp11::writable::doubles_matrix bbox_to_matrix(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->as_numeric();
}

[[cpp11::register]]
cpp11::writable::strings bbox_format(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    return {">>>Data structure pointer cleared from memory<<<"};
  }
  return bboxes->format();
}

[[cpp11::register]]
cpp11::writable::logicals bbox_is_equal(bbox_vector_base_p bboxes1, bbox_vector_base_p bboxes2) {
  if (bboxes1.get() == nullptr || bboxes2.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return (*bboxes1) == (*bboxes2);
}

[[cpp11::register]]
bbox_vector_base_p bbox_plus(bbox_vector_base_p bboxes, bbox_vector_base_p other) {
  if (bboxes.get() == nullptr || other.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return (*bboxes) + (*other);
}

[[cpp11::register]]
bbox_vector_base_p bbox_sum(bbox_vector_base_p bboxes, bool na_rm) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->sum(na_rm);
}

[[cpp11::register]]
bbox_vector_base_p bbox_cumsum(bbox_vector_base_p bboxes) {
  if (bboxes.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes->cumsum();
}

[[cpp11::register]]
cpp11::writable::logicals bbox_overlaps(bbox_vector_base_p bboxes1, bbox_vector_base_p bboxes2) {
  if (bboxes1.get() == nullptr || bboxes2.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return bboxes1->overlaps(*bboxes2);
}
