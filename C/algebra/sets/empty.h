// Empty Set (Ø)
#ifndef algebra_sets_empty_h
#define algebra_sets_empty_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_empty(const Number x);

static const Set E = {
    .symbol = 'E',
    .parent = &U,
    .belongs = &belongs_empty,
    .rules_tot = 1,
    .rules = {EMPTY}
};

const bool belongs_empty(const Number x) {
    return belongs_to_set(x, E);
}

#endif
