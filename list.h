#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

/*
 * Struct stores a list of things.
 * Properties:
 *  - elements = The contents of the list.
 *  - size = size of the list.
 *  - maxSize = The maximum allocated space for the list currently.
 */
typedef struct {
    void** elements;
    int size;
    int maxSize;
} List;


/*
 * Creates a list from scratch.
 */
List* create_list(int startingSize);

/*
 * Frees a list from memory. If 'hardFree' is true then not only
 * will the list and object be free'd but each element inside the
 * list will be freed as well.
 */
void free_list(List* list, bool hardFree);

/*
 * Adds an element to a list. Creating more space if
 * needed.
 */
void add_to_list(List* list, void* element);

/*
 * Removes an element from a list given it's index.
 */
void remove_from_list(List* list, int index);


#endif
