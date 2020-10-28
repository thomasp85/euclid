#pragma once

#include <cstdlib>
#include <stdlib.h>
#include <iostream>

#include <cpp11/R.hpp>

#define cerr clog

namespace std {
inline int _exit_mask(int x) {
  Rf_error("exit called");
}
}
#define exit _exit_mask

namespace std {
inline int _abort_mask() {
  Rf_error("abort called");
}
}
#define abort _abort_mask
