// Example Sets
#ifndef algebra_sets_examples_h
#define algebra_sets_examples_h

#include "../../utils/util.h"
#include "sets.h"

const bool belongs_even(const void *x, const Type x_type);
const bool belongs_odd(const void *x, const Type x_type);

// Example of all even natural numbers
const static Set E = {
    .symbol = 'E',
    .belongs = &belongs_even
};

// Example of all odd natural numbers
const static Set O = {
    .symbol = 'O',
    .belongs = &belongs_odd
};


const bool belongs_even(const void *x, const Type x_type) {
    if (!N.belongs(x, x_type)) {
        return false;
    }
    switch (x_type) {
        case t_unsigned_short_int:
        return *((unsigned short int *) x) %2 == 0;
        case t_unsigned_int:
        return *((unsigned int *) x) %2 == 0;
        case t_unsigned_long_int:
        return *((unsigned long int *) x) %2 == 0;
        case t_unsigned_long_long_int:
        return *((unsigned long long int *) x) %2 == 0;
        case t_short_int:
        return *((short int *) x) %2 == 0;
        case t_int:
        return *((int*) x) %2 == 0;
        case t_long_int:
        return *((long int *) x) %2 == 0;
        case t_long_long_int:
        return *((long long int *) x) %2 == 0;
    }
    return false;
}

const bool belongs_odd(const void *x, const Type x_type) {
    return N.belongs(x, x_type) && !E.belongs(x, x_type);
}

#endif
