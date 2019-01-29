// Universe Set (U)
#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool universe_contains(const void *x, const Type type);

static const Set U = {
    .symbol = 'U',
    .contains = &universe_contains
};

const bool universe_contains(const void *x, const Type type) {
    return true;
}

#endif
