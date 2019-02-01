// Universe Set (U),

#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/number.h"
#include "set_interface.h"




//---- Static constants
#define N_RULES_UNIVERSE 0
#define N_RELATIONS_UNIVERSE_AND 0
#define N_RELATIONS_UNIVERSE_OR 0



//---- Function declarations
const bool belongs_universe(const Number x);
const Relations *get_relations_universe();



//---- Static variables
static Relations *relations_universe = NULL;



//---- Main struct
const static Set U = {
    .symbol = 'U',
    .belongs = &belongs_universe,
    .relations = &get_relations_universe,
};



//---- Function implementations

const bool belongs_universe(const Number x) {
    return belongs_to_set(x, U);
}

const Relations *get_relations_universe() {
    if (relations_universe != NULL) {
        return relations_universe;
    }

    //-- OR relations
    Relation *or_relations = get_relations_part(N_RELATIONS_UNIVERSE_OR);

    // AND relations
    Relation *and_relations = get_relations_part(N_RELATIONS_UNIVERSE_AND);

    // Rules
    unsigned int *rules = get_rules(N_RULES_UNIVERSE);

    // All Relations
    relations_universe = get_relations(or_relations, and_relations,
        N_RELATIONS_UNIVERSE_OR, N_RELATIONS_UNIVERSE_AND, rules, N_RULES_UNIVERSE);

    return relations_universe;
}

#endif
