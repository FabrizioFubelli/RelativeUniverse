#ifndef algebra_sets_set_relations_h
#define algebra_sets_set_relations_h

#include <stdbool.h>

typedef unsigned int (*rules_fun)();
typedef struct relation Relation;
typedef enum relaction_types {
    AND, OR
} RelactionType;

#include "../../utils/util.h"
#include "set_interface.h"

struct relation
{
    const Set *A;
    const Set *B;
    const RelactionType type;
    const unsigned int rules_tot;
    const rules_fun get_rule_numbers;
};

#endif
