// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() {
  list_t *list = (list_t *) malloc(sizeof(list_t));
  list->head = NULL;
  return list;
}
void list_free(list_t *l) {
  node_t *current = l->head;
  node_t *next;
  while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
  }
  l->head = NULL;
}

void list_print(list_t *l) {
  if (l->head == NULL) {
    printf("The linked list is empty.\n");
    return;
  }

  node_t *current = l->head;
  while (current != NULL) {
      printf("%d ", current->value);
      current = current->next;
  }
  printf("\n");
}
int list_length(list_t *l) {
  int length = 0;
  node_t *current = l->head;
  while (current != NULL) {
      length++;
      current = current->next;
  }
  return length;
 }

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  if (l->head == NULL) {
      l->head = new_node;
      return;
  }

  node_t *current = l->head;
  while (current->next != NULL) {
      current = current->next;
  }
  
  current->next = new_node;
}
void list_add_to_front(list_t *l, elem value) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->value = value;

  new_node->next = l->head;
  l->head = new_node;
}
void list_add_at_index(list_t *l, elem value, int index) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->value = value;

  if (index == 0) {
      new_node->next = l->head;
      l->head = new_node;
      return;
  }

  node_t *current = l->head;
  for (int i = 0; i < index - 1; i++) {
      if (current == NULL) return; // index out of bounds
      current = current->next;
  }

  new_node->next = current->next;
  current->next = new_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) {
      return -1; // List is empty
  }

  node_t *current = l->head;
  node_t *prev = NULL;
  while (current->next != NULL) {
      prev = current;
      current = current->next;
  }

  elem value = current->value;
  free(current);

  if (prev != NULL) {
      prev->next = NULL;
  } else {
      l->head = NULL; // List is now empty
  }

  return value;
}

elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) {
      return -1; // List is empty
  }

  node_t *next_node = l->head->next;
  elem value = l->head->value;

  free(l->head);
  l->head = next_node;

  return value;
}

elem list_remove_at_index(list_t *l, int index) {
  if (l->head == NULL || index < 0) {
      return -1; // List is empty or index is invalid
  }

  if (index == 0) {
      return list_remove_from_front(l);
  }

  node_t *current = l->head;
  node_t *prev = NULL;
  for (int i = 0; i < index; i++) {
      if (current == NULL) {
          return -1; // Index is out of bounds
      }
      prev = current;
      current = current->next;
  }

  if (current == NULL) {
      return -1; // Index is out of bounds
  }

  elem value = current->value;
  prev->next = current->next;

  free(current);

  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t *current = l->head;
    
	while (current != NULL) {
		if (current->value == value) {
			return true;
		}
		current = current->next;
	}
	
	return false;
}

elem list_get_elem_at(list_t *l, int index) {
	if (l->head == NULL || index < 0) {
		return -1; // List is empty or index is invalid
	}

	node_t *current = l->head;
	for (int i = 0; i < index; i++) {
		if (current == NULL) {
			return -1; // Index is out of bounds
		}
		current = current->next;
	}

	if (current == NULL) {
		return -1; // Index is out of bounds
	}

	return current->value;
}

int list_get_index_of(list_t *l, elem value) {
	node_t *current = l->head;

	for (int i = 0; current != NULL; i++) {
		if (current->value == value) {
			return i;
		}
		current = current->next;
	}

	return -1; // Element not found in the list
}

char* get_list(list_t *l) {
  node_t *current = l->head;
  char *list_str = malloc(1000 * sizeof(char));
  list_str[0] = '\0';

  while (current != NULL) {
      char node_str[50];
      sprintf(node_str, "%d->", current->value);
      strcat(list_str, node_str);

      current = current->next;
  }

  strcat(list_str, "NULL");

  return list_str;
}

