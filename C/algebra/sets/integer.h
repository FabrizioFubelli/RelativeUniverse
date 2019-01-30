// Set of Integers (Z)
#ifndef algebra_sets_integer_h
#define algebra_sets_integer_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "natural.h"

const bool belongs_integer(const Number x);

static const Set Z = {
    .symbol = 'Z',
    .belongs = &belongs_integer
};

const bool belongs_integer(const Number x) {
    return N.belongs(x) || N.belongs(-x);
}

#endif
