#include <stdio.h>
#include <stddef.h>

#include "../../utils/util.h"
#include "sets.h"

#include "natural.h"

int main() {
    printf("Hello Set!\n");

    Set generic;
    enum type type_generic = typename(generic);
    printf("type_generic: %s\n", str_typename(type_generic));

    Natural natural;
    enum type type_natural = typename(natural);
    printf("type_generic: %s\n", str_typename(type_natural));

    return 0;
}
