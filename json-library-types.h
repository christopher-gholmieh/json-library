// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_TYPES_H__
#define __JSON_LIBRARY_TYPES_H__

// Headers:
#include <stdlib.h>

// Enumerations:
typedef enum {
    /* Boolean: */
    JSON_BOOLEAN,

    /* Object: */
    JSON_OBJECT,

    /* Number: */
    JSON_NUMBER,

    /* String: */
    JSON_STRING,

    /* Array: */
    JSON_ARRAY,
} json_type_t;

// Structures:
typedef struct {
    /* Type: */
    json_type_t json_type;

    /* Pointer: */
    void* pointer;
} json_node_t;

typedef struct {
    /* Value: */
    int value;
} json_boolean_t;

typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Length: */
    size_t length;

    /* Values: */
    json_node_t** values;

    /* Keys: */
    char** keys;
} json_object_t;

typedef struct {
    /* Value: */
    double value;
} json_number_t;

typedef struct {
    /* Value: */
    char* value;
} json_string_t;

typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Length: */
    size_t length;

    /* Values: */
    json_node_t** values;
} json_array_t;

// Guard:
#endif /** __JSON_LIBRARY_TYPES_H__ */