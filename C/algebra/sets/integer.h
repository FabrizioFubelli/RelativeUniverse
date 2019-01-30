// Set of Integers (Z)
#ifndef algebra_sets_integer_h
#define algebra_sets_integer_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "real.h"

const bool belongs_integer(const Number x);

static const Set Z = {
    .symbol = 'Z',
    .parent = &R,
    .belongs = &belongs_integer,
    .rules_tot = 1,
    .rules = {ONLY_INTEGERS}
};

const bool belongs_integer(const Number x) {
    return belongs_to_set(x, Z);
}

#endif
