// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_CONSTRUCTORS_H__
#define __JSON_LIBRARY_CONSTRUCTORS_H__

// Headers:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "json-library-types.h"

// Prototypes:
json_node_t* initialize_json_node(json_type_t json_type, void* pointer);
json_boolean_t* initialize_json_boolean(int value);

json_object_t* initialize_json_object(void);
json_number_t* initialize_json_number(double value);

json_string_t* initialize_json_string(char* value);
json_array_t* initialize_json_array(void);

// Definition:
json_node_t* initialize_json_node(json_type_t json_type, void* pointer) {
    // Variables (Assignment):
    // Node:
    json_node_t* json_node = (json_node_t*) malloc(sizeof(json_node_t));

    if (json_node == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON node.\n");

        // Logic:
        return NULL;
    }

    // Type:
    json_node->json_type = json_type;

    // Pointer:
    json_node->pointer = pointer;

    // Logic:
    return json_node;
}

json_boolean_t* initialize_json_boolean(int value) {
    // Variables (Assignment):
    // Boolean:
    json_boolean_t* json_boolean = (json_boolean_t*) malloc(sizeof(json_boolean_t));

    if (json_boolean == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON boolean.\n");

        // Logic:
        return NULL;
    }

    // Value:
    json_boolean->value = value;

    // Logic:
    return json_boolean;
}

json_object_t* initialize_json_object(void) {
    // Variables (Assignment):
    // Object:
    json_object_t* json_object = (json_object_t*) malloc(sizeof(json_object_t));

    if (json_object == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON object.\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    json_object->capacity = 4;

    // Length:
    json_object->length = 0;

    // Values:
    json_node_t** values = (json_node_t**) malloc(sizeof(json_node_t*) * json_object->capacity);

    if (values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON object's values.\n");

        // Memory:
        free(json_object);

        // Logic:
        return NULL;
    }

    // Keys:
    char** keys = (char**) malloc(sizeof(char*) * json_object->capacity);

    if (keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON object's keys.\n");

        // Memory:
        free(json_object);
        free(values);

        // Logic:
        return NULL;
    }

    // Memory:
    memset(values, 0, sizeof(json_node_t*) * json_object->capacity);
    memset(keys, 0, sizeof(char*) * json_object->capacity);

    // Logic:
    json_object->values = values;
    json_object->keys = keys;

    return json_object;
}

json_number_t* initialize_json_number(double value) {
    // Variables (Assignment):
    // Number:
    json_number_t* json_number = (json_number_t*) malloc(sizeof(json_number_t));

    if (json_number == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON number.\n");

        // Logic:
        return NULL;
    }

    // Value:
    json_number->value = value;

    // Logic:
    return json_number;
}

json_string_t* initialize_json_string(char* value) {
    // Variables (Assignment):
    // String:
    json_string_t* json_string = (json_string_t*) malloc(sizeof(json_string_t));

    if (json_string == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON string.\n");

        // Logic:
        return NULL;
    }

    // Value:
    char* duplicated_value = strdup(value);
    
    if (duplicated_value == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to duplicate string for JSON string.\n");

        // Memory:
        free(json_string);

        // Logic:
        return NULL;
    }

    // Logic:
    json_string->value = duplicated_value;

    return json_string;
}

json_array_t* initialize_json_array(void) {
    // Variables (Assignment):
    // Array:
    json_array_t* json_array = (json_array_t*) malloc(sizeof(json_array_t));

    if (json_array == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON array.\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    json_array->capacity = 4;

    // Length:
    json_array->length = 0;

    // Values:
    json_node_t** values = (json_node_t**) malloc(sizeof(json_node_t*) * json_array->capacity);

    if (values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for JSON array's values.\n");

        // Memory:
        free(json_array);

        // Logic:
        return NULL;
    }
    
    // Memory:
    memset(values, 0, sizeof(json_node_t*) * json_array->capacity);

    // Logic:
    json_array->values = values;

    return json_array;
}

// Guard:
#endif /** __JSON_LIBRARY_CONSTRUCTORS_H__ */