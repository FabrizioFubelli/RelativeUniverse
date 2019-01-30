// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include "../../utils/util.h"
#include "set_interface.h"

const bool belongs_natural(const Number x);

static const Set N = {
    .symbol = 'N',
    .belongs2 = &belongs_natural
};

const bool belongs_natural(const Number x) {
    long long int int_part = (long long int) x;
    Number dec_part = x - int_part;
    printf("belongs_natural(x) -> int=%lld, decimal=%Lf\n", int_part, dec_part);
    //double fractional = modf(x, &integral);
    return false;
}

#endif
