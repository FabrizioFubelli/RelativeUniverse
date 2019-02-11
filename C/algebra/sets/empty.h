// Empty Set (Ø)

#ifndef algebra_sets_empty_h
#define algebra_sets_empty_h

#include "../../utils/number.h"
#include "set_interface.h"




//---- Static constants
#define N_RULES_EMPTY 1
#define N_RELATIONS_EMPTY_AND 0
#define N_RELATIONS_EMPTY_OR 0



//---- Function declarations
const bool belongs_empty(const Number x);
const Relations *get_relations_empty();



//---- Static variables
static Relations *relations_empty = NULL;



//---- Main struct
const static Set E = {
    .symbol = "E",
    .belongs = &belongs_empty,
    .relations = &get_relations_empty,
};



//---- Function implementations

const bool belongs_empty(const Number x) {
    return belongs_to_set(x, &E);
}

const Relations *get_relations_empty() {
    if (relations_empty != NULL) {
        return relations_empty;
    }

    //-- OR relations
    const Relation **or_relations = get_relations_part(N_RELATIONS_EMPTY_OR);

    // AND relations
    const Relation **and_relations = get_relations_part(N_RELATIONS_EMPTY_AND);

    // Rules
    unsigned int *rules = get_rules(N_RULES_EMPTY, EMPTY);

    // All Relations
    relations_empty = get_relations(or_relations, and_relations,
        N_RELATIONS_EMPTY_OR, N_RELATIONS_EMPTY_AND, rules, N_RULES_EMPTY);

    return relations_empty;
}

#endif
