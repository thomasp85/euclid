#include "exact_numeric.h"
#include "match.h"

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
exact_numeric_p create_exact_numeric(cpp11::doubles numeric) {
  exact_numeric* ex_n(new exact_numeric(numeric));

  return {ex_n};
}
[[cpp11::register]]
int exact_numeric_length(exact_numeric_p ex_n) {
  if (ex_n.get() == nullptr) {
    return 0;
  }
  return ex_n->size();
}

exact_numeric exact_numeric::subset(cpp11::integers index) const {
  std::vector<Exact_number> result;
  result.reserve(index.size());

  for (R_xlen_t i = 0; i < index.size(); ++i) {
    if (index[i] == R_NaInt) {
      result.push_back(Exact_number::NA_value());
    } else {
      result.push_back(_storage[index[i] - 1]);
    }
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_subset(exact_numeric_p ex_n, cpp11::integers index) {
  exact_numeric* new_ex(new exact_numeric(ex_n->subset(index)));
  return {new_ex};
}

exact_numeric exact_numeric::assign(cpp11::integers index, const exact_numeric& value) const {
  exact_numeric result = *this;
  int max_size = *std::max_element(index.begin(), index.end());
  if (max_size > result.size()) {
    result._storage.reserve(max_size);
    for (int j = result.size(); j < max_size; ++j) {
      result._storage.push_back(Exact_number::NA_value());
    }
  }
  for (R_xlen_t i = 0; i < index.size(); ++i) {
    result._storage[index[i] - 1] = value[i];
  }

  return result;
}
[[cpp11::register]]
exact_numeric_p exact_numeric_assign(exact_numeric_p ex_n, cpp11::integers index, exact_numeric_p value) {
  exact_numeric* new_ex(new exact_numeric(ex_n->assign(index, *value)));
  return {new_ex};
}

exact_numeric exact_numeric::combine(cpp11::list_of< exact_numeric_p > extra) const {
  exact_numeric result = *this;

  for (R_xlen_t i = 0; i < extra.size(); ++i) {
    for (size_t j = 0; j < extra[i]->size(); ++j) {
      result.push_back(extra[i]->_storage[j]);
    }
  }

  return result;
}
[[cpp11::register]]
exact_numeric_p exact_numeric_combine(exact_numeric_p ex_n, cpp11::list_of<exact_numeric_p> extra) {
  exact_numeric* new_ex(new exact_numeric(ex_n->combine(extra)));
  return {new_ex};
}

cpp11::writable::logicals exact_numeric::is_na() const {
  cpp11::writable::logicals result;
  result.reserve(size());

  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    result.push_back((Rboolean) !(*iter));
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_is_na(exact_numeric_p ex_n) {
  return ex_n->is_na();
}

bool exact_numeric::any_na() const {
  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    if (!(*iter)) {
      return true;
    }
  }
  return false;
}
[[cpp11::register]]
bool exact_numeric_any_na(exact_numeric_p ex_n) {
  return ex_n->any_na();
}

cpp11::writable::doubles exact_numeric::as_numeric() const {
  cpp11::writable::doubles result(size());

  for (size_t i = 0; i < size(); ++i) {
    if (_storage[i]) {
      result[i] = CGAL::to_double(_storage[i].base());
    } else {
      result[i] = R_NaReal;
    }
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::doubles exact_numeric_to_numeric(exact_numeric_p ex_n) {
  if (ex_n.get() == nullptr) {
    return {};
  }
  return ex_n->as_numeric();
}

cpp11::writable::logicals exact_numeric::operator==(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] == x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_is_equal(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) == (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator!=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] != x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_is_not_equal(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) != (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator<(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] < x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_less(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) < (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator<=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] <= x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_less_equal(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) <= (*ex_n2);
}


cpp11::writable::logicals exact_numeric::operator>(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] > x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_greater(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) > (*ex_n2);
}

cpp11::writable::logicals exact_numeric::operator>=(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  cpp11::writable::logicals result(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result[i] = NA_LOGICAL;
      continue;
    }
    result[i] = (Rboolean) (_storage[i % size()] >= x[i % x.size()]);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::logicals exact_numeric_greater_equal(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  return (*ex_n) >= (*ex_n2);
}

exact_numeric exact_numeric::unique() const {
  std::vector<Exact_number> new_storage;
  std::set<Exact_number> uniques;
  bool NA_seen = false;
  for (auto iter = _storage.begin(); iter != _storage.end(); ++iter) {
    if (!iter->is_valid()) {
      if (!NA_seen) {
        new_storage.push_back(Exact_number::NA_value());
        NA_seen = true;
      }
      continue;
    }
    if (uniques.find(*iter) == uniques.end()) {
      uniques.insert(*iter);
      new_storage.push_back(*iter);
    }
  }

  return {new_storage};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_unique(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->unique()));
  return {new_ex};
}

cpp11::writable::logicals exact_numeric::duplicated() const {
  std::set<Exact_number> uniques;
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
cpp11::writable::logicals exact_numeric_duplicated(exact_numeric_p ex_n) {
  return ex_n->duplicated();
}

int exact_numeric::any_duplicated() const {
  std::set<Exact_number> uniques;

  int anyone = -1;
  bool NA_seen = false;

  for (size_t i = 0; i < _storage.size(); ++i) {
    if (!_storage[i].is_valid()) {
      if (NA_seen) {
        anyone = i;
        break;
      }
      NA_seen = true;
    } else if (uniques.find(_storage[i]) == uniques.end()) {
      uniques.insert(_storage[i]);
    } else {
      anyone = i;
      break;
    }
  }

  return anyone;
}
[[cpp11::register]]
int exact_numeric_any_duplicated(exact_numeric_p ex_n) {
  return ex_n->any_duplicated() + 1;
}

cpp11::writable::integers exact_numeric::rank() const {
  std::vector< std::pair<Exact_number, size_t> > ranks;
  ranks.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    ranks.emplace_back(_storage[i], i);
  }

  std::stable_sort(ranks.begin(), ranks.end(), [](const std::pair<Exact_number, size_t>& l, const std::pair<Exact_number, size_t> & r) {
    if (l.first && r.first) {
      return l.first < r.first;
    } else if (l.first) {
      return true;
    }
    return false;
  });

  cpp11::writable::integers result;
  result.reserve(size());
  for (auto iter = ranks.begin(); iter != ranks.end(); ++iter) {
    result.push_back(iter->second + 1);
  }

  return result;
}
[[cpp11::register]]
cpp11::writable::integers exact_numeric_rank(exact_numeric_p ex_n) {
  return ex_n->rank();
}

cpp11::writable::integers exact_numeric::match(const exact_numeric& table) const {
  return match_impl(_storage, table._storage);
}
[[cpp11::register]]
cpp11::writable::integers exact_numeric_match(exact_numeric_p ex_n, exact_numeric_p table) {
  return ex_n->match(*table);
}

exact_numeric exact_numeric::operator+(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(_storage[i % size()] + x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_plus(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) + (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator-(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(_storage[i % size()] - x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_minus(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) - (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator-() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    if (!_storage[i]) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(-_storage[i]);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_uni_minus(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(-(*ex_n)));
  return {new_ex};
}

exact_numeric exact_numeric::operator*(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()]) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(_storage[i % size()] * x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_times(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) * (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::operator/(const exact_numeric& x) const {
  size_t output_length = std::max(size(), x.size());

  std::vector<Exact_number> result;
  result.reserve(output_length);

  for (size_t i = 0; i < output_length; ++i) {
    if (!_storage[i % size()] || !x[i % x.size()] || x[i % x.size()] == 0.0) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(_storage[i % size()] / x[i % x.size()]);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_divided(exact_numeric_p ex_n, exact_numeric_p ex_n2) {
  exact_numeric* new_ex(new exact_numeric((*ex_n) / (*ex_n2)));
  return {new_ex};
}

exact_numeric exact_numeric::abs() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  for (size_t i = 0; i < size(); ++i) {
    if (!_storage[i]) {
      result.push_back(Exact_number::NA_value());
      continue;
    }
    result.push_back(CGAL::abs(_storage[i].base()));
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_abs(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->abs()));
  return {new_ex};
}

cpp11::writable::integers exact_numeric::sign() const {
  cpp11::writable::integers result(size());

  for (size_t i = 0; i < size(); ++i) {
    if (!_storage[i]) {
      result[i] = R_NaInt;
      continue;
    }
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
cpp11::writable::integers exact_numeric_sign(exact_numeric_p ex_n) {
  return ex_n->sign();
}

exact_numeric exact_numeric::cumsum() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  Exact_number cum_sum = 0.0;
  bool is_na = false;

  for (size_t i = 0; i < size(); ++i) {
    if (!is_na && !_storage[i]) {
      is_na = true;
      cum_sum = Exact_number::NA_value();
    }
    if (!is_na) {
      cum_sum += _storage[i];
    }
    result.push_back(cum_sum);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_cumsum(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cumsum()));
  return {new_ex};
}

exact_numeric exact_numeric::cumprod() const {
  std::vector<Exact_number> result;
  result.reserve(size());

  Exact_number cum_prod = 0.0;
  bool is_na = false;

  for (size_t i = 0; i < size(); ++i) {
    if (!is_na && !_storage[i]) {
      is_na = true;
      cum_prod = Exact_number::NA_value();
    }
    if (!is_na) {
      cum_prod *= _storage[i];
    }
    result.push_back(cum_prod);
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_cumprod(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cumprod()));
  return {new_ex};
}

exact_numeric exact_numeric::cummax() const {
  std::vector<Exact_number> result;
  result.reserve(size());
  if (size() != 0) {
    Exact_number cum_max = _storage[0];
    bool is_na = !cum_max;

    for (size_t i = 0; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_max = Exact_number::NA_value();
      }
      if (!is_na) {
        cum_max = CGAL::max(_storage[i], cum_max);
      }
      result.push_back(cum_max);
    }
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_cummax(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cummax()));
  return {new_ex};
}

exact_numeric exact_numeric::cummin() const {
  std::vector<Exact_number> result;
  result.reserve(size());
  if (size() != 0) {
    Exact_number cum_min = _storage[0];
    bool is_na = !cum_min;

    for (size_t i = 0; i < size(); ++i) {
      if (!is_na && !_storage[i]) {
        is_na = true;
        cum_min = Exact_number::NA_value();
      }
      if (!is_na) {
        cum_min = CGAL::max(_storage[i], cum_min);
      }
      result.push_back(cum_min);
    }
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_cummin(exact_numeric_p ex_n) {
  exact_numeric* new_ex(new exact_numeric(ex_n->cummin()));
  return {new_ex};
}

exact_numeric exact_numeric::diff(int lag) const {
  std::vector<Exact_number> result;
  if (size() >= lag) {
    result.reserve(size() - lag);

    for (size_t i = 0; i < size() - lag; ++i) {
      if (!_storage[i + lag] || !_storage[i]) {
        result.push_back(Exact_number::NA_value());
      } else {
        result.push_back(_storage[i + lag] - _storage[i]);
      }
    }
  }

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_diff(exact_numeric_p ex_n, int lag) {
  exact_numeric* new_ex(new exact_numeric(ex_n->diff(lag)));
  return {new_ex};
}

exact_numeric exact_numeric::sort(bool decreasing, cpp11::logicals na_last) const {
  exact_numeric result = *this;

  auto end = std::remove_if(result._storage.begin(), result._storage.end(), [](const Exact_number& x) { return !x.is_valid(); });
  int n_na = result._storage.end() - end;
  result._storage.resize(end - result._storage.begin());

  if (decreasing) {
    std::stable_sort(result._storage.begin(), result._storage.end(), std::greater<Exact_number>());
  } else {
    std::stable_sort(result._storage.begin(), result._storage.end());
  }

  if (cpp11::is_na(na_last[0])) {
    for (int i = 0; i < n_na; ++i) {
      result._storage.push_back(Exact_number::NA_value());
    }
    if (n_na > 0 && na_last[0] == FALSE) {
      std::rotate(result._storage.rbegin(), result._storage.rbegin() + n_na, result._storage.rend());
    }
  }

  return result;
}
[[cpp11::register]]
exact_numeric_p exact_numeric_sort(exact_numeric_p ex_n, bool decreasing, cpp11::logicals na_last) {
  exact_numeric* new_ex(new exact_numeric(ex_n->sort(decreasing, na_last)));
  return {new_ex};
}

exact_numeric exact_numeric::sum(bool na_rm) const {
  Exact_number total = 0.0;

  for (size_t i = 0; i < size(); ++i) {
    if (!_storage[i]) {
      if (!na_rm) {
        total = Exact_number::NA_value();
        break;
      }
      continue;
    }
    total += _storage[i];
  }
  std::vector<Exact_number> result;
  result.push_back(total);

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_sum(exact_numeric_p ex_n, bool na_rm) {
  exact_numeric* new_ex(new exact_numeric(ex_n->sum(na_rm)));
  return {new_ex};
}

exact_numeric exact_numeric::prod(bool na_rm) const {
  Exact_number total = 1.0;

  for (size_t i = 0; i < size(); ++i) {
    if (!_storage[i]) {
      if (!na_rm) {
        total = Exact_number::NA_value();
        break;
      }
      continue;
    }
    total *= _storage[i];
  }
  std::vector<Exact_number> result;
  result.push_back(total);

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_prod(exact_numeric_p ex_n, bool na_rm) {
  exact_numeric* new_ex(new exact_numeric(ex_n->prod(na_rm)));
  return {new_ex};
}

exact_numeric exact_numeric::min(bool na_rm) const {
  Exact_number minimum;

  if (size() == 0) {
    minimum = Exact_number::NA_value();
  } else {
    minimum = _storage[0];
    for (size_t i = 1; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          minimum = Exact_number::NA_value();
          break;
        }
        continue;
      }
      minimum = CGAL::min(_storage[i], minimum);
    }
  }

  std::vector<Exact_number> result;
  result.push_back(minimum);

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_min(exact_numeric_p ex_n, bool na_rm) {
  exact_numeric* new_ex(new exact_numeric(ex_n->min(na_rm)));
  return {new_ex};
}

exact_numeric exact_numeric::max(bool na_rm) const {
  Exact_number maximum;

  if (size() == 0) {
    maximum = Exact_number::NA_value();
  } else {
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        if (!na_rm) {
          maximum = Exact_number::NA_value();
          break;
        }
        continue;
      }
      maximum = CGAL::max(_storage[i], maximum);
    }
  }

  std::vector<Exact_number> result;
  result.push_back(maximum);

  return {result};
}
[[cpp11::register]]
exact_numeric_p exact_numeric_max(exact_numeric_p ex_n, bool na_rm) {
  exact_numeric* new_ex(new exact_numeric(ex_n->max(na_rm)));
  return {new_ex};
}
