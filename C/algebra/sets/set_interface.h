#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

#include <stdbool.h>

#include "../../utils/util.h"

typedef struct set Set;

/* Set of Objects (Example) */
struct set
{
    const Type accepted_types[1];
    const char symbol;
};

/*
 * @return `A ⊂ B`
*/
static bool set_includes(Set A, Set B) {
    printf("set_includes\n");
}

/*
 * @return `A ⊃ B`
*/
static bool set_is_included(Set A, Set B) {
    printf("set_is_included\n");
}

/*
 * @return `x ∊ A`
*/
bool set_belongs(Set x, Set A) {
    printf("set_belongs\n");
}

#endif
