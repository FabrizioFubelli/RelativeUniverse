// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_natural(const Number x);

static const Set N = {
    .symbol = 'N',
    .belongs = &belongs_natural
};

const bool belongs_natural(const Number x) {
    return (x - ((long long int) x)) == 0;
}

#endif
