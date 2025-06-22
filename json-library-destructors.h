// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_DESTRUCTORS_H__
#define __JSON_LIBRARY_DESTRUCTORS_H__

// Headers:
#include <stdlib.h>
#include <stdio.h>

#include "json-library-types.h"

// Prototypes:
void destruct_json_node(json_node_t* json_node);
void destruct_json_boolean(json_boolean_t* json_boolean);

void destruct_json_object(json_object_t* json_object);
void destruct_json_number(json_number_t* json_number);

void destruct_json_string(json_string_t* json_string);
void destruct_json_array(json_array_t* json_array);

// Definition:
void destruct_json_node(json_node_t* json_node) {
    // Validation:
    if (json_node == NULL) {
        // Message:
        fprintf(stderr, "[!] Can't perform destruct operation on NULL JSON node.\n");

        // Logic:
        return;
    }

    if (json_node->pointer != NULL) {
        switch (json_node->json_type) {
            case JSON_BOOLEAN:
                {
                    destruct_json_boolean((json_boolean_t*) json_node->pointer);
                }

                break;

            case JSON_OBJECT:
                {
                    destruct_json_object((json_object_t*) json_node->pointer);
                }

                break;

            case JSON_NUMBER:
                {
                    destruct_json_number((json_number_t*) json_node->pointer);
                }

                break;

            case JSON_STRING:
                {
                    destruct_json_string((json_string_t*) json_node->pointer);
                }

                break;

            case JSON_ARRAY:
                {
                    destruct_json_array((json_array_t*) json_node->pointer);
                }

                break;
        }
    }

    free(json_node);
}

void destruct_json_boolean(json_boolean_t* json_boolean) {
    free(json_boolean);
}

void destruct_json_object(json_object_t* json_object) {
    for (size_t iterator = 0; iterator < json_object->length; iterator++) {
        destruct_json_node(json_object->values[iterator]);

        free(json_object->keys[iterator]);
    }

    free(json_object->values);
    free(json_object->keys);
}

void destruct_json_number(json_number_t* json_number) {
    free(json_number);
}

void destruct_json_string(json_string_t* json_string) {
    free(json_string->value);
    free(json_string);
}

void destruct_json_array(json_array_t* json_array) {
    for (size_t iterator = 0; iterator < json_array->length; iterator++) {
        destruct_json_node(json_array->values[iterator]);
    }

    free(json_array->values);
    free(json_array);
}

// Guard:
#endif /** __JSON_LIBRARY_DESTRUCTORS_H__ */