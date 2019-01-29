#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "../../utils/util.h"
#include "sets.h"

int main() {
    printf("Hello Sets!\n\n");

    long long int i = 4467489989451615;
    printf("N.contains(%lld) = %d\n", i, N.contains(&i, t_long_long_int));

    Set N_check = {
        .symbol = N.symbol,
        .contains = N.contains
    };

    bool belongs = set_contains(&N, &i, t_long_long_int);

    printf("set_contains(N, %lld) = %d\n", i, belongs);

    set_is_included(&N_check, &N);

    return 0;
}
