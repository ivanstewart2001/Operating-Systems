#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

int main() {
  printf("Write your Tests for your linked list implementation\n");
  list_t *mylist;
  mylist = list_alloc();
  list_print(mylist);
  list_add_to_front(mylist, 10);
  list_add_to_front(mylist, 20);
  list_add_to_front(mylist, 30);
  list_add_to_front(mylist, 40);
  list_add_to_front(mylist, 50);
  list_add_to_front(mylist, 60);
  list_add_to_front(mylist, 70);
  list_add_to_front(mylist, 80);
  list_add_to_front(mylist, 90);
  list_add_to_front(mylist, 100);
  list_print(mylist);

  if(strcmp("100->90->80->70->60->50->40->30->20->10->NULL",get_list(mylist)) != 0) {
    printf("list_add_to_front : FAILED\n\n");
  } else {
    printf("\nlist_add_to_front: PASSED\n\n");
  }

  list_remove_at_index(mylist, 3);
  if(strcmp("100->90->80->60->50->40->30->20->10->NULL",get_list(mylist)) != 0) {
    printf("list_remove_at_index : FAILED\n\n");
  } else {
    printf("\nlist_remove_at_index: PASSED\n\n");
  }

  list_remove_at_index(mylist, 20);
  if(strcmp("100->90->80->60->50->40->30->20->10->NULL",get_list(mylist)) != 0) {
    printf("list_remove_at_index : FAILED\n\n");
  } else {
    printf("\nlist_remove_at_index: PASSED\n\n");
  }

  list_remove_at_index(mylist, 0);
  if(strcmp("90->80->60->50->40->30->20->10->NULL",get_list(mylist)) != 0) {
    printf("list_remove_at_index : FAILED\n\n");
  } else {
    printf("\nlist_remove_at_index: PASSED\n\n");
  }

  list_remove_at_index(mylist, 6);
  if(strcmp("90->80->60->50->40->30->10->NULL",get_list(mylist)) != 0) {
    printf("\nlist_remove_at_index : FAILED\n\n");
  } else {
    printf("\nlist_remove_at_index: PASSED\n\n");
  }
  
  if(list_length(mylist) != 7) {
    printf("\nlist_length : FAILED\n\n");
  } else {
    printf("\nlist_length: PASSED\n\n");
  }

  list_add_to_back(mylist, 39);
  list_add_to_back(mylist, 18);
  list_add_to_back(mylist, 42);
  list_add_to_back(mylist, 190);
  list_free(mylist);

  if(list_length(mylist) != 0) {
    printf("\nlist_free : FAILED\n\n");
  } else {
    printf("\nlist_free: PASSED\n\n");
  }

  list_add_to_front(mylist, 81);
  list_add_to_back(mylist, 4);
  list_add_to_front(mylist, 308);
  list_add_to_back(mylist, 70);
  list_add_to_front(mylist, 290);

  if(list_get_elem_at(mylist, 0) != 290) {
    printf("\nlist_add_to_front : FAILED\n\n");
  } else {
    printf("\nlist_add_to_front: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, 4) != 70) {
    printf("\nlist_add_to_back: FAILED\n\n");
  } else {
    printf("\nlist_add_to_back: PASSED\n\n");
  }
  
  list_add_at_index(mylist, 65, 0);
  if(list_get_elem_at(mylist, 0) != 65) {
    printf("\nlist_add_at_index: FAILED\n\n");
  } else {
    printf("\nlist_add_at_index: PASSED\n\n");
  }

  list_add_at_index(mylist, 100, 3);
  if(list_get_elem_at(mylist, 3) != 100) {
    printf("\nlist_add_at_index: FAILED\n\n");
  } else {
    printf("\nlist_add_at_index: PASSED\n\n");
  }

  list_remove_from_back(mylist);
  if((list_get_elem_at(mylist, 5) != 4) || (list_length(mylist) != 6)) {
    printf("\nlist_remove_from_back: FAILED\n\n");
  } else {
    printf("\nlist_remove_from_back: PASSED\n\n");
  }

  list_remove_from_front(mylist);
  if((list_get_elem_at(mylist, 0) != 290) || (list_length(mylist) != 5)) {
    printf("\nlist_remove_from_front: FAILED\n\n");
  } else {
    printf("\nlist_remove_from_front: PASSED\n\n");
  }

  list_remove_at_index(mylist, 3);
  if((list_get_elem_at(mylist, 3) == 81) || (list_length(mylist) != 4)) {
    printf("\nlist_remove_at_index: FAILED\n\n");
  } else {
    printf("\nlist_remove_at_index: PASSED\n\n");
  }

  if(list_is_in(mylist, 21) == 1) {
    printf("\nlist_is_in: FAILED\n\n");
  } else {
    printf("\nlist_is_in: PASSED\n\n");
  }

  if(list_is_in(mylist, 290) == 0) {
    printf("\nlist_is_in: FAILED\n\n");
  } else {
    printf("\nlist_is_in: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, 0) != 290) {
    printf("\nlist_get_elem_at: FAILED\n\n");
  } else {
    printf("\nlist_get_elem_at: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, 1) != 308) {
    printf("\nlist_get_elem_at: FAILED\n\n");
  } else {
    printf("\nlist_get_elem_at: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, 2) != 100) {
    printf("\nlist_get_elem_at: FAILED\n\n");
  } else {
    printf("\nlist_get_elem_at: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, 3) != 4) {
    printf("\nlist_get_elem_at: FAILED\n\n");
  } else {
    printf("\nlist_get_elem_at: PASSED\n\n");
  }

  if(list_get_elem_at(mylist, -2) != -1) {
    printf("\nlist_get_elem_at: FAILED\n\n");
  } else {
    printf("\nlist_get_elem_at: PASSED\n\n");
  }

  if(list_get_index_of(mylist, 290) != 0) {
    printf("\nlist_get_index_of: FAILED\n\n");
  } else {
    printf("\nlist_get_index_of: PASSED\n\n");
  }

  if(list_get_index_of(mylist, 308) != 1) {
    printf("\nlist_get_index_of: FAILED\n\n");
  } else {
    printf("\nlist_get_index_of: PASSED\n\n");
  }

  if(list_get_index_of(mylist, 100) != 2) {
    printf("\nlist_get_index_of: FAILED\n\n");
  } else {
    printf("\nlist_get_index_of: PASSED\n\n");
  }

  if(list_get_index_of(mylist, 4) != 3) {
    printf("\nlist_get_index_of: FAILED\n\n");
  } else {
    printf("\nlist_get_index_of: PASSED\n\n");
  }

  if(list_get_index_of(mylist, 81) != -1) {
    printf("\nlist_get_index_of: FAILED\n\n");
  } else {
    printf("\nlist_get_index_of: PASSED\n\n");
  }
  
  list_print(mylist);
  return 0;
}