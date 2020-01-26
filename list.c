#include "list.h"

List* create_list(int startingSize) {
    List* list = (List*) malloc(sizeof(List));

    list->elements = (void**) calloc(startingSize, sizeof(void*));

    list->size = 0;

    list->maxSize = startingSize;

    return list;
}

void free_list(List* list, bool hardFree) {
    
    if (hardFree) {
        for (int i = 0; i < list->size; i++) {
            free(list->elements[i]);
        }
    }

    free(list->elements);

    free(list);
}

void add_to_list(List* list, void* element) {
    // Check if at maximum capacity
    if (list->size >= list->maxSize) {
        // Allocate more space.
        list->maxSize += 10;

        int byteSize = sizeof(void*) * list->maxSize;

        list->elements = (void**) realloc(list->elements, byteSize);
    }

    list->elements[list->size] = element;
    list->size++;
}

void remove_from_list(List* list, int index) {
    // Go through and move everything from the list down.
    for (int i = index + 1; i < list->size; i++) {
        list->elements[i - 1] = list->elements[i];
    }

    list->size--;
}
