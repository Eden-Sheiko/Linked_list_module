//
// Created by edens on 28/09/2024.
//
#include "List.h"

struct list_module_s {
    void* data;
    struct list_module_s* next;
};

list_module_t* init_list() {
    list_module_t* list = calloc(1,sizeof(list_module_t));
    if (list == NULL) {
        return NULL;
    }
    /* dummy node */
    list->data = (uint16_t*)0xFFFF;
    list->next = NULL;
    return list;
}
bool is_list_empty(list_module_t* list) {
    if (list->next == NULL) {
        return true;
    }
    return false;
}
list_module_t* init_list_no_dummy(void* val) {
    list_module_t* list = calloc(1,sizeof(list_module_t));
    if (list == NULL) {
        return NULL;
    }
    list->data = val;
    list->next = NULL;
    return list;
}


list_module_error_t print_list(list_module_t* list) {
    list_module_t* p_list = list;
    uint8_t is_first_loop = 1;
    if (is_list_empty(p_list)) {
        return LIST_MODULE_EMPTY;
    }
    while (p_list) {
        if(is_first_loop) {
            is_first_loop = 0;
            p_list = p_list->next;
        }
        printf("%d -> ",p_list->data);
        p_list = p_list->next;
    }
    printf("NULL \n");
    return LIST_MODULE_ERROR_OK;
}

size_t list_size(list_module_t* list) {
    list_module_t* p_list = list;
    size_t counter = 0;
    if (is_list_empty(p_list)) {
        return 0;
    }
    while (!is_list_empty(p_list)) {
        ++counter;
        p_list = p_list->next;
    }
    return counter;
}
list_module_error_t insert_node_begin(list_module_t* list, void* val) {
    list_module_t* p_list = list;
    list_module_t* new_node = calloc(1,sizeof(list_module_t));
    if (new_node == NULL) {
        return LIST_MODULE_ALLOC_ERROR;
    }
    new_node->data = val;
    new_node->next = p_list->next;
    p_list->next = new_node;
    return LIST_MODULE_ERROR_OK;
}
list_module_error_t insert_node_end(list_module_t* list, void* val) {
    list_module_t* p_list = list;
    list_module_t* new_node = calloc(1,sizeof(list_module_t));
    if (new_node == NULL) {
        return LIST_MODULE_ALLOC_ERROR;
    }
    new_node->data = val;
    while (p_list) {
        if (p_list->next == NULL) {
            new_node->next = NULL;
            p_list->next = new_node;
            break;
        }
        p_list = p_list->next;
    }
    return LIST_MODULE_ERROR_OK;
}
//todo: fix bug
list_module_error_t insert_node_middle(list_module_t* list, void* val) {
    list_module_t* p_list = list;
    list_module_t* new_node = calloc(1,sizeof(list_module_t));
    if (new_node == NULL) {
        return LIST_MODULE_ALLOC_ERROR;
    }
    new_node->data = val;
    size_t size = list_size(p_list);
    for (int i = 0;i < size/2; ++i) {
        p_list = p_list->next;
    }
    new_node->next=p_list->next;
    p_list->next = new_node;
    return LIST_MODULE_ERROR_OK;
}
list_module_error_t destroy_list(list_module_t* list) {
    while (list) {
        list_module_t* p_list = list->next;
        free(list);
        list = p_list;
    }
    return LIST_MODULE_ERROR_OK;
}
list_module_error_t delete_node(list_module_t* list) {
    list_module_t* p_list = list;
    if (p_list == NULL) {
        return LIST_MODULE_NULL_ERROR;
    }
    if (p_list->next == NULL) {
        free(list);
        return LIST_MODULE_ERROR_OK;
    }
    /* take care of dummy head 0XFFFF */
    if (p_list->data == (uint16_t*)0xFFFF && list_size(p_list) >= 2) {
        list_module_t* tmp_list = list->next;
        p_list=p_list->next->next;
        list->next = p_list;
        free(tmp_list);
        return LIST_MODULE_ERROR_OK;
    }
    /* add case 1 size node , and return empty list with dummy */
    p_list = p_list->next;
    list->next = NULL;
    free(p_list);
    return LIST_MODULE_ERROR_OK;
}
list_module_error_t find_loop(list_module_t* list) {
    list_module_t* slow_ptr = list;
    list_module_t* fast_ptr = list;
    while (slow_ptr != NULL && fast_ptr->next != NULL) {
        if (slow_ptr == fast_ptr) {
            return LIST_MODULE_ERROR_OK;
        }
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    }
    return LIST_MODULE_NO_MATCH;
}
list_module_error_t delete_node_end(list_module_t* list){
    list_module_t* p_list = list;
    list_module_t* p_list_next = list;

    if (p_list == NULL){
        return LIST_MODULE_NULL_ERROR;
    }
    if (p_list->next == NULL){
        return LIST_MODULE_EMPTY;
    }
    if (list_size(p_list) == 1){
        p_list = p_list->next;
        free(p_list);
        list->next = NULL;
        return LIST_MODULE_ERROR_OK;
    }
    while (p_list->next->next != NULL){
        p_list = p_list->next;
    }
    p_list_next = p_list->next;
    free(p_list_next);
    p_list->next = NULL;
    return LIST_MODULE_ERROR_OK;
}
list_module_error_t delete_node_begin(list_module_t* list){
    list_module_t* p_list = list;
    if (p_list == NULL){
        return LIST_MODULE_NULL_ERROR;
    }
    if (p_list->next == NULL){
        return LIST_MODULE_EMPTY;
    }

    return LIST_MODULE_ERROR_OK;
}
//todo: fix
list_module_t* flip_list(list_module_t* list){
    list_module_t* prev = NULL;
    list_module_t* curr = list;
    list_module_t* next = NULL;

    while (curr != NULL){
        next = curr->next;
        curr->next = prev;


        prev = curr;
        curr = next;
    }
    return prev;
}

list_module_error_t print_list_rec(list_module_t* list) {
    if (list == NULL) {
        printf(" NULL");
        return;
    }
    printf("%d -> ",list->data);
    print_list_rec(list->next);
}

list_module_t* flip_list_rec(list_module_t* list) {
    // Base case: if head is NULL or only one node, return head
    if (list == NULL || list->next == NULL) {
        return list;
    }
    list_module_t* new_head = flip_list_rec(list->next);
    list->next->next = list;
    list->next = NULL;

    return new_head;

}











