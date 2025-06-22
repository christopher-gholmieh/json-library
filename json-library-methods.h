// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_METHODS_H__
#define __JSON_LIBRARY_METHODS_H__

// Headers:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "json-library-constants.h"
#include "json-library-types.h"

// Prototypes:
int json_object_resize(json_object_t* json_object);
int json_object_append(json_object_t* json_object, char* key, json_node_t* value);

int json_array_resize(json_array_t* json_array);
int json_array_append(json_array_t* json_array, json_node_t* json_node);

// Definition:
int json_object_resize(json_object_t* json_object) {
    // Validation:
    if (json_object == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform resize operation on NULL JSON object.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = json_object->capacity * 2;

    // Values:
    json_node_t** updated_values = (json_node_t**) realloc(json_object->values, sizeof(json_node_t*) * updated_capacity);

    if (updated_values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to reallocate memory for JSON object's updated values.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Keys:
    char** updated_keys = (char**) realloc(json_object->keys, sizeof(char*) * updated_capacity);

    if (updated_keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to reallocate memory for JSON object's updated keys.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    json_object->capacity = updated_capacity;
    json_object->values = updated_values;
    json_object->keys = updated_keys;
    
    return SUCCESSFUL_OPERATION;
}

int json_object_append(json_object_t* json_object, char* key, json_node_t* value) {
    // Validation:
    if (json_object->length >= json_object->capacity) {
        if (json_object_resize(json_object) == UNSUCCESSFUL_OPERATION) {
            // Message:
            fprintf(stderr, "[!] Unable to perform resize operation on JSON object.\n");

            // Logic:
            return UNSUCCESSFUL_OPERATION;
        }
    }

    if (key == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform append operation on JSON object with NULL key.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    if (value == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform append operation on JSON object with NULL JSON node.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Variables (Assignment):
    // Key:
    char* duplicated_key = strdup(key);

    if (duplicated_key == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to duplicate key.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    json_object->values[json_object->length] = value;
    json_object->keys[json_object->length] = duplicated_key;
    json_object->length++;

    return SUCCESSFUL_OPERATION;
}

int json_array_resize(json_array_t* json_array) {
    // Validation:
    if (json_array == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform resize operation on NULL JSON array.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = json_array->capacity * 2;

    // Values:
    json_node_t** updated_values = (json_node_t**) realloc(json_array->values, sizeof(json_node_t*) * updated_capacity);

    if (updated_values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to reallocate memory for JSON array's updated values.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    json_array->capacity = updated_capacity;
    json_array->values = updated_values;

    return SUCCESSFUL_OPERATION;
}

int json_array_append(json_array_t* json_array, json_node_t* json_node) {
    // Validation:
    if (json_array->length >= json_array->capacity) {
        if (json_array_resize(json_array) == UNSUCCESSFUL_OPERATION) {
            // Message:
            fprintf(stderr, "[!] Unable to perform resize operation on JSON array.\n");

            // Logic:
            return UNSUCCESSFUL_OPERATION;
        }
    }

    if (json_node == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform append operation on JSON array with NULL JSON node.\n");

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    json_array->values[json_array->length] = json_node;
    json_array->length++;

    return SUCCESSFUL_OPERATION;
};

// Guard:
#endif /** __JSON_LIBRARY_METHODS_H__ */