#pragma once

#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <cpp11/logicals.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/r_string.hpp>
#include <cpp11/list.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include "exact_numeric.h"
#include "transform.h"
#include "bbox.h"
#include "is_degenerate.h"
#include "point_predicates.h"
#include "geometry_measures.h"
#include "geometry_projection.h"
#include "get_vertex.h"
#include "match.h"
#include "constant_in.h"
#include "normal.h"

#include <sstream>
#include <iomanip>

enum Primitive {
  VIRTUAL,
  CIRCLE,
  DIRECTION,
  ISOCUBE,
  ISORECT,
  LINE,
  PLANE,
  POINT,
  RAY,
  SEGMENT,
  SPHERE,
  TETRAHEDRON,
  TRIANGLE,
  VECTOR,
  WPOINT
};

class geometry_vector_base {
public:
  geometry_vector_base() {}
  virtual ~geometry_vector_base() = default;

  // Conversion
  virtual cpp11::writable::doubles_matrix as_numeric() const = 0;
  virtual cpp11::writable::strings format() const = 0;
  virtual std::vector<double> get_row(size_t i, size_t j) const = 0;

  // Equality
  virtual cpp11::writable::logicals operator==(const geometry_vector_base& other) const = 0;

  // Dimensions
  virtual size_t size() const = 0;
  virtual size_t dimensions() const = 0;
  virtual Primitive geometry_type() const = 0;
  virtual cpp11::writable::strings def_names() const = 0;
  virtual std::vector<Exact_number> definition(int which, cpp11::integers element) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> vertex(cpp11::integers which) const = 0;
  virtual Exact_number get_single_definition(size_t i, int which, int element) const = 0;
  virtual size_t cardinality(size_t i) const = 0;
  virtual size_t long_length() const = 0;

  // Subsetting etc
  virtual cpp11::external_pointer<geometry_vector_base> subset(cpp11::integers index) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> copy() const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> assign(cpp11::integers index, const geometry_vector_base& value) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> combine(cpp11::list_of< cpp11::external_pointer<geometry_vector_base> > extra) const = 0;

  // Self-similarity
  virtual cpp11::external_pointer<geometry_vector_base> unique() const = 0;
  virtual cpp11::writable::logicals duplicated() const = 0;
  virtual int any_duplicated() const = 0;
  virtual cpp11::writable::integers match(const geometry_vector_base& table) const = 0;
  virtual cpp11::writable::logicals is_na() const = 0;
  virtual bool any_na() const = 0;

  // Predicates
  virtual cpp11::writable::logicals is_degenerate() const = 0;
  virtual cpp11::writable::logicals has_inside(const geometry_vector_base& points) const = 0;
  virtual cpp11::writable::logicals has_on(const geometry_vector_base& points) const = 0;
  virtual cpp11::writable::logicals has_outside(const geometry_vector_base& points) const = 0;
  virtual cpp11::writable::logicals has_on_positive(const geometry_vector_base& points) const = 0;
  virtual cpp11::writable::logicals has_on_negative(const geometry_vector_base& points) const = 0;
  virtual cpp11::writable::logicals constant_in(cpp11::integers coord) const = 0;

  // Measures
  virtual cpp11::writable::doubles length() const = 0;
  virtual cpp11::writable::doubles area() const = 0;
  virtual cpp11::writable::doubles volume() const = 0;
  virtual std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const = 0;
  virtual cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const = 0;

  // Common
  virtual cpp11::external_pointer<geometry_vector_base> transform(const transform_vector_base& affine) const = 0;
  virtual bbox_vector_base_p bbox() const = 0;

  // Projections
  virtual cpp11::external_pointer<geometry_vector_base> project_to_line(const geometry_vector_base& lines) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> project_to_plane(const geometry_vector_base& planes) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> map_to_plane(const geometry_vector_base& planes) const = 0;
  virtual cpp11::external_pointer<geometry_vector_base> normal() const = 0;

  // Intersections
  virtual cpp11::writable::list intersection(const geometry_vector_base& other) const = 0;
  virtual cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const = 0;
};
typedef cpp11::external_pointer<geometry_vector_base> geometry_vector_base_p;

// General constructor
template<typename T>
geometry_vector_base_p create_geometry_vector(std::vector<T>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Circle_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Circle_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Direction_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Direction_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Iso_cuboid>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Iso_rectangle>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Line_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Line_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Plane>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Point_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Point_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Ray_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Ray_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Segment_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Segment_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Sphere>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Tetrahedron>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Triangle_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Triangle_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Vector_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Vector_3>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Weighted_point_2>& input);
template<>
geometry_vector_base_p create_geometry_vector(std::vector<Weighted_point_3>& input);

template<typename T>
geometry_vector_base_p create_scalar_geometry(const T& val) {
  std::vector<T> scalar = {val};
  return create_geometry_vector(scalar);
}

// General extractors
template<typename T>
const std::vector<T> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Circle_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Circle_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Direction_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Direction_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Iso_cuboid> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Iso_rectangle> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Line_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Line_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Plane> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Point_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Point_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Ray_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Ray_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Segment_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Segment_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Sphere> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Tetrahedron> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Triangle_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Triangle_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Vector_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Vector_3> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Weighted_point_2> get_vector_of_geo(const geometry_vector_base& geometries);
template<>
const std::vector<Weighted_point_3> get_vector_of_geo(const geometry_vector_base& geometries);

// geometry_vector -------------------------------------------------------------

template <typename T, size_t dim, typename U = T>
class geometry_vector : public geometry_vector_base {
  typedef typename std::conditional<dim == 2, Aff_transformation_2, Aff_transformation_3>::type Aff;
  typedef typename std::conditional<dim == 2, Point_2, Point_3>::type Point;
  typedef typename std::conditional<dim == 2, Line_2, Line_3>::type Line;
  typedef typename std::conditional<dim == 2, Bbox_2, Bbox_3>::type Bbox;
  typedef typename std::conditional<dim == 2, bbox2, bbox3>::type bbox_vec;
  typedef typename std::conditional<dim == 2, Direction_2, Direction_3>::type Direction;

protected:
  std::vector<T> _storage;

public:
  geometry_vector() {}
  // Construct without element copy - BEWARE!
  geometry_vector(std::vector<T> content) {
    _storage.swap(content);
  }
  geometry_vector(const geometry_vector& copy) : _storage(copy._storage) {}
  geometry_vector& operator=(const geometry_vector& copy) const {
    _storage.clear();
    _storage.assign(_storage.end(), copy._storage.begin(), copy._storage.end());
    return *this;
  }
  ~geometry_vector() = default;
  const std::vector<T>& get_storage() const { return _storage; }

  // Conversion
  cpp11::writable::doubles_matrix as_numeric() const {
    cpp11::writable::strings colnames = def_names();
    size_t ncols = colnames.size();
    cpp11::writable::doubles_matrix result(long_length(), ncols);

    size_t ii = 0;
    for (size_t i = 0; i < size(); ++i) {
      bool is_na = !_storage[i];
      for (size_t j = 0; j < cardinality(i); ++j) {
        std::vector<double> row = get_row(i, j);
        for (size_t k = 0; k < ncols; ++k) {
          result(ii, k) = is_na ? R_NaReal : row[k];
        }
        ++ii;
      }
    }

    result.attr("dimnames") = cpp11::writable::list({R_NilValue, colnames});
    return result;
  }
  cpp11::writable::strings format() const {
    cpp11::writable::strings result(size());
    cpp11::writable::strings defnames = def_names();
    size_t ndims = defnames.size();

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result[i] = "<NA>";
        continue;
      }
      std::ostringstream f;
      f << std::setprecision(3);
      size_t car = cardinality(i);
      if (car > 1) {
        f << "[";
      }
      for (size_t j = 0; j < car; ++j) {
        if (j != 0) {
          f << ", ";
        }
        f << "<";
        std::vector<double> row = get_row(i, j);
        for (size_t k = 0; k < ndims; ++k) {
          if (k != 0) {
            f << ", ";
          }
          const std::string name = cpp11::r_string(defnames[k]);
          f << name << ":" << row[k];
        }
        f << ">";
      }
      if (car > 1) {
        f << "]";
      }

      result[i] = f.str();
    }

    return result;
  }
  std::vector<Exact_number> definition(int which, cpp11::integers element) const {
    bool get_all = element[0] == R_NaInt;
    std::vector<Exact_number> result;
    result.reserve(get_all ? long_length() : size());

    for (size_t i = 0; i < size(); ++i) {
      if (get_all) {
        for (size_t j = 0; j < cardinality(i); ++j) {
          result.push_back(get_single_definition(i, which, j));
        }
      } else {
        result.push_back(get_single_definition(i, which, element[i]));
      }
    }

    return result;
  }
  cpp11::external_pointer<geometry_vector_base> vertex(cpp11::integers which) const {
    std::vector<Point> vertices;
    size_t max_size = std::max(size(), (size_t) which.size());
    vertices.reserve(max_size);
    for (size_t i = 0; i < max_size; ++i) {
      if (!_storage[i % size()] || which[i % which.size()] == R_NaInt) {
        vertices.push_back(Point::NA_value());
      }
      vertices.push_back(get_vertex_impl<T, Point>(_storage[i % size()], which[i % which.size()]));
    }
    return create_geometry_vector(vertices);
  }

  // Equality
  cpp11::writable::logicals operator==(const geometry_vector_base& other) const {
    size_t output_length = std::max(size(), other.size());

    cpp11::writable::logicals result(output_length);

    if (typeid(*this) != typeid(other)) {
      for (size_t i = 0; i < size(); ++i) {
        result[i] = (Rboolean) false;
      }
      return result;
    }

    auto other_vec = get_vector_of_geo<T>(other);

    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !other_vec[i % other_vec.size()]) {
        result[i] = NA_LOGICAL;
        continue;
      }
      result[i] = (Rboolean) (_storage[i % size()] == other_vec[i % other_vec.size()]);
    }

    return result;
  }

  // Utility
  size_t size() const { return _storage.size(); }
  T operator[](size_t i) const { return _storage[i]; }
  void clear() { _storage.clear(); }
  void push_back(T element) { _storage.push_back(element); }
  size_t dimensions() const {
    return dim;
  };
  size_t cardinality(size_t i) const { return 1; }
  size_t long_length() const { return size(); }

  // Subsetting, assignment, combining etc
  geometry_vector_base_p subset(cpp11::integers index) const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      if (index[i] == R_NaInt) {
        new_storage.push_back(T::NA_value());
      } else {
        new_storage.push_back(_storage[index[i] - 1]);
      }
    }
    return create_geometry_vector(new_storage);
  }
  geometry_vector_base_p copy() const {
    std::vector<T> new_storage;
    new_storage.reserve(size());
    new_storage.insert(new_storage.begin(), _storage.begin(), _storage.end());
    return create_geometry_vector(new_storage);
  }
  geometry_vector_base_p assign(cpp11::integers index, const geometry_vector_base& value) const {
    if (index.size() != value.size()) {
      cpp11::stop("Incompatible vector sizes");
    }
    if (typeid(*this) != typeid(value)) {
      cpp11::stop("Incompatible assignment value type");
    }

    auto value_vec = get_vector_of_geo<T>(value);

    std::vector<T> new_storage(_storage);
    int max_size = *std::max_element(index.begin(), index.end());
    if (max_size > new_storage.size()) {
      new_storage.reserve(max_size);
      for (int j = new_storage.size(); j < max_size; ++j) {
        new_storage.push_back(T::NA_value());
      }
    }
    for (R_xlen_t i = 0; i < index.size(); ++i) {
      new_storage[index[i] - 1] = value_vec[i];
    }
    return create_geometry_vector(new_storage);
  }
  geometry_vector_base_p combine(cpp11::list_of< geometry_vector_base_p > extra) const {
    std::vector<T> new_storage(_storage);

    for (R_xlen_t i = 0; i < extra.size(); ++i) {
      geometry_vector_base* candidate = extra[i].get();
      if (typeid(*this) != typeid(*candidate)) {
        cpp11::stop("Incompatible vector types");
      }
      auto candidate_vec = get_vector_of_geo<T>(*candidate);
      for (size_t j = 0; j < candidate_vec.size(); ++j) {
        new_storage.push_back(candidate_vec[j]);
      }
    }

    return create_geometry_vector(new_storage);
  }

  // Self-similarity
  geometry_vector_base_p unique() const {
    std::vector<T> new_storage;
    bool NA_seen = false;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!iter->is_valid()) {
        if (!NA_seen) {
          new_storage.push_back(T::NA_value());
          NA_seen = true;
        }
        continue;
      }
      if (std::find(new_storage.begin(), new_storage.end(), *iter) == new_storage.end()) {
        new_storage.push_back(*iter);
      }
    }

    return create_geometry_vector(new_storage);
  };
  cpp11::writable::logicals duplicated() const {
    std::vector<T> uniques;
    cpp11::writable::logicals dupes;
    dupes.reserve(size());
    bool NA_seen = false;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!iter->is_valid()) {
        if (!NA_seen) {
          dupes.push_back(TRUE);
          NA_seen = true;
        }
        continue;
      }
      if (std::find(uniques.begin(), uniques.end(), *iter) == uniques.end()) {
        uniques.push_back(*iter);
        dupes.push_back(FALSE);
      } else {
        dupes.push_back(TRUE);
      }
    }

    return dupes;
  }
  int any_duplicated() const {
    int anyone = -1;
    bool NA_seen = false;;
    int i = 0;
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!_storage[i].is_valid()) {
        if (NA_seen) {
          anyone = i;
          break;
        }
        NA_seen = true;
      } else if (std::find(iter + 1, _storage.end(), *iter) != _storage.end()) {
        anyone = true;
        break;
      }
      ++i;
    }

    return anyone;
  }
  cpp11::writable::integers match(const geometry_vector_base& table) const {
    cpp11::writable::integers results;
    results.reserve(size());

    if (typeid(*this) != typeid(table)) {
      for (size_t i = 0; i < size(); ++i) {
        results.push_back(R_NaInt);
      }
      return results;
    }

    auto table_vec = get_vector_of_geo<T>(table);

    return match_impl(_storage, table_vec);
  }
  cpp11::writable::logicals is_na() const {
    cpp11::writable::logicals result;
    result.reserve(size());

    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      result.push_back((Rboolean) !(*iter));
    }

    return result;
  }
  bool any_na() const {
    for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
      if (!(*iter)) {
        return true;
      }
    }
    return false;
  }

  // Predicates
  cpp11::writable::logicals is_degenerate() const {
    cpp11::writable::logicals result;
    result.reserve(_storage.size());
    for (size_t i = 0; i < _storage.size(); ++i) {
      if (!_storage[i]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) is_degenerate_impl(_storage[i]));
    }
    return result;
  }
  cpp11::writable::logicals has_inside(const geometry_vector_base& points) const {
    if (dim != points.dimensions()) {
      cpp11::stop("points must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), points.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    auto points_vec = get_vector_of_geo<Point>(points);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !points_vec[i % points_vec.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) has_inside_impl(_storage[i % size()], points_vec[i % points_vec.size()]));
    }
    return result;
  }
  cpp11::writable::logicals has_on(const geometry_vector_base& points) const {
    if (dim != points.dimensions()) {
      cpp11::stop("points must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), points.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    auto points_vec = get_vector_of_geo<Point>(points);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !points_vec[i % points_vec.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) has_on_impl(_storage[i % size()], points_vec[i % points_vec.size()]));
    }
    return result;
  }
  cpp11::writable::logicals has_outside(const geometry_vector_base& points) const {
    if (dim != points.dimensions()) {
      cpp11::stop("points must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), points.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    auto points_vec = get_vector_of_geo<Point>(points);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !points_vec[i % points_vec.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) has_outside_impl(_storage[i % size()], points_vec[i % points_vec.size()]));
    }
    return result;
  }
  cpp11::writable::logicals has_on_positive(const geometry_vector_base& points) const {
    if (dim != points.dimensions()) {
      cpp11::stop("points must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), points.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    auto points_vec = get_vector_of_geo<Point>(points);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !points_vec[i % points_vec.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) has_on_positive_impl(_storage[i % size()], points_vec[i % points_vec.size()]));
    }
    return result;
  }
  cpp11::writable::logicals has_on_negative(const geometry_vector_base& points) const {
    if (dim != points.dimensions()) {
      cpp11::stop("points must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), points.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    auto points_vec = get_vector_of_geo<Point>(points);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !points_vec[i % points_vec.size()]) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back((Rboolean) has_on_negative_impl(_storage[i % size()], points_vec[i % points_vec.size()]));
    }
    return result;
  }
  cpp11::writable::logicals constant_in(cpp11::integers coord) const {
    size_t output_length = std::max(size(), (size_t) coord.size());
    cpp11::writable::logicals result;
    result.reserve(output_length);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || coord[i % coord.size()] == R_NaInt) {
        result.push_back(NA_LOGICAL);
        continue;
      }
      result.push_back(constant_in_impl<T>(_storage[i % size()], coord[i % coord.size()]));
    }
    return result;
  }

  // Measures
  cpp11::writable::doubles length() const {
    cpp11::writable::doubles result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(R_NaReal);
        continue;
      }
      result.push_back(length_impl(_storage[i]));
    }

    return result;
  }
  cpp11::writable::doubles area() const {
    cpp11::writable::doubles result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(R_NaReal);
        continue;
      }
      result.push_back(area_impl(_storage[i]));
    }

    return result;
  }
  cpp11::writable::doubles volume() const {
    cpp11::writable::doubles result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(R_NaReal);
        continue;
      }
      result.push_back(volume_impl(_storage[i]));
    }

    return result;
  }

  // Common
  geometry_vector_base_p transform(const transform_vector_base& affine) const {
    if (dim != affine.dimensions()) {
      cpp11::stop("Transform matrix must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), affine.size());

    std::vector<T> result;
    result.reserve(output_length);

    const transform_vector<Aff, dim>* affine_recast = dynamic_cast< const transform_vector<Aff, dim>* >(&affine);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !(*affine_recast)[i % affine_recast->size()]) {
        result.push_back(T::NA_value());
        continue;
      }
      result.push_back(transform_impl(_storage[i % size()], (*affine_recast)[i % affine_recast->size()]));
    }

    return create_geometry_vector(result);
  }

  bbox_vector_base_p bbox() const {
    std::vector<Bbox> result;
    result.reserve(size());

    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(Bbox::NA_value());
        continue;
      }
      result.push_back(bbox_impl<Bbox, T>(_storage[i]));
    }

    bbox_vec* vec(new bbox_vec(result));

    return {vec};
  }

  // Projections
  geometry_vector_base_p project_to_line(const geometry_vector_base& lines) const {
    if (dim != lines.dimensions()) {
      cpp11::stop("Projection target must match dimensionality of geometry");
    }
    size_t output_length = std::max(size(), lines.size());

    std::vector<T> result;
    result.reserve(output_length);

    auto lines_vec = get_vector_of_geo<Line>(lines);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !lines_vec[i % lines_vec.size()]) {
        result.push_back(T::NA_value());
        continue;
      }
      result.push_back(project_to_line_impl(_storage[i % size()], lines_vec[i % lines_vec.size()]));
    }

    return create_geometry_vector(result);
  }
  geometry_vector_base_p project_to_plane(const geometry_vector_base& planes) const {
    if (dim != 3) {
      cpp11::stop("Only 3 dimensional geometries can be projected to plane");
    }
    size_t output_length = std::max(size(), planes.size());

    std::vector<T> result;
    result.reserve(output_length);

    auto planes_vec = get_vector_of_geo<Plane>(planes);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !planes_vec[i % planes_vec.size()]) {
        result.push_back(T::NA_value());
        continue;
      }
      result.push_back(project_to_plane_impl(_storage[i % size()], planes_vec[i % planes_vec.size()]));
    }

    return create_geometry_vector(result);
  }
  geometry_vector_base_p map_to_plane(const geometry_vector_base& planes) const {
    if (dim != 3) {
      cpp11::stop("Only 3 dimensional geometries can be mapped to plane");
    }
    size_t output_length = std::max(size(), planes.size());

    std::vector<U> result;
    result.reserve(output_length);

    auto planes_vec = get_vector_of_geo<Plane>(planes);
    for (size_t i = 0; i < output_length; ++i) {
      if (!_storage[i % size()] || !planes_vec[i % planes_vec.size()]) {
        result.push_back(U::NA_value());
        continue;
      }
      result.push_back(map_to_plane_impl<T, U>(_storage[i % size()], planes_vec[i % planes_vec.size()]));
    }

    return create_geometry_vector(result);
  }
  geometry_vector_base_p normal() const {
    std::vector<Direction> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(Direction::NA_value());
        continue;
      }
      result.push_back(normal_impl<T, Direction>(_storage[i]));
    }

    return create_geometry_vector(result);
  }
};
