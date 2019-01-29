// Set of Integers (Z)
#ifndef algebra_sets_integer_h
#define algebra_sets_integer_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "natural.h"

const bool integer_contains(const void *x, const Type x_type);

static const Set Z = {
    .symbol = 'Z',
    .contains = &integer_contains
};

const bool integer_contains(const void *x, const Type x_type) {
    if (N.contains(x, x_type)) {
        return true;
    }
    switch (x_type) {
        case t_short_int:
        return true;
        case t_int:
        return true;
        case t_long_int:
        return true;
        case t_long_long_int:
        return true;
    }
    return false;
}

#endif
