#include "cgal_types.h"
#include "geometry_vector.h"
#include "point.h"

[[cpp11::register]]
geometry_vector_base_p geometry_barycenter_2(geometry_vector_base_p p1, geometry_vector_base_p p2) {
  if (p1->dimensions() == 2) {
    auto vec1 = get_vector_of_geo<Weighted_point_2>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_2>(*p2);
    size_t output_size = std::max(vec1.size(), vec2.size());
    std::vector<Point_2> result;
    if (vec1.size() == 0 || vec2.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_2 wp1 = vec1[i % vec1.size()];
      Weighted_point_2 wp2 = vec2[i % vec2.size()];
      if (!wp1 || !wp2 || wp1.weight() + wp2.weight() == 0) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight()));
    }
    return create_geometry_vector(result);
  } else {
    auto vec1 = get_vector_of_geo<Weighted_point_3>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_3>(*p2);
    size_t output_size = std::max(vec1.size(), vec2.size());
    std::vector<Point_3> result;
    if (vec1.size() == 0 || vec2.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_3 wp1 = vec1[i % vec1.size()];
      Weighted_point_3 wp2 = vec2[i % vec2.size()];
      if (!wp1 || !wp2 || wp1.weight() + wp2.weight() == 0) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight()));
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_barycenter_3(geometry_vector_base_p p1, geometry_vector_base_p p2, geometry_vector_base_p p3) {
  if (p1->dimensions() == 2) {
    auto vec1 = get_vector_of_geo<Weighted_point_2>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_2>(*p2);
    auto vec3 = get_vector_of_geo<Weighted_point_2>(*p3);
    size_t output_size = std::max(std::max(vec1.size(), vec2.size()), vec3.size());
    std::vector<Point_2> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_2 wp1 = vec1[i % vec1.size()];
      Weighted_point_2 wp2 = vec2[i % vec2.size()];
      Weighted_point_2 wp3 = vec3[i % vec3.size()];
      if (!wp1 || !wp2 || !wp3 || wp1.weight() + wp2.weight() + wp3.weight() == 0) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight(), wp3.point(), wp3.weight()));
    }
    return create_geometry_vector(result);
  } else {
    auto vec1 = get_vector_of_geo<Weighted_point_3>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_3>(*p2);
    auto vec3 = get_vector_of_geo<Weighted_point_3>(*p3);
    size_t output_size = std::max(std::max(vec1.size(), vec2.size()), vec3.size());
    std::vector<Point_3> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_3 wp1 = vec1[i % vec1.size()];
      Weighted_point_3 wp2 = vec2[i % vec2.size()];
      Weighted_point_3 wp3 = vec3[i % vec3.size()];
      if (!wp1 || !wp2 || !wp3 || wp1.weight() + wp2.weight() + wp3.weight() == 0) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight(), wp3.point(), wp3.weight()));
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_barycenter_4(geometry_vector_base_p p1, geometry_vector_base_p p2, geometry_vector_base_p p3, geometry_vector_base_p p4) {
  if (p1->dimensions() == 2) {
    auto vec1 = get_vector_of_geo<Weighted_point_2>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_2>(*p2);
    auto vec3 = get_vector_of_geo<Weighted_point_2>(*p3);
    auto vec4 = get_vector_of_geo<Weighted_point_2>(*p4);
    size_t output_size = std::max(std::max(std::max(vec1.size(), vec2.size()), vec3.size()), vec4.size());
    std::vector<Point_2> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0 || vec4.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_2 wp1 = vec1[i % vec1.size()];
      Weighted_point_2 wp2 = vec2[i % vec2.size()];
      Weighted_point_2 wp3 = vec3[i % vec3.size()];
      Weighted_point_2 wp4 = vec4[i % vec4.size()];
      if (!wp1 || !wp2 || !wp3 || !wp4 || wp1.weight() + wp2.weight() + wp3.weight() + wp4.weight() == 0) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight(), wp3.point(), wp3.weight(), wp4.point(), wp4.weight()));
    }
    return create_geometry_vector(result);
  } else {
    auto vec1 = get_vector_of_geo<Weighted_point_3>(*p1);
    auto vec2 = get_vector_of_geo<Weighted_point_3>(*p2);
    auto vec3 = get_vector_of_geo<Weighted_point_3>(*p3);
    auto vec4 = get_vector_of_geo<Weighted_point_3>(*p4);
    size_t output_size = std::max(std::max(std::max(vec1.size(), vec2.size()), vec3.size()), vec4.size());
    std::vector<Point_3> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0 || vec4.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Weighted_point_3 wp1 = vec1[i % vec1.size()];
      Weighted_point_3 wp2 = vec2[i % vec2.size()];
      Weighted_point_3 wp3 = vec3[i % vec3.size()];
      Weighted_point_3 wp4 = vec4[i % vec4.size()];
      if (!wp1 || !wp2 || !wp3 || !wp4 || wp1.weight() + wp2.weight() + wp3.weight() + wp4.weight() == 0) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::barycenter(wp1.point(), wp1.weight(), wp2.point(), wp2.weight(), wp3.point(), wp3.weight(), wp4.point(), wp4.weight()));
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_bisector(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  size_t output_size = std::max(geo1->size(), geo2->size());
  if (geo1->dimensions() == 2) {
    std::vector<Line_2> result;
    if (geo1->size() == 0 || geo2->size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    switch (geo1->geometry_type()) {
    case POINT: {
      auto p1 = get_vector_of_geo<Point_2>(*geo1);
      auto p2 = get_vector_of_geo<Point_2>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!p1[i % p1.size()] || !p2[i % p2.size()] || p1[i % p1.size()] == p2[i % p2.size()]) {
          result.push_back(Line_2::NA_value());
          continue;
        }
        result.push_back(CGAL::bisector(p1[i % p1.size()], p2[i % p2.size()]));
      }
      break;
    }
    //case LINE: {
    //  auto p1 = get_vector_of_geo<Line_2>(*geo1);
    //  auto p2 = get_vector_of_geo<Line_2>(*geo2);
    //  for (size_t i = 0; i < output_size; ++i) {
    //    if (!p1[i % p1.size()] || !p2[i % p2.size()]) {
    //      result.push_back(Line_2::NA_value());
    //      continue;
    //    }
    //    result.push_back(CGAL::bisector(p1[i % p1.size()], p2[i % p2.size()]));
    //  }
    //}
    default: cpp11::stop("Don't know how to calculate bisector of given geometries");
    }
    return create_geometry_vector(result);
  } else {
    std::vector<Plane> result;
    if (geo1->size() == 0 || geo2->size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    switch (geo1->geometry_type()) {
    case POINT: {
      auto p1 = get_vector_of_geo<Point_3>(*geo1);
      auto p2 = get_vector_of_geo<Point_3>(*geo2);
      for (size_t i = 0; i < output_size; ++i) {
        if (!p1[i % p1.size()] || !p2[i % p2.size()] || p1[i % p1.size()] == p2[i % p2.size()]) {
          result.push_back(Plane::NA_value());
          continue;
        }
        result.push_back(CGAL::bisector(p1[i % p1.size()], p2[i % p2.size()]));
      }
      break;
    }
    //case PLANE: {
    //  auto p1 = get_vector_of_geo<Plane>(*geo1);
    //  auto p2 = get_vector_of_geo<Plane>(*geo2);
    //  for (size_t i = 0; i < output_size; ++i) {
    //    if (!p1[i % p1.size()] || !p2[i % p2.size()]) {
    //      result.push_back(Plane::NA_value());
    //      continue;
    //    }
    //    result.push_back(CGAL::bisector(p1[i % p1.size()], p2[i % p2.size()]));
    //  }
    //}
    default: cpp11::stop("Don't know how to calculate bisector of given geometries");
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_centroid_1(geometry_vector_base_p geo) {
  switch (geo->geometry_type()) {
  case TRIANGLE: {
    if (geo->dimensions() == 2) {
      std::vector<Point_2> result;
      result.reserve(geo->size());
      auto t = get_vector_of_geo<Triangle_2>(*geo);
      for (size_t i = 0; i < t.size(); ++i) {
        if (!t[i]) {
          result.push_back(Point_2::NA_value());
          continue;
        }
        result.push_back(CGAL::centroid(t[i]));
      }
      return create_geometry_vector(result);
    } else {
      std::vector<Point_3> result;
      result.reserve(geo->size());
      auto t = get_vector_of_geo<Triangle_3>(*geo);
      for (size_t i = 0; i < t.size(); ++i) {
        if (!t[i]) {
          result.push_back(Point_3::NA_value());
          continue;
        }
        result.push_back(CGAL::centroid(t[i]));
      }
      return create_geometry_vector(result);
    }
  }
  case TETRAHEDRON: {
    std::vector<Point_3> result;
    result.reserve(geo->size());
    auto t = get_vector_of_geo<Tetrahedron>(*geo);
    for (size_t i = 0; i < t.size(); ++i) {
      if (!t[i]) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::centroid(t[i]));
    }
    return create_geometry_vector(result);
  }
  default: cpp11::stop("Don't know how to calculate centroid of given geometry");
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_centroid_3(geometry_vector_base_p p1, geometry_vector_base_p p2, geometry_vector_base_p p3) {
  if (p1->dimensions() == 2) {
    auto vec1 = get_vector_of_geo<Point_2>(*p1);
    auto vec2 = get_vector_of_geo<Point_2>(*p2);
    auto vec3 = get_vector_of_geo<Point_2>(*p3);
    size_t output_size = std::max(std::max(vec1.size(), vec2.size()), vec3.size());
    std::vector<Point_2> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Point_2 wp1 = vec1[i % vec1.size()];
      Point_2 wp2 = vec2[i % vec2.size()];
      Point_2 wp3 = vec3[i % vec3.size()];
      if (!wp1 || !wp2 || !wp3) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(CGAL::centroid(wp1, wp2, wp3));
    }
    return create_geometry_vector(result);
  } else {
    auto vec1 = get_vector_of_geo<Point_3>(*p1);
    auto vec2 = get_vector_of_geo<Point_3>(*p2);
    auto vec3 = get_vector_of_geo<Point_3>(*p3);
    size_t output_size = std::max(std::max(vec1.size(), vec2.size()), vec3.size());
    std::vector<Point_3> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Point_3 wp1 = vec1[i % vec1.size()];
      Point_3 wp2 = vec2[i % vec2.size()];
      Point_3 wp3 = vec3[i % vec3.size()];
      if (!wp1 || !wp2 || !wp3) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::centroid(wp1, wp2, wp3));
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_centroid_4(geometry_vector_base_p p1, geometry_vector_base_p p2, geometry_vector_base_p p3, geometry_vector_base_p p4) {
  if (p1->dimensions() == 2) {
    auto vec1 = get_vector_of_geo<Point_2>(*p1);
    auto vec2 = get_vector_of_geo<Point_2>(*p2);
    auto vec3 = get_vector_of_geo<Point_2>(*p3);
    auto vec4 = get_vector_of_geo<Point_2>(*p4);
    size_t output_size = std::max(std::max(std::max(vec1.size(), vec2.size()), vec3.size()), vec4.size());
    std::vector<Point_2> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0 || vec4.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Point_2 wp1 = vec1[i % vec1.size()];
      Point_2 wp2 = vec2[i % vec2.size()];
      Point_2 wp3 = vec3[i % vec3.size()];
      Point_2 wp4 = vec4[i % vec4.size()];
      if (!wp1 || !wp2 || !wp3 || !wp4) {
        result.push_back(Point_2::NA_value());
        continue;
      }
      result.push_back(CGAL::centroid(wp1, wp2, wp3, wp4));
    }
    return create_geometry_vector(result);
  } else {
    auto vec1 = get_vector_of_geo<Point_3>(*p1);
    auto vec2 = get_vector_of_geo<Point_3>(*p2);
    auto vec3 = get_vector_of_geo<Point_3>(*p3);
    auto vec4 = get_vector_of_geo<Point_3>(*p4);
    size_t output_size = std::max(std::max(std::max(vec1.size(), vec2.size()), vec3.size()), vec4.size());
    std::vector<Point_3> result;
    if (vec1.size() == 0 || vec2.size() == 0 || vec3.size() == 0 || vec4.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      Point_3 wp1 = vec1[i % vec1.size()];
      Point_3 wp2 = vec2[i % vec2.size()];
      Point_3 wp3 = vec3[i % vec3.size()];
      Point_3 wp4 = vec4[i % vec4.size()];
      if (!wp1 || !wp2 || !wp3 || !wp4) {
        result.push_back(Point_3::NA_value());
        continue;
      }
      result.push_back(CGAL::centroid(wp1, wp2, wp3, wp4));
    }
    return create_geometry_vector(result);
  }
}

[[cpp11::register]]
geometry_vector_base_p geometry_equidistant_line(point3_p p1, point3_p p2, point3_p p3) {
  size_t output_size = std::max(std::max(p1->size(), p2->size()), p3->size());
  std::vector<Line_3> result;
  if (p1->size() == 0 || p2->size() == 0 || p3->size() == 0) {
    return create_geometry_vector(result);
  }
  result.reserve(output_size);
  for (size_t i = 0; i < output_size; ++i) {
    if (!(*p1)[i % p1->size()] || !(*p2)[i % p2->size()] || !(*p3)[i % p3->size()] ||
        CGAL::collinear((*p1)[i % p1->size()], (*p2)[i % p2->size()], (*p3)[i % p3->size()])) {
      result.push_back(Line_3::NA_value());
      continue;
    }
    result.push_back(CGAL::equidistant_line((*p1)[i % p1->size()], (*p2)[i % p2->size()], (*p3)[i % p3->size()]));
  }
  return create_geometry_vector(result);
}

[[cpp11::register]]
geometry_vector_base_p geometry_radical_geometry(geometry_vector_base_p geo1, geometry_vector_base_p geo2) {
  size_t output_size = std::max(geo1->size(), geo2->size());
  if (geo1->geometry_type() == SPHERE) {
    auto s1 = get_vector_of_geo<Sphere>(*geo1);
    auto s2 = get_vector_of_geo<Sphere>(*geo2);
    std::vector<Plane> result;
    if (s1.size() == 0 || s2.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      if (!s1[i % s1.size()] || !s2[i % s2.size()] ||
          s1[i % s1.size()].center() == s2[i % s2.size()].center()) {
        result.push_back(Plane::NA_value());
        continue;
      }
      result.push_back(CGAL::radical_plane(s1[i % s1.size()], s2[i % s2.size()]));
    }
    return create_geometry_vector(result);
  } else if (geo1->geometry_type() == CIRCLE && geo1->dimensions() == 2) {
    auto c1 = get_vector_of_geo<Circle_2>(*geo1);
    auto c2 = get_vector_of_geo<Circle_2>(*geo2);
    std::vector<Line_2> result;
    if (c1.size() == 0 || c2.size() == 0) {
      return create_geometry_vector(result);
    }
    result.reserve(output_size);
    for (size_t i = 0; i < output_size; ++i) {
      if (!c1[i % c1.size()] || !c2[i % c2.size()] ||
          c1[i % c1.size()].center() == c2[i % c2.size()].center()) {
        result.push_back(Line_2::NA_value());
        continue;
      }
      result.push_back(CGAL::radical_line(c1[i % c1.size()], c2[i % c2.size()]));
    }
    return create_geometry_vector(result);
  } else {
    cpp11::stop("Don't know how to calculate radical geometry of given geometries");
  }
}
