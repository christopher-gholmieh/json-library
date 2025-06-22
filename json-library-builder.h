// Written by: Christopher Gholmieh
// Guards:
#ifndef __JSON_LIBRARY_BUILDER_H__
#define __JSON_LIBRARY_BUILDER_H__

// Headers:
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// Structures:
typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Length: */
    size_t length;

    /* Data: */
    char* data;
} string_builder_t;

// Prototypes:
string_builder_t* initialize_string_builder(void);

void string_builder_append_data(string_builder_t* string_builder, const char* data);
void string_builder_append_indent(string_builder_t* string_builder, int indent_level);
char* string_builder_finalize(string_builder_t* string_builder);

void destruct_string_builder(string_builder_t* string_builder);

// Definition:
string_builder_t* initialize_string_builder(void) {
    // Variables (Assignment):
    // Builder:
    string_builder_t* string_builder = (string_builder_t*) malloc(sizeof(string_builder_t));

    if (string_builder == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for string builder.\n");

        // Logic:
        return NULL;
    }

    // Capacity:
    string_builder->capacity = 512;

    // Length:
    string_builder->length = 0;

    // Data:
    string_builder->data = (char*) malloc(string_builder->capacity);

    if (string_builder->data == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for string builder's data.\n");

        // Memory:
        free(string_builder);

        // Logic:
        return NULL;
    }

    memset(string_builder->data, 0, string_builder->capacity);
    string_builder->data[string_builder->length] = '\0';

    // Logic:
    return string_builder;
}

void string_builder_append_data(string_builder_t* string_builder, const char* data) {
    // Validation:
    if (string_builder == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform append data operation on NULL string builder.\n");

        // Logic:
        return;
    }
    
    // Variables (Assignment):
    // Length:
    size_t length = strlen(data);

    // Logic:
    while (string_builder->capacity <= string_builder->length + length) {
        // Capacity:
        string_builder->capacity = string_builder->capacity * 2;
    }

    // Variables (Assignment):
    // Data:
    char* updated_data = (char*) realloc(string_builder->data, string_builder->capacity);

    if (updated_data == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform resize operation on string builder data.\n");

        // Logic:
        return;
    }

    string_builder->data = updated_data;

    // Logic:
    memcpy(string_builder->data + string_builder->length, data, length);

    string_builder->length = string_builder->length + length;
    string_builder->data[string_builder->length] = '\0';
}

void string_builder_append_indent(string_builder_t* string_builder, int indent_level) {
    for (int iterator = 0; iterator < indent_level; iterator++) {
        string_builder_append_data(string_builder, "    ");
    }
}

char* string_builder_finalize(string_builder_t* string_builder) {
    // Validation:
    if (string_builder == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to perform finalize operation on NULL string builder.\n");

        // Logic:
        return NULL;
    }

    // Variables (Assignment):
    // Finalized:
    char* finalized_data = strdup(string_builder->data);

    if (finalized_data == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to duplicate string builder's data.\n");

        // Logic:
        return NULL;
    }

    // Logic:
    destruct_string_builder(string_builder);

    return finalized_data;
}

void destruct_string_builder(string_builder_t* string_builder) {
    // Validation:
    if (string_builder == NULL) {
        // Message:
        fprintf(stderr, "[!] Can't perform destruct operation on NULL string builder.\n");

        // Logic:
        return;
    }

    // Logic:
    if (string_builder->data != NULL) {
        free(string_builder->data);
    }

    free(string_builder);
}

// Guard:
#endif /** __JSON_LIBRARY_BUILDER_H__ */