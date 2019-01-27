#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

#define type(T)  typeof(T *)

#include <stdbool.h>

/* Set of Objects (Insieme) */
typedef struct set Set
{

    /*
     * @return `x ∊ Set`
    */
    bool
    bool contains()
};

#endif
