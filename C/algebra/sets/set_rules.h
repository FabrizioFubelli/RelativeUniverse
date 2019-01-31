#ifndef algebra_sets_set_rules_h
#define algebra_sets_set_rules_h

#include <stdbool.h>
#include <math.h>

enum rule_numbers {
    ONLY_INTEGERS=1,    // 1
    ONLY_NATURAL,       // 2
    ONLY_EVEN,          // 3
    ONLY_ODD,           // 4
    EMPTY,              // 5
};

static char *rule_to_string(unsigned int index) {
    char *rule_name;
    switch (index) {
        case ONLY_INTEGERS:
        rule_name = "ONLY_INTEGERS"; break;
        case ONLY_NATURAL:
        rule_name = "ONLY_NATURAL"; break;
        case ONLY_EVEN:
        rule_name = "ONLY_EVEN"; break;
        case ONLY_ODD:
        rule_name = "ONLY_ODD"; break;
        case EMPTY:
        rule_name = "EMPTY"; break;
        default:
        rule_name = "UNKNOWN"; break;
    }
    char *s_index = malloc(sizeof(char)*50);
    sprintf(s_index, "%u) %s", index, rule_name);
    return s_index;
}

#include "../../utils/util.h"
#include "set_interface.h"

typedef bool (*Rule)(const Number x);

static bool only_integers(const Number x);
static bool only_natural(const Number x);
static bool only_even(const Number x);
static bool only_odd(const Number x);
static bool empty(const Number x);

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
static bool only_integers(const Number x) {
    return (x - ((long long int) x)) == 0;
}

/*
 * 2
*/
static bool only_natural(const Number x) {
    return x >= (Number) 0;
}

/*
 * 3
*/
static bool only_even(const Number x) {
    return remainder(x, 2) == 0;
}

/*
 * 4
*/
static bool only_odd(const Number x) {
    return remainder(x, 2) != 0;
}

/*
 * 5
*/
static bool empty(const Number x) {
    return false;
}

#endif
