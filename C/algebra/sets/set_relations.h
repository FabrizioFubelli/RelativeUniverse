#ifndef algebra_sets_set_relations_h
#define algebra_sets_set_relations_h

#include <stdbool.h>

typedef unsigned int (*rules_fun)();
typedef struct relation Relation;
typedef struct relations Relations;
typedef struct relation_map RelationMap;
typedef enum relation_type {
    AND=1, OR, DIFF
} RelationType;
static const char *type_to_string(RelationType type);
static const char *type_to_symbol(RelationType type);

struct relation_map {
    const char *key;
    const Relations *value;
};

#include "../../utils/number.h"
#include "set_interface.h"

struct relation
{
    const Set *A;
    const Set *B;
    const unsigned short int type;
};

struct relations
{
    const unsigned int rules_length;
    const unsigned int *rules_index;
    const unsigned int and_length;
    const unsigned int or_length;
    const Relation** and;
    const Relation** or;
};

static const char *type_to_symbol(RelationType type) {
    switch (type) {
        case AND:
            return "∩";
        case OR:
            return "∪";
        case DIFF:
            return "-";
        default:
            return "?";
    }
}

static const char *type_to_string(RelationType type) {
    switch (type) {
        case AND:
            return "AND";
        case OR:
            return "OR";
        case DIFF:
            return "DIFF";
        default:
            return "UNKNOWN";
    }
}

static void print_relation(const Relation *relation, const unsigned int left) {
    unsigned int i, s;
    char *space = (char *) malloc(left*sizeof(char)+1);
    for (s=0; s<left; s++) {
        space[s] = ' ';
    }
    space[s] = '\0';

    printf("%s|-- A ", space);
    print_set(relation->A, left+6);
    printf("%s|-- B ", space);

    print_set(relation->B, left+6);
    free(space);
}

static void print_relations(const Relations *relations, const unsigned int left) {
    unsigned int i, s;
    char *space = (char *) malloc(left*sizeof(char)+1);
    for (s=0; s<left; s++) {
        space[s] = ' ';
    }
    space[s] = '\0';
    printf("%s|--Relations\n", space);
    printf("%s    |\n", space);
    printf("%s    |--rules_length: %u\n", space, relations->rules_length);
    if (relations->rules_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--rules_index\n", space);
        for (i=0; i<relations->rules_length; i++) {
            bool last = i == relations->rules_length-1;
            printf("%s    %c      |\n", space, last ? ' ' : '|');
            const unsigned int rule_index = relations->rules_index[i];
            char *rule_name =  rule_to_string(rule_index);
            printf("%s    %c      |-- %u. Rule: %s\n", space, last ? ' ' : '|', i+1, rule_name);
            free(rule_name);
        }
    }
    printf("%s    |\n", space);
    printf("%s    |--and_length: %u\n", space, relations->and_length);
    if (relations->and_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--and (list)\n", space);
        const Relation **ands = relations->and;
        for (i=0; i<relations->and_length; i++) {
            const Relation *and = ands[i];
            const bool last = i == relations->and_length-1;
            printf("%s    %c  |\n", space, last ? ' ' : '|');
            printf("%s    %c  |-- %u. Relation (type: %s)\n", space, last ? ' ' : '|', i+1, type_to_string(and->type));
            printf("%s    %c            |\n", space, last ? ' ' : '|');
            print_relation(and, left+17);
        }
    }
    printf("%s    |\n", space);
    printf("%s    |--or_length: %u\n", space, relations->or_length);
    if (relations->or_length > 0) {
        printf("%s    |\n", space);
        printf("%s    |--or (list)\n", space);
        for (i=0; i<relations->or_length; i++) {
            const bool last = i == relations->or_length-1;
            const Relation *or = relations->or[i];
            printf("%s    %c  |\n", space, last ? ' ' : '|');
            printf("%s    %c  |-- %u. Relation (type: %s)\n", space, last ? ' ' : '|', i+1, type_to_string(or->type));
            printf("%s    %c            |\n", space, last ? ' ' : '|');
            print_relation(or, left+17);
        }
    }
    printf("\n");
    free(space);
}

#endif
