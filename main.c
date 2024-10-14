#include "List.h"
int main(void){
    list_module_t* ptr = init_list();
    print_list(ptr);
    printf("size: %zu\n",list_size(ptr));
    printf("is empty? %d\n",is_list_empty(ptr));
    insert_node_begin(ptr,5);
    insert_node_begin(ptr,2);
    insert_node_begin(ptr,1);
    insert_node_end(ptr,15);
    insert_node_middle(ptr, 3);
    print_list(ptr);
    printf("size %zu\n",list_size(ptr));
    printf("is empty? %d\n",is_list_empty(ptr));
    delete_node(ptr);
    printf("size %zu\n",list_size(ptr));
    printf("is loop? %d\n",find_loop(ptr));
    print_list(ptr);
    delete_node(ptr);
    print_list(ptr);
    destroy_list(ptr);
    printf("-------------\n");
    ptr = init_list();
    insert_node_begin(ptr,3);
    insert_node_begin(ptr,1);
    insert_node_begin(ptr,0);
    print_list(ptr);
    delete_node_end(ptr);
    print_list(ptr);
    destroy_list(ptr);
    printf("-------------\n");
    printf("testing flip\n");
    ptr = init_list();
    insert_node_begin(ptr,1);
    insert_node_end(ptr,3);
    insert_node_middle(ptr,2);
    print_list(ptr);
    print_list_rec(ptr);


    return 0;
}
