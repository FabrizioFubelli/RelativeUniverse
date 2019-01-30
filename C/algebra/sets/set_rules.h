#ifndef algebra_sets_set_rules_h
#define algebra_sets_set_rules_h

#include <stdbool.h>
#include <math.h>

enum rule_numbers {
    ONLY_INTEGERS=1,
    ONLY_NATURAL,
    ONLY_EVEN,
    ONLY_ODD,
    EMPTY
};

#include "../../utils/util.h"
#include "set_interface.h"

typedef bool (*Rule)(const Set X, const Number x);

static bool only_integers(const Set X, const Number x);
static bool only_natural(const Set X, const Number x);
static bool only_even(const Set X, const Number x);
static bool only_odd(const Set X, const Number x);
static bool empty(const Set X, const Number x);

static const Rule SET_RULES[] = {
    [ONLY_INTEGERS] = only_integers,
    [ONLY_NATURAL] = only_natural,
    [ONLY_EVEN] = only_even,
    [ONLY_ODD] = only_odd,
    [EMPTY] = empty,
};

/*
 * 1
*/
static bool only_integers(const Set X, const Number x) {
    return (x - ((long long int) x)) == 0;
}

/*
 * 2
*/
static bool only_natural(const Set X, const Number x) {
    return x >= (Number) 0;
}

/*
 * 3
*/
static bool only_even(const Set X, const Number x) {
    return remainder(x, 2) == 0;
}

/*
 * 4
*/
static bool only_odd(const Set X, const Number x) {
    return remainder(x, 2) != 0;
}

/*
 * 5
*/
static bool empty(const Set X, const Number x) {
    return false;
}

#endif
