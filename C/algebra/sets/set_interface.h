#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

typedef struct set Set;

#include <stdbool.h>

#include "../../utils/util.h"

/* Set of Objects */
struct set
{
    const char symbol;
    const bool (*belongs)(const void *, const Type);
};

/*
 * @return `A ⊂ B`
*/
static bool set_includes(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ⊃ B`
*/
static bool set_is_included(const Set A, const Set B) {
    printf("NOT IMPLEMENTED\n");
}

/*
 * @return `A ∩ B`
*/
static Set set_intersection(const Set A, const Set B) {
    const bool belongs_intersection(const void * x, const Type x_type) {
        return A.belongs(x, x_type) && B.belongs(x, x_type);
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
    const bool belongs_union(const void * x, const Type x_type) {
        return A.belongs(x, x_type) || B.belongs(x, x_type);
    }
    const Set C = {
        .symbol = 'C',
        .belongs = &belongs_union
    };
    return C;
}

/*
 * @return `x ∊ A`
*/
static bool belongs_to_set(const void *x, const Type x_type, const Set X) {
    return X.belongs(x, x_type);
}

#endif
