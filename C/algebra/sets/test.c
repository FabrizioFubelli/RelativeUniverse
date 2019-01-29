#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "../../utils/util.h"
#include "sets.h"

int main() {
    printf("Hello Set!\n");

    Set generic;
    Type type_generic = typename(generic);
    printf("type_generic: %s\n", str_typename(type_generic));

    Type type_N = typename(N);
    printf("N: %s\n", str_typename(type_N));
    printf("N.symbol: %c\n", N.symbol);


    const Type *N_accepted_types = N.accepted_types;

    Empty empty;
    Type type_empty = typename(empty);
    printf("type_empty: %s\n", str_typename(type_empty));

    unsigned a=100;
    float a2= ((float) a)-5.6;
    printf("a: %s\n", str_typename(typename(a)));
    printf("a2 type: %s\n", str_typename(typename(a2)));
    printf("a2: %f\n", a2);
    return 0;
}
