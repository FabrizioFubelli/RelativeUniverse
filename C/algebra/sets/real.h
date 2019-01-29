// Set of Real numbers (R)
#ifndef algebra_sets_real_h
#define algebra_sets_real_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "integer.h"

const bool belongs_real(const void *x, const Type x_type);

static const Set R = {
    .symbol = 'R',
    .belongs = &belongs_real
};

const bool belongs_real(const void *x, const Type x_type) {
    if (Z.belongs(x, x_type)) {
        return true;
    }
    switch (x_type) {
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
