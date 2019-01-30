// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "integer.h"

const bool belongs_natural(const Number x);

static const Set N = {
    .symbol = 'N',
    .parent = &Z,
    .belongs = &belongs_natural,
    .rules_tot = 1,
    .rules = {ONLY_NATURAL}
};

const bool belongs_natural(const Number x) {
    return belongs_to_set(x, N);
}

#endif
