// Empty Set (Ø)
#ifndef algebra_sets_empty_h
#define algebra_sets_empty_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_empty(const Number x);

static const Set E = {
    .symbol = 'E',
    .belongs = &belongs_empty
};

const bool belongs_empty(const Number x) {
    return false;
}

#endif
