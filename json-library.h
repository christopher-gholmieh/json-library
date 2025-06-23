// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_H__
#define __JSON_LIBRARY_H__

// Headers:
#include "json-library-constructors.h"
#include "json-library-constants.h"
#include "json-library-builder.h"
#include "json-library-types.h"

// Prototypes:
static void stringify_json_node_internal(json_node_t* json_node, string_builder_t* string_builder, int indentation_level);
char* stringify_json_node(json_node_t* json_node);

int write_json_to_file(json_node_t* json_node, char* file_path);

// Definition:
static void stringify_json_node_internal(json_node_t* json_node, string_builder_t* string_builder, int indentation_level) {
    switch (json_node->json_type) {
        case JSON_BOOLEAN: {
            // Variables (Assignment):
            // Boolean:
            json_boolean_t* json_boolean = (json_boolean_t*) json_node->pointer;
            
            // Logic:
            string_builder_append_data(string_builder, json_boolean->value ? "true" : "false");
            break;
        }

        case JSON_OBJECT: {
            // Variables (Assignment):
            // Object:
            json_object_t* json_object = (json_object_t*) json_node->pointer;

            string_builder_append_data(string_builder, "{\n");

            for (size_t iterator = 0; iterator < json_object->length; iterator++) {
                string_builder_append_indent(string_builder, indentation_level + 1);
                string_builder_append_data(string_builder, "\"");
                string_builder_append_data(string_builder, json_object->keys[iterator]);
                string_builder_append_data(string_builder, "\": ");

                stringify_json_node_internal(json_object->values[iterator], string_builder, indentation_level + 1);

                if (iterator != json_object->length - 1) {
                    string_builder_append_data(string_builder, ",");
                }

                string_builder_append_data(string_builder ,"\n");
            }

            string_builder_append_indent(string_builder, indentation_level);
            string_builder_append_data(string_builder, "}");

            break;
        }

        case JSON_NUMBER: {
            // Variables (Assignment):
            // Number:
            json_number_t* json_number = (json_number_t*) json_node->pointer;

            // Buffer:
            char* buffer = (char*) malloc(64);
            
            if (buffer == NULL) {
                // Message:
                fprintf(stderr, "[!] Unable to allocate memory for buffer.\n");

                // Memory:
                destruct_string_builder(string_builder);

                // Logic:
                return;
            }

            // Logic:
            snprintf(buffer, 64, "%.2f", json_number->value);
            string_builder_append_data(string_builder, buffer);

            // Memory:
            free(buffer);

            // Logic:
            break;
        }

        case JSON_STRING: {
            // Variables (Assignment):
            // String:
            json_string_t* json_string = (json_string_t*) json_node->pointer;

            // Logic:
            string_builder_append_data(string_builder, "\"");
            string_builder_append_data(string_builder, json_string->value);
            string_builder_append_data(string_builder, "\"");

            break;
        }

        case JSON_ARRAY: {
            // Variables (Assignment):
            // Array:
            json_array_t* json_array = (json_array_t*) json_node->pointer;

            // Logic:
            string_builder_append_data(string_builder, "[\n");

            for (size_t iterator = 0; iterator < json_array->length; iterator++) {
                // Logic:
                string_builder_append_indent(string_builder, indentation_level + 1);
                stringify_json_node_internal(json_array->values[iterator], string_builder, indentation_level + 1);

                if (iterator != json_array->length - 1) {
                    string_builder_append_data(string_builder, ", ");
                }
            }

            string_builder_append_indent(string_builder, indentation_level);
            string_builder_append_data(string_builder, "]");

            break;
        }
    }
}

char* stringify_json_node(json_node_t* json_node) {
    // Validation:
    if (json_node == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform stringify operation on NULL JSON node.\n");

        // Logic:
        return NULL;
    }

    // Variables (Assignment);
    // Builder:
    string_builder_t* string_builder = initialize_string_builder();
    
    if (string_builder == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to create string builder.\n");

        // Logic:
        return NULL;
    }

    // Logic:
    stringify_json_node_internal(json_node, string_builder, 0);

    // Variables (Assignment):
    // Data:
    char* finalized_data = string_builder_finalize(string_builder);

    if (finalized_data == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to finalize JSON data.\n");

        // Memory:
        destruct_string_builder(string_builder);

        // Logic:
        return NULL;
    }

    // Logic:
    return finalized_data;
}

int write_json_to_file(json_node_t* json_node, char* file_path) {
    // Variables (Assignment):
    // File:
    FILE* file_pointer = fopen(file_path, "a");

    // Representation:
    char* representation = stringify_json_node(json_node);

    if (representation == NULL) {
        // Message:
        fprintf(stderr, "[!] Invalid JSON detected.\n");

        // Memory:
        fclose(file_pointer);

        // Logic:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    fprintf(file_pointer, representation);

    // Memory:
    fclose(file_pointer);
}

// Guard:
#endif /** __JSON_LIBRARY_H__ */