#include <stdio.h>
#include <math.h>

#include "../../utils/util.h"
#include "sets.h"
#include "examples.h"

int main() {
    printf("Hello Sets!\n\n");
    long double d = sqrt(2);
    printf("sqrt(2) = %Lf\n", d);
    printf("typename(sqrt(2)) = %s\n", str_typename(typename(d)));

    /*
     * N = Natural numbers
     * Z = Integers
     * R = Real numbers
     * E = Even numbers
     * O = Odd numbers
     */

    bool belongs;

    {
        long long int n = 16436238;

        belongs = belongs_to_set(&n, t_long_long_int, E);
        printf("belongs_to_set(%lld, E) = %d    # Even numbers\n", n, belongs);

        belongs = belongs_to_set(&n, t_long_long_int, O);
        printf("belongs_to_set(%lld, O) = %d    # Odd numbers\n", n, belongs);
    }

    return 0;
}
