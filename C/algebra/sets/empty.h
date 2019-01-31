// Empty Set (Ø)
#ifndef algebra_sets_empty_h
#define algebra_sets_empty_h

#include "../../utils/util.h"
#include "set_interface.h"

static const bool belongs_empty(const Number x);
static const unsigned int *rules_empty();
static const Relation *relations_empty();

static const Set E = {
    .symbol = 'E',
    //.relations_length = 1,
    .belongs = &belongs_empty,
    //.relations = &relations_empty
};

static const bool belongs_empty(const Number x) {
    return belongs_to_set(x, E);
}

static const Relation *relations_empty() {
    /*const Relation r = {
        .A = NULL,
        .B = NULL,
        .type = AND,
        .rules_length = 1,
        .rules_index = &rules_empty
    };
    const Relation relations[] = { r };
    return relations;*/
}

static const unsigned int *rules_empty() {
    /*const unsigned int rule_numbers[] = { EMPTY };
    return rule_numbers;*/
    /*
    void *p = malloc(sizeof(Rule) * 1);
    return (Rule *) memcpy(p, EMPTY, sizeof(EMPTY));*/
}

#endif
