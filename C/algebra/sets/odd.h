// Set of Odd numbers (D)
#ifndef algebra_sets_odd_h
#define algebra_sets_odd_h

#include "../../utils/number.h"
#include "integer.h"



//---- Static constants
#define N_RULES_ODD 1
#define N_RELATIONS_ODD_AND 1
#define N_RELATIONS_ODD_OR 0



//---- Function declarations
const Relations *get_relations_odd(const Set *self);



//---- Static variables
static Relations *relations_odd = NULL;



//---- Main struct
const static Set D = {
    .symbol = "D",
    .belongs = &belongs_to_set,
    .relations = &get_relations_odd,
};



//---- Function implementations

const Relations *get_relations_odd(const Set *self) {
    if (relations_odd != NULL) {
        return relations_odd;
    }

    //-- OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_ODD_OR);

    // AND relations
    const Relation and_1 = {
        .A = &Z,
        .B = &E,
        .type = OR
    };
    const Relation **and_relations = get_relations_part(N_RELATIONS_ODD_AND, &and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_ODD, ONLY_ODD);

    // All Relations
    relations_odd = get_relations(or_relations, and_relations,
        N_RELATIONS_ODD_OR, N_RELATIONS_ODD_AND, rules, N_RULES_ODD);

    return relations_odd;
}

#endif
