#pragma once

#include <vector>
#include <limits>
#include <cpp11/doubles.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>
#include "cgal_types.h"

class exact_numeric {
private:
  std::vector<Exact_number> _storage;

public:
  exact_numeric() {}
  ~exact_numeric() {}

  // Construction
  exact_numeric(const cpp11::doubles& x) {
    _storage.reserve(x.size());
    for (R_xlen_t i = 0; i < x.size(); ++i) {
      if (R_finite(x[i])) {
        _storage.emplace_back(x[i]);
      } else {
        _storage.push_back(Exact_number::NA_value());
      }
    }
  }
  exact_numeric(const std::vector<double>& x) : _storage(x.begin(), x.end()) {}
  exact_numeric(std::vector<Exact_number>& x) {
    _storage.swap(x);
  }
  exact_numeric(const exact_numeric& x) : _storage(x._storage) {}
  exact_numeric& operator=(const exact_numeric& copy) {
    _storage.clear();
    _storage.insert(_storage.end(), copy._storage.begin(), copy._storage.end());
    return *this;
  }
  const std::vector<Exact_number>& get_storage() { return _storage; }

  // Utility
  size_t size() const {
    return _storage.size();
  }
  Exact_number operator[](size_t index) const {
    return _storage[index];
  }
  void clear() { _storage.clear(); }
  void swap(exact_numeric& x) { _storage.swap(x._storage); }
  void push_back(Exact_number x) { _storage.push_back(x); }
  exact_numeric subset(cpp11::integers index) const;
  exact_numeric assign(cpp11::integers index, const exact_numeric& value) const;
  exact_numeric combine(cpp11::list_of< cpp11::external_pointer<exact_numeric> > extra) const;
  cpp11::writable::logicals is_na() const;
  bool any_na() const;

  // Convert back
  cpp11::writable::doubles as_numeric() const;

  // Relation
  cpp11::writable::logicals operator==(const exact_numeric& x) const;
  cpp11::writable::logicals operator<(const exact_numeric& x) const;
  cpp11::writable::logicals operator>(const exact_numeric& x) const;
  exact_numeric unique() const;
  cpp11::writable::logicals duplicated() const;
  int any_duplicated() const;
  cpp11::writable::integers rank() const;
  cpp11::writable::integers match(const exact_numeric& table) const;

  // Math
  exact_numeric operator+(const exact_numeric& x) const;
  exact_numeric operator-(const exact_numeric& x) const;
  exact_numeric operator-() const;
  exact_numeric operator*(const exact_numeric& x) const;
  exact_numeric operator/(const exact_numeric& x) const;

  exact_numeric abs() const;
  cpp11::writable::integers sign() const;

  exact_numeric cumsum() const;
  exact_numeric cumprod() const;
  exact_numeric cummax() const;
  exact_numeric cummin() const;
  exact_numeric diff(int lag) const;
  exact_numeric sort(bool decreasing, cpp11::logicals na_last) const;

  // Summary
  exact_numeric sum(bool na_rm) const;
  exact_numeric prod(bool na_rm) const;
  exact_numeric min(bool na_rm) const;
  exact_numeric max(bool na_rm) const;
};

typedef cpp11::external_pointer<exact_numeric> exact_numeric_p;
