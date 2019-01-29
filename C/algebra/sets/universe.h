// Universe Set (U)
#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_universe(const void *x, const Type x_type);

static const Set U = {
    .symbol = 'U',
    .belongs = &belongs_universe
};

const bool belongs_universe(const void *x, const Type x_type) {
    return true;
}

#endif
