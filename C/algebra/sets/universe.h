// Universe Set (U)&U,

#ifndef algebra_sets_universe_h
#define algebra_sets_universe_h

#include "../../utils/util.h"
#include "set_interface.h"
#include "set_relations.h"
#include "set_rules.h"

const bool belongs_universe(const Number x);
const unsigned int *rules_universe();

static const Set U = {
    .symbol = 'U',
    .belongs = &belongs_universe,
    .relations_length = 0,
    .relations = {
        {
            .A = NULL,
            .B = NULL,
            .type = AND,
            .rules_tot = 0,
            .get_rule_numbers = rules_universe
        }
    }
};

const bool belongs_universe(const Number x) {
    return belongs_to_set(x, U);
}

const unsigned int *rules_universe() {
    return NULL;
}

#endif
