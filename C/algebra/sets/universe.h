// Universe Set (U)&U,

#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "set_relations.h"
#include "set_rules.h"

static const bool belongs_universe(const Number x);
static const unsigned int *rules_universe();
static const Relation *relations_universe();

static const Set U = {
    .symbol = 'U',
    .belongs = &belongs_universe,
    //.relations_length = 0,
    //.relations = &relations_universe
};

static const bool belongs_universe(const Number x) {
    //return belongs_to_set(x, U);
}

static const Relation *relations_universe() {
    /*const Relation relations[0];
    return relations;*/
}

static const unsigned int *rules_universe() {
    return NULL;
}



#endif
