// Set of Real numbers (R)
#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "universe.h"

const bool belongs_real(const Number x);

static const Set R = {
    .symbol = 'R',
    .belongs = &belongs_real
};

const bool belongs_real(const Number x) {
    // Check complex, imaginary ?
    return U.belongs(x);
}

#endif
