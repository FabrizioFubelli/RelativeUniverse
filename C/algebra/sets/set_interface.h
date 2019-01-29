#ifndef algebra_sets_set_interface_h
#define algebra_sets_set_interface_h

#include <stdbool.h>

#include "../../utils/util.h"

#define setname(x) _Generic((x),        /* Get the name of a type */              \
          Set: t_set,                            Empty: t_empty_set,              \
      Complex: t_complex_set,                Imaginary: t_imaginary_set,          \
      Integer: t_integer_set,               Irrational: t_irrational_set,         \
      Natural: t_natural_set,                 Rational: t_rational_set,           \
         Real: t_real_set,                    Universe: t_universe_set,           \
      default: t_other)

typedef struct set Set;

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
 * @return `x ∊ A`
*/
bool set_contains(const Set X, const void *x, const Type type) {
    return X.contains(x, type);
}

#endif
