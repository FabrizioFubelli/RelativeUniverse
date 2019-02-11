// Set of Even numbers (P)
#ifndef algebra_sets_even_h
#define algebra_sets_even_h

#include "../../utils/number.h"
#include "natural.h"



//---- Static constants
#define N_RULES_EVEN 1
#define N_RELATIONS_EVEN_AND 1
#define N_RELATIONS_EVEN_OR 0



//---- Function declarations
const Relations *get_relations_even(const Set *self);



//---- Static variables
static Relations *relations_even = NULL;



//---- Main struct
const static Set P = {
    .symbol = "P",
    .belongs = &belongs_to_set,
    .relations = &get_relations_even,
};



//---- Function implementations

const Relations *get_relations_even(const Set *self) {
    if (relations_even != NULL) {
        return relations_even;
    }

    //-- OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_EVEN_OR);

    // AND relations
    const Relation and_1 = {
        .A = &N,
        .B = &E,
        .type = OR
    };
    const Relation **and_relations = get_relations_part(N_RELATIONS_EVEN_AND, &and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_EVEN, ONLY_EVEN);

    // All Relations
    relations_even = get_relations(or_relations, and_relations,
        N_RELATIONS_EVEN_OR, N_RELATIONS_EVEN_AND, rules, N_RULES_EVEN);

    return relations_even;
}

#endif
