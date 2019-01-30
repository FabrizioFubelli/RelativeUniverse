// Example Sets
#ifndef algebra_sets_examples_h
#define algebra_sets_examples_h

#include <math.h>
#include "../../utils/util.h"
#include "sets.h"

const bool belongs_even(Number x);
const bool belongs_odd(const Number x);


// Example of all even natural numbers
const static Set E = {
    .symbol = 'E',
    .belongs = &belongs_even
};
const bool belongs_even(Number x) {
    //printf("%d\n", pow(x, 2));
    return N.belongs(x);
}


// Example of all odd natural numbers
const static Set O = {
    .symbol = 'O',
    .belongs = &belongs_odd
};
const bool belongs_odd(const Number x) {
    return N.belongs(x) && !E.belongs(x);
}

#endif
