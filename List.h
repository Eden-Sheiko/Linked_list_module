//
// Created by edens on 28/09/2024.
//

#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct list_module_s list_module_t;

//todo:
typedef struct list_module_config_s {
    bool thread_safe;
}list_module_config_t;

typedef enum list_module_error_e {
    LIST_MODULE_ERROR_OK = 0,
    LIST_MODULE_EMPTY,
    LIST_MODULE_ALLOC_ERROR,
    LIST_MODULE_NO_MATCH,
    LIST_MODULE_NULL_ERROR,

}list_module_error_t;

list_module_t* init_list();

list_module_error_t print_list(list_module_t* list);

list_module_error_t insert_node_end(list_module_t* list, void* val);

bool is_list_empty(list_module_t* list);

list_module_error_t insert_node_begin(list_module_t* list, void* val);

list_module_error_t insert_node_middle(list_module_t* list, void* val);

list_module_error_t delete_node(list_module_t* list);

list_module_error_t delete_node_end(list_module_t* list);

list_module_error_t delete_node_begin(list_module_t* list);

list_module_error_t find_loop(list_module_t* list);

list_module_t* flip_list(list_module_t* list);

list_module_error_t print_list_rec(list_module_t* list);

list_module_t* flip_list_rec(list_module_t* list);

//remove loop

list_module_error_t destroy_list(list_module_t* list);

size_t list_size(list_module_t* list);




#endif //LIST_H