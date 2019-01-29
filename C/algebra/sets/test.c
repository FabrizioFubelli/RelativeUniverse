#include <stdio.h>

#include "../../utils/util.h"
#include "sets.h"

int main() {
    printf("Hello Sets!\n\n");

    bool belongs;

    {
        long long int i = -4469989451615;

        belongs = set_contains(Z, &i, t_long_long_int);
        printf("set_contains(Z, %lld) = %d\n", i, belongs);

        belongs = set_contains(N, &i, t_long_long_int);
        printf("set_contains(N, %lld) = %d\n", i, belongs);
    }

    /*{
        long double i = 1023.123;

        belongs = set_contains(Z, &i, t_long_double);
        printf("set_contains(Z, %Lf) = %d\n", i, belongs);

        belongs = set_contains(R, &i, t_long_double);
        printf("set_contains(R, %Lf) = %d\n", i, belongs);
    }

    set_includes(Z, N);*/

    return 0;
}
