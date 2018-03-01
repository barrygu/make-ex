#define GET_3RD_ARG(a1, a2, a3, ...) a3

#define CONCAT(a, b) CONCAT_X(a, b)
#define CONCAT_X(a, b) a ## b

#define ENUM_TYPE_NAME(nam) e ##nam ##_type
#define ENUM_TYPE(nam, ...) ENUM_TYPE_X(ENUM_TYPE_NAME(nam), __VA_ARGS__)
#define ENUM_TYPE_X(typ, ...) typedef enum { __VA_ARGS__ } typ 

#define ENUM_NAMES_VAR(nam) e ##nam ##_Names
#define ENUM_NAMES(nam, ...) ENUM_NAMES_X(ENUM_NAMES_VAR(nam), __VA_ARGS__)
#define ENUM_NAMES_X(var, ...) char * var [] = { __VA_ARGS__ } 

#define ENUM_VALUES_VAR(nam)  e ##nam ##_Values
#define ENUM_VALUES(nam, ...) ENUM_VALUES_X(ENUM_TYPE_NAME(nam), ENUM_VALUES_VAR(nam), __VA_ARGS__)
#define ENUM_VALUES_X(typ, var, ...) typ var [] = { __VA_ARGS__ } 

#define GET_VAL_0(v, ...)
#define GET_VAL_1(v, ...) = v

#define FRUITS_ITEMS       \
    ENUM_ITEM(APPLE),      \
    ENUM_ITEM(MELON, -2),  \
    ENUM_ITEM(ORANGE, 10), \
    ENUM_ITEM(PEAR)

/**
 * Define type of the enumrator
 **/
#undef  ENUM_ITEM
#define ENUM_ITEM(nam, ...) nam CONCAT(GET_VAL_, \
    GET_3RD_ARG(, ## __VA_ARGS__, 1, 0))(__VA_ARGS__)

ENUM_TYPE(Fruits, FRUITS_ITEMS);

/**
 * Generate elements name list of the enumrator
 **/
#undef  ENUM_ITEM
#define ENUM_ITEM(nam, ...) #nam

ENUM_NAMES(Fruits, FRUITS_ITEMS);

/**
 * Generate elements value list of the enumrator
 **/
#undef  ENUM_ITEM
#define ENUM_ITEM(nam, ...) nam

#define NUM_ARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__}) / sizeof(int) - 1)

ENUM_VALUES(Fruits, FRUITS_ITEMS);

/**
 * Test code
 */
//#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("Count number of names list: %lu\n", 
        sizeof(ENUM_NAMES_VAR(Fruits))/sizeof(char *));
    printf("Count number of values list: %lu\n", 
        sizeof(ENUM_VALUES_VAR(Fruits))/sizeof(ENUM_TYPE_NAME(Fruits)));
    printf("Count number of enumrate items with variadic macro: %lu\n", 
        NUM_ARGS(FRUITS_ITEMS));
}
