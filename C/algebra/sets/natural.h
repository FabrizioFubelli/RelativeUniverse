// Set of Natural numbers (N)
#ifndef algebra_sets_natural_h
#define algebra_sets_natural_h

#include <stdlib.h>
#include "../../utils/util.h"
#include "set_interface.h"

typedef struct natural
{
    const char symbol;
    const Type accepted_types[4];
} Natural;

const Natural N = {
    .symbol = 'N',
    .accepted_types = {
         t_unsigned_short_int, t_unsigned_int, t_unsigned_long_int,
         t_unsigned_long_long_int
     }
};

#endif
