#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

typedef struct set Set;

#include <stdbool.h>

#include "../../utils/util.h"

/* Set of Objects */
struct set
{
    const char symbol;
    const bool (*belongs)(const Number n);
};

/*
 * @return `A ⊆ B`
*/
static bool is_subset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊇ B`
*/
static bool is_superset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊂ B`
*/
static bool is_proper_subset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊃ B`
*/
static bool is_proper_superset(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set A, const Set B) {
    const bool belongs_intersection(Number x) {
        return A.belongs(x) && B.belongs(x);
    }
    const Set C = {
        .symbol = 'C',
        .belongs = &belongs_intersection
    };
    return C;
}

/*
 * @return `A ∪ B`
*/
static Set set_union(const Set A, const Set B) {
    const bool belongs_union(Number x) {
        return A.belongs(x) || B.belongs(x);
    }
    const Set C = {
        .symbol = 'C',
        .belongs = &belongs_union
    };
    return C;
}

/*
 * @return `P(X)`: all subsets of X
*/
static Set set_power(const Set X) {
    printf("NOT IMPLEMENTED");
}

/*
 * @return `x ∊ A`
*/
static bool belongs_to_set(const Number x, const Set X) {
    return X.belongs(x);
}

#endif
