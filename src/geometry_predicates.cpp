#include "geometry_vector.h"

#include <cpp11/integers.hpp>
#include <cpp11/logicals.hpp>

[[cpp11::register]]
cpp11::writable::logicals geometry_is_degenerate(geometry_vector_base_p geometries) {
  return geometries->is_degenerate();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_inside(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_inside(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_outside(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_outside(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on_positive(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on_positive(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_has_point_on_negative(geometry_vector_base_p geometries, geometry_vector_base_p points) {
  return geometries->has_on_negative(*points);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_constant_in(geometry_vector_base_p geometries, cpp11::integers coord) {
  return geometries->constant_in(coord);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_parallel(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  size_t output_size = std::max(geo1->size(), geo2->size());
  cpp11::writable::logicals result;
  result.reserve(output_size);
  if (geo1->dimensions() == 2) {
    switch (geo1->geometry_type()) {
    case LINE: {
      auto l1 = get_vector_of_geo<Line_2>(*geo1);
      auto l2 = get_vector_of_geo<Line_2>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    case RAY: {
      auto l1 = get_vector_of_geo<Ray_2>(*geo1);
      auto l2 = get_vector_of_geo<Ray_2>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    case SEGMENT: {
      auto l1 = get_vector_of_geo<Segment_2>(*geo1);
      auto l2 = get_vector_of_geo<Segment_2>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    default: cpp11::stop("Don't know how to assess parallelity of the given geometries");
    }
  } else {
    switch (geo1->geometry_type()) {
    case LINE: {
      auto l1 = get_vector_of_geo<Line_3>(*geo1);
      auto l2 = get_vector_of_geo<Line_3>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    case PLANE: {
      auto l1 = get_vector_of_geo<Plane>(*geo1);
      auto l2 = get_vector_of_geo<Plane>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    case RAY: {
      auto l1 = get_vector_of_geo<Ray_3>(*geo1);
      auto l2 = get_vector_of_geo<Ray_3>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    case SEGMENT: {
      auto l1 = get_vector_of_geo<Segment_3>(*geo1);
      auto l2 = get_vector_of_geo<Segment_3>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!l1[i % l1.size()] || !l2[i % l2.size()]) {
          result.push_back(NA_LOGICAL);
          continue;
        }
        result.push_back((Rboolean) CGAL::parallel(l1[i % l1.size()], l2[i % l2.size()]));
      }
      break;
    }
    default: cpp11::stop("Don't know how to assess parallelity of the given geometries");
    }
  }
  return result;
}
