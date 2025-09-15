# JSON Library

A lightweight, header-only JSON library written in C for creating, manipulating, and serializing JSON data structures.

## Features

- **Complete JSON Support**: Handles all JSON data types (objects, arrays, strings, numbers, booleans)
- **Memory Management**: Automatic memory allocation and cleanup with proper destructors
- **Dynamic Resizing**: Arrays and objects automatically resize as needed
- **Pretty Printing**: Formatted JSON output with proper indentation
- **File I/O**: Write JSON data directly to files
- **Header-Only**: No compilation required - just include the headers
- **Error Handling**: Comprehensive error checking and reporting

## Data Types

The library supports all standard JSON data types:

- **JSON Objects**: Key-value pairs with dynamic resizing
- **JSON Arrays**: Ordered collections of JSON nodes
- **JSON Strings**: Text values with automatic memory management
- **JSON Numbers**: Double-precision floating-point numbers
- **JSON Booleans**: True/false values

## Quick Start

### Basic Usage

```c
#include "json-library.h"

int main() {
    // Create a JSON object
    json_object_t* person = initialize_json_object();
    
    // Add string properties
    json_string_t* name = initialize_json_string("John Doe");
    json_node_t* name_node = initialize_json_node(JSON_STRING, name);
    json_object_append(person, "name", name_node);
    
    // Add number properties
    json_number_t* age = initialize_json_number(30.0);
    json_node_t* age_node = initialize_json_node(JSON_NUMBER, age);
    json_object_append(person, "age", age_node);
    
    // Add boolean properties
    json_boolean_t* active = initialize_json_boolean(1);
    json_node_t* active_node = initialize_json_node(JSON_BOOLEAN, active);
    json_object_append(person, "active", active_node);
    
    // Create the root node
    json_node_t* root = initialize_json_node(JSON_OBJECT, person);
    
    // Convert to string
    char* json_string = stringify_json_node(root);
    printf("%s\n", json_string);
    
    // Write to file
    write_json_to_file(root, "person.json");
    
    // Clean up
    free(json_string);
    destruct_json_node(root);
    
    return 0;
}
```

### Working with Arrays

```c
// Create a JSON array
json_array_t* hobbies = initialize_json_array();

// Add string elements
json_string_t* hobby1 = initialize_json_string("Reading");
json_node_t* hobby1_node = initialize_json_node(JSON_STRING, hobby1);
json_array_append(hobbies, hobby1_node);

json_string_t* hobby2 = initialize_json_string("Swimming");
json_node_t* hobby2_node = initialize_json_node(JSON_STRING, hobby2);
json_array_append(hobbies, hobby2_node);

// Create array node
json_node_t* hobbies_node = initialize_json_node(JSON_ARRAY, hobbies);

// Add to object
json_object_append(person, "hobbies", hobbies_node);
```

### Nested Objects

```c
// Create nested address object
json_object_t* address = initialize_json_object();

json_string_t* street = initialize_json_string("123 Main St");
json_node_t* street_node = initialize_json_node(JSON_STRING, street);
json_object_append(address, "street", street_node);

json_string_t* city = initialize_json_string("Anytown");
json_node_t* city_node = initialize_json_node(JSON_STRING, city);
json_object_append(address, "city", city_node);

json_node_t* address_node = initialize_json_node(JSON_OBJECT, address);
json_object_append(person, "address", address_node);
```

## API Reference

### Constructors

- `initialize_json_node(json_type_t type, void* pointer)` - Create a JSON node
- `initialize_json_object()` - Create an empty JSON object
- `initialize_json_array()` - Create an empty JSON array
- `initialize_json_string(char* value)` - Create a JSON string
- `initialize_json_number(double value)` - Create a JSON number
- `initialize_json_boolean(int value)` - Create a JSON boolean

### Object Methods

- `json_object_append(json_object_t* obj, char* key, json_node_t* value)` - Add key-value pair
- `json_object_resize(json_object_t* obj)` - Resize object capacity

### Array Methods

- `json_array_append(json_array_t* array, json_node_t* node)` - Add element to array
- `json_array_resize(json_array_t* array)` - Resize array capacity

### Serialization

- `stringify_json_node(json_node_t* node)` - Convert JSON to formatted string
- `write_json_to_file(json_node_t* node, char* file_path)` - Write JSON to file

### Memory Management

- `destruct_json_node(json_node_t* node)` - Free JSON node and all children
- `destruct_json_object(json_object_t* obj)` - Free JSON object
- `destruct_json_array(json_array_t* array)` - Free JSON array
- `destruct_json_string(json_string_t* str)` - Free JSON string
- `destruct_json_number(json_number_t* num)` - Free JSON number
- `destruct_json_boolean(json_boolean_t* bool)` - Free JSON boolean

## File Structure

```
json-library/
├── json-library.h              # Main header with serialization functions
├── json-library-types.h        # Data type definitions
├── json-library-constants.h    # Library constants
├── json-library-constructors.h # Object creation functions
├── json-library-methods.h      # Object manipulation methods
├── json-library-builder.h      # String builder for serialization
├── json-library-destructors.h  # Memory cleanup functions
└── README.md                   # This file
```

## Memory Management

The library handles all memory allocation automatically. When creating JSON structures:

1. **Allocation**: All constructors allocate memory and return pointers
2. **Resizing**: Arrays and objects automatically resize when capacity is exceeded
3. **Cleanup**: Use destructor functions to free memory properly
4. **String Duplication**: String values are automatically duplicated to prevent memory issues

**Important**: Always call the appropriate destructor function to prevent memory leaks.

## Error Handling

The library includes comprehensive error checking:

- **NULL Pointer Validation**: All functions check for NULL inputs
- **Memory Allocation Errors**: Proper error messages for allocation failures
- **Operation Status**: Functions return success/failure status codes
- **Error Messages**: Descriptive error messages printed to stderr

## Example Output

The library produces properly formatted JSON with indentation:

```json
{
    "name": "John Doe",
    "age": 30.00,
    "active": true,
    "hobbies": [
        "Reading",
        "Swimming"
    ],
    "address": {
        "street": "123 Main St",
        "city": "Anytown"
    }
}
```

## Requirements

- **C99 Compatible Compiler**: GCC, Clang, or MSVC
- **Standard C Library**: stdlib.h, string.h, stdio.h
- **Memory Management**: Manual memory management (malloc/free)