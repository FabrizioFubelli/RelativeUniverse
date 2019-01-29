// Example Sets
#ifndef algebra_sets_examples_h
#define algebra_sets_examples_h

#include "../../utils/util.h"
#include "sets.h"

// Example of all even natural numbers
const bool even_contains(const void *x, const Type x_type) {
    if (!N.contains(x, x_type)) {
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
const static Set E = {
    .symbol = 'E',
    .contains = &even_contains
};

// Example of all odd natural numbers
const bool odd_contains(const void *x, const Type x_type) {
    return N.contains(x, x_type) && !E.contains(x, x_type);
}
const static Set O = {
    .symbol = 'O',
    .contains = &odd_contains
};

#endif
