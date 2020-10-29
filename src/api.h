#pragma once

#include <cpp11/R.hpp>
#include <cpp11/external_pointer.hpp>

template<typename T>
cpp11::external_pointer<T> get_ext_pointer(SEXP val) {
  if (TYPEOF(val) != VECSXP) {
    cpp11::stop("Provided object not an euclid class");
  }
  SEXP pointer = VECTOR_ELT(val, 0);
  if (TYPEOF(val) != EXTPTRSXP) {
    cpp11::stop("Provided object not an euclid class");
  }
  cpp11::external_pointer<T> ex_p(pointer);
  if (ex_p.get() == nullptr) {
    cpp11::stop("Provided object is not of the correct class");
  }
  return ex_p;
}
