// Set of Real numbers (R)
#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "universe.h"

const bool belongs_real(const Number x);

static const Set R = {
    .symbol = 'R',
    .parent = &U,
    .belongs = &belongs_real,
    .rules_tot = 0,
    .rules = {}
};

const bool belongs_real(const Number x) {
    return belongs_to_set(x, R);
}

#endif
