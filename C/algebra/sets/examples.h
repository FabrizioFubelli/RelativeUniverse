// Example Sets
#ifndef algebra_sets_examples_h
#define algebra_sets_examples_h

#include "../../utils/number.h"
#include "natural.h"

const bool belongs_even(Number x);
const bool belongs_odd(const Number x);

// Example of all even natural numbers
const static Set P = {
    .symbol = 'P',
    .parent = &N,
    .belongs = &belongs_even,
    .rules_tot = 1,
    .rules = {ONLY_EVEN}
};
const bool belongs_even(Number x) {
    return belongs_to_set(x, P);
}

// Example of all odd natural numbers
const static Set D = {
    .symbol = 'D',
    .parent = &N,
    .belongs = &belongs_odd,
    .rules_tot = 1,
    .rules = {ONLY_ODD}
};
const bool belongs_odd(const Number x) {
    return belongs_to_set(x, D);
}

#endif
