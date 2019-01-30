// Universe Set (U)
#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_universe(const Number x);

static const Set U = {
    .symbol = 'U',
    .parent = NULL,
    .belongs = &belongs_universe,
    .rules_tot = 0,
    .rules = {}
};

const bool belongs_universe(const Number x) {
    return belongs_to_set(x, U);
}

#endif
