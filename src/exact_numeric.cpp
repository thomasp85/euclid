#include "exact_numeric.h"

#include <CGAL/number_utils.h>
#include <CGAL/utils_classes.h>
#include <cpp11/doubles.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/external_pointer.hpp>
#include <limits>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include <typeinfo>
#include <iostream>

[[cpp11::register]]
cpp11::external_pointer<exact_numeric> create_exact_numeric(cpp11::doubles numeric) {
  exact_numeric* ex_n(new exact_numeric(numeric));

  return {ex_n};
}
[[cpp11::register]]
int exact_numeric_length(cpp11::external_pointer<exact_numeric> ex_n) {
  return ex_n->size();
}

exact_numeric exact_numeric::subset(cpp11::integers index) const {
  std::vector<Exact_number> result;
  result.reserve(index.size());

  for (R_xlen_t i = 0; i < index.size(); ++i) {
    result.push_back(_storage[index[i] - 1]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_subset(cpp11::external_pointer<exact_numeric> ex_n, cpp11::integers index) {
  exact_numeric* new_ex(new exact_numeric(ex_n->subset(index)));
  return {new_ex};
}

exact_numeric exact_numeric::assign(cpp11::integers index, exact_numeric value) const {
  exact_numeric result = *this;

  for (R_xlen_t i = 0; i < index.size(); ++i) {
    result._storage[index[i] - 1] = value[i];
  }

  return result;
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_assign(cpp11::external_pointer<exact_numeric> ex_n, cpp11::integers index,
                                                            cpp11::external_pointer<exact_numeric> value) {
  exact_numeric* new_ex(new exact_numeric(ex_n->assign(index, *value)));
  return {new_ex};
}

exact_numeric exact_numeric::combine(cpp11::list_of< cpp11::external_pointer<exact_numeric> > extra) const {
  exact_numeric result = *this;

  for (R_xlen_t i = 0; i < extra.size(); ++i) {
    for (size_t j = 0; j < extra[i]->size(); ++j) {
      result.push_back(extra[i]->_storage[j]);
    }
  }

  return result;
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_combine(cpp11::external_pointer<exact_numeric> ex_n,
                                                             cpp11::list_of< cpp11::external_pointer<exact_numeric> > extra) {
  exact_numeric* new_ex(new exact_numeric(ex_n->combine(extra)));
  return {new_ex};
}

cpp11::writable::doubles exact_numeric::as_numeric() const {
  cpp11::writable::doubles result(size());

  for (size_t i = 0; i < size(); ++i) {
    result[i] = CGAL::to_double(_storage[i]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::doubles exact_numeric_to_numeric(cpp11::external_pointer<exact_numeric> ex_n) {
  return ex_n->as_numeric();
}

cpp11::writable::logicals exact_numeric::operator==(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] == x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_is_equal(cpp11::external_pointer<exact_numeric> ex_n,
                                                 cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) == (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator!=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] != x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_is_not_equal(cpp11::external_pointer<exact_numeric> ex_n,
                                                     cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) != (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator<(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] < x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_less(cpp11::external_pointer<exact_numeric> ex_n,
                                             cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) < (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator<=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] <= x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_less_equal(cpp11::external_pointer<exact_numeric> ex_n,
                                                   cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) <= (*ex_n2);
}


cpp11::writable::logicals exact_numeric::operator>(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] > x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_greater(cpp11::external_pointer<exact_numeric> ex_n,
                                                cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) > (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator>=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result[i] = (Rboolean) (_storage[i % size()] >= x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_greater_equal(cpp11::external_pointer<exact_numeric> ex_n,
                                                      cpp11::external_pointer<exact_numeric> ex_n2) {
  return (*ex_n) >= (*ex_n2);
}

exact_numeric exact_numeric::unique() const {
  std::set<Exact_number> uniques;
  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    uniques.insert(*iter);
  }
  std::vector<Exact_number> new_storage(uniques.begin(), uniques.end());

  return {new_storage};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_unique(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->unique()));
  return {new_ex};
}

cpp11::writable::logicals exact_numeric::duplicated() const {
  std::set<Exact_number> uniques;
  cpp11::writable::logicals dupes;
  dupes.reserve(size());
  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    if (uniques.find(*iter) == uniques.end()) {
      uniques.insert(*iter);
      dupes.push_back(FALSE);
    } else {
      dupes.push_back(TRUE);
    }
  }

  return dupes;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_duplicated(cpp11::external_pointer<exact_numeric> ex_n) {
  return ex_n->duplicated();
}

bool exact_numeric::any_duplicated() const {
  std::set<Exact_number> uniques;

  bool anyone = false;

  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    if (uniques.find(*iter) == uniques.end()) {
      uniques.insert(*iter);
    } else {
      anyone = true;
      break;
    }
  }

  return anyone;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_any_duplicated(cpp11::external_pointer<exact_numeric> ex_n) {
  return {(Rboolean) ex_n->any_duplicated()};
}

cpp11::writable::integers exact_numeric::rank() const {
  std::vector< std::pair<Exact_number, size_t> > ranks;
  ranks.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    ranks.emplace_back(_storage[i], i);
  }

  std::stable_sort(ranks.begin(), ranks.end(), [](const std::pair<Exact_number, size_t>& l, const std::pair<Exact_number, size_t> & r) {
    return l.first < r.first;
  });

  cpp11::writable::integers result;
  result.reserve(size());
  for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
    result.push_back(iter->second + 1);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::integers exact_numeric_rank(cpp11::external_pointer<exact_numeric> ex_n) {
  return ex_n->rank();
}

cpp11::writable::integers exact_numeric::match(const exact_numeric& table) const {
  std::map<Exact_number, size_t> lookup;

  for (size_t i = 0; i < table.size(); ++i) {
    if (lookup.find(table[i]) == lookup.end()) {
      lookup[table[i]] = i;
    }
  }
  cpp11::writable::integers result;
  result.reserve(size());
  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    auto match = lookup.find(*iter);
    if (match == lookup.end()) {
      result.push_back(R_NaInt);
    } else {
      result.push_back(match->second + 1);
    }
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::integers exact_numeric_match(cpp11::external_pointer<exact_numeric> ex_n,
                                              cpp11::external_pointer<exact_numeric> table) {
  return ex_n->match(*table);
}

exact_numeric exact_numeric::operator+(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result.push_back(_storage[i % size()] + x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_plus(cpp11::external_pointer<exact_numeric> ex_n,
                                                          cpp11::external_pointer<exact_numeric> ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) + (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator-(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result.push_back(_storage[i % size()] - x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_minus(cpp11::external_pointer<exact_numeric> ex_n,
                                                           cpp11::external_pointer<exact_numeric> ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) - (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator-() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    result.push_back(-_storage[i]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_uni_minus(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(-(*ex_n)));
  return {new_ex};
}

exact_numeric exact_numeric::operator*(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    result.push_back(_storage[i % size()] * x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_times(cpp11::external_pointer<exact_numeric> ex_n,
                                                           cpp11::external_pointer<exact_numeric> ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) * (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator/(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (x[i % x.size()] == 0.0) {
      cpp11::stop("Division by zero not allowed");
    }
    result.push_back(_storage[i % size()] / x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_divided(cpp11::external_pointer<exact_numeric> ex_n,
                                                             cpp11::external_pointer<exact_numeric> ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) / (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::abs() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    result.push_back(CGAL::abs(_storage[i]));
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_abs(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->abs()));
  return {new_ex};
}

cpp11::writable::integers exact_numeric::sign() const {
  cpp11::writable::integers result(size());

  for (size_t i = 0; i < size(); ++i) {
    if (_storage[i] > 0) {
      result[i] = 1;
    } else if (_storage[i] < 0) {
      result[i] = -1;
    } else {
      result[i] = 0;
    }
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::integers exact_numeric_sign(cpp11::external_pointer<exact_numeric> ex_n) {
  return ex_n->sign();
}

exact_numeric exact_numeric::cumsum() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  Exact_number cum_sum = 0.0;

  for (size_t i = 0; i < size(); ++i) {
    cum_sum += _storage[i];
    result.push_back(cum_sum);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_cumsum(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cumsum()));
  return {new_ex};
}

exact_numeric exact_numeric::cumprod() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  Exact_number cum_prod = 0.0;

  for (size_t i = 0; i < size(); ++i) {
    cum_prod *= _storage[i];
    result.push_back(cum_prod);
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_cumprod(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cumprod()));
  return {new_ex};
}

exact_numeric exact_numeric::cummax() const {
  std::vector<Exact_number> result;
  result.reserve(size());
  if (size() != 0) {
    Exact_number cum_max = _storage[0];

    for (size_t i = 0; i < size(); ++i) {
      cum_max = CGAL::max(_storage[i], cum_max);
      result.push_back(cum_max);
    }
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_cummax(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cummax()));
  return {new_ex};
}

exact_numeric exact_numeric::cummin() const {
  std::vector<Exact_number> result;
  result.reserve(size());
  if (size() != 0) {
    Exact_number cum_min = _storage[0];

    for (size_t i = 0; i < size(); ++i) {
      cum_min = CGAL::max(_storage[i], cum_min);
      result.push_back(cum_min);
    }
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_cummin(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cummin()));
  return {new_ex};
}

exact_numeric exact_numeric::diff(int lag) const {
  std::vector<Exact_number> result;
  if (size() >= lag) {
    result.reserve(size() - lag);

    for (size_t i = 0; i < size() - lag; ++i) {
      result.push_back(_storage[i + lag] - _storage[i]);
    }
  }

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_diff(cpp11::external_pointer<exact_numeric> ex_n, int lag) {
  exact_numeric* new_ex(new exact_numeric(ex_n->diff(lag)));
  return {new_ex};
}

exact_numeric exact_numeric::sort(bool decreasing) const {
  exact_numeric result = *this;

  if (decreasing) {
    std::stable_sort(result._storage.begin(), result._storage.end(), std::greater<Exact_number>());
  } else {
    std::stable_sort(result._storage.begin(), result._storage.end());
  }

  return result;
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_sort(cpp11::external_pointer<exact_numeric> ex_n, bool decreasing) {
  exact_numeric* new_ex(new exact_numeric(ex_n->sort(decreasing)));
  return {new_ex};
}

exact_numeric exact_numeric::sum() const {
  Exact_number total = 0.0;

  for (size_t i = 0; i < size(); ++i) {
    total += _storage[i];
  }
  std::vector<Exact_number> result;
  result.push_back(total);

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_sum(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->sum()));
  return {new_ex};
}

exact_numeric exact_numeric::prod() const {
  Exact_number total = 0.0;

  for (size_t i = 0; i < size(); ++i) {
    total *= _storage[i];
  }
  std::vector<Exact_number> result;
  result.push_back(total);

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_prod(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->prod()));
  return {new_ex};
}

exact_numeric exact_numeric::min() const {
  Exact_number minimum = std::numeric_limits<double>::infinity();

  for (size_t i = 0; i < size(); ++i) {
    minimum = CGAL::min(_storage[i], minimum);
  }
  std::vector<Exact_number> result;
  result.push_back(minimum);

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_min(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->min()));
  return {new_ex};
}

exact_numeric exact_numeric::max() const {
  Exact_number minimum = -std::numeric_limits<double>::infinity();

  for (size_t i = 0; i < size(); ++i) {
    minimum = CGAL::max(_storage[i], minimum);
  }
  std::vector<Exact_number> result;
  result.push_back(minimum);

  return {result};
}
[[cpp11::register]]
cpp11::external_pointer<exact_numeric> exact_numeric_max(cpp11::external_pointer<exact_numeric> ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->max()));
  return {new_ex};
}
