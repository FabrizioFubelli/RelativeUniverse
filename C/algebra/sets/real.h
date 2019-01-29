// Set of Real numbers (R)
#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "integer.h"

const bool real_contains(const void *x, const Type type);

const Set R = {
    .symbol = 'R',
    .contains = &real_contains
};

const bool real_contains(const void *x, const Type type) {
    if (Z.contains(x, type)) {
        return true;
    }
    switch (type) {
        case t_float:
        return true;
        case t_double:
        return true;
        case t_long_double:
        return true;
    }
    return false;
}

#endif
