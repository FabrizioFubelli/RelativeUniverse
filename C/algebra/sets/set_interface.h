#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

typedef struct set Set;

#include <stdbool.h>

#include "../../utils/util.h"

/* Set of Objects */
struct set
{
    const char symbol;
    const bool (*contains)(const void *, const Type);
};

/*
 * @return `A ⊂ B`
*/
static bool set_includes(const Set A, const Set B) {
    printf("set_includes\n");
}

/*
 * @return `A ⊃ B`
*/
static bool set_is_included(const Set A, const Set B) {
    printf("set_is_included\n");
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set A, const Set B) {
    const bool intersection_contains(const void * x, const Type x_type) {
        return A.contains(x, x_type) && B.contains(x, x_type);
    }
    const Set C = {
        .symbol = 'C',
        .contains = &intersection_contains
    };
    return C;
}

/*
 * @return `A ∪ B`
*/
static Set set_union(const Set A, const Set B) {
    const bool union_contains(const void * x, const Type x_type) {
        return A.contains(x, x_type) || B.contains(x, x_type);
    }
    const Set C = {
        .symbol = 'C',
        .contains = &union_contains
    };
    return C;
}

/*
 * @return `x ∊ A`
*/
static bool set_contains(const Set X, const void *x, const Type x_type) {
    return X.contains(x, x_type);
}

#endif
