// Universe Set (U)
#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_universe(const Number x);

static const Set U = {
    .symbol = 'U',
    .belongs = &belongs_universe
};

const bool belongs_universe(const Number x) {
    return true;
}

#endif
