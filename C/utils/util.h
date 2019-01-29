#ifndef utils_util_h
#define utils_util_h

typedef enum {
    t_other=0,
    t_bool=1,
    t_unsigned_char=2, t_char=3, t_signed_char=4,
    t_short_int=5, t_unsigned_short_int=6, t_int=7, t_unsigned_int=8,
    t_long_int=9, t_unsigned_long_int=10, t_long_long_int=11, t_unsigned_long_long_int=12,
    t_float=13,
    t_double=14, t_long_double=15,
    t_pointer_to_char=16, t_pointer_to_void=17, t_pointer_to_int=18,
    t_set=19
} Type;

#include "../algebra/sets/set_interface.h"

#define typename(x) _Generic((x),        /* Get the name of a type */              \
        _Bool: t_bool,                   unsigned char: t_unsigned_char,          \
         char: t_char,                     signed char: t_signed_char,            \
    short int: t_short_int,         unsigned short int: t_unsigned_short_int,     \
          int: t_int,                     unsigned int: t_unsigned_int,           \
     long int: t_long_int,           unsigned long int: t_unsigned_long_int,      \
long long int: t_long_long_int, unsigned long long int: t_unsigned_long_long_int, \
         float: t_float,                          double: t_double,                 \
  long double: t_long_double,                   char *: t_pointer_to_char,        \
       void *: t_pointer_to_void,                int *: t_pointer_to_int,         \
          Set: t_set,                          default: t_other)

static char *str_typename(Type t) {
    switch (t) {
        case t_bool:
            return "bool";
        case t_unsigned_char:
            return "unsigned char";
        case t_char:
            return "char";
        case t_signed_char:
            return "signed char";

        case t_short_int:
            return "short int";
        case t_unsigned_short_int:
            return "unsigned short int";
        case t_int:
            return "int";
        case t_unsigned_int:
            return "unsigned int";

        case t_long_int:
            return "long int";
        case t_unsigned_long_int:
            return "unsigned long int";
        case t_long_long_int:
            return "long long int";
        case t_unsigned_long_long_int:
            return "unsigned long long int";

        case t_float:
            return "float";
        case t_double:
            return "double";
        case t_long_double:
            return "long double";
        case t_pointer_to_char:
            return "char *";

        case t_pointer_to_void:
            return "void *";
        case t_pointer_to_int:
            return "int *";

        case t_set:
            return "Set";

        default:
            return "other";
    }
}

#endif
