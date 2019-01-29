// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_natural(const void *x, const Type x_type);

static const Set N = {
    .symbol = 'N',
    .belongs = &belongs_natural
};

const bool belongs_natural(const void *x, const Type x_type) {
    switch (x_type) {
        case t_unsigned_short_int:
        return true;
        case t_unsigned_int:
        return true;
        case t_unsigned_long_int:
        return true;
        case t_unsigned_long_long_int:
        return true;
        case t_short_int:
        return *((short int *) x) >= 0;
        case t_int:
        return *((int*) x) >= 0;
        case t_long_int:
        return *((long int *) x) >= 0;
        case t_long_long_int:
        return *((long long int *) x) >= 0;
    }
    return false;
}

#endif
