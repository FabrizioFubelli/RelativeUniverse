// Set of Natural numbers (N)
#ifndef algebra_sets_negative_h
#define algebra_sets_negative_h

#include "../../utils/number.h"
#include "set_interface.h"
#include "integer.h"
#include "natural.h"



//---- Static constants
#define N_RULES_NEGATIVE 0
#define N_RELATIONS_NEGATIVE_AND 1
#define N_RELATIONS_NEGATIVE_OR 0



//---- Function declarations
const Relations *get_relations_negative(const Set *self);



//---- Static variables
static Relations *relations_negative = NULL;



//---- Main struct
const static Set Z_ = {
    .symbol = "Zˉ",
    .belongs = &belongs_to_set,
    .relations = &get_relations_negative,
};



//---- Function implementations

const Relations *get_relations_negative(const Set *self) {
    if (relations_negative != NULL) {
        return relations_negative;
    }

    // OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_NEGATIVE_OR);

    // AND relations
    const Relation and_1 = {
        .A = &Z,
        .B = &N,
        .type = DIFF
    };
    const Relation **and_relations = get_relations_part(N_RELATIONS_NEGATIVE_AND, &and_1);

    // Rules
    unsigned int *rules = get_rules(N_RULES_NEGATIVE);

    // All Relations
    relations_negative = get_relations(or_relations, and_relations,
        N_RELATIONS_NEGATIVE_OR, N_RELATIONS_NEGATIVE_AND, rules, N_RULES_NEGATIVE);

    return relations_negative;
}

#endif
