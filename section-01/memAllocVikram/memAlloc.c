#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;         //Unique identifier for this allocation
    size_t size;    //Size in bytes
    void* addr;     //Address returned by malloc
} allocation_t;

allocation_t *allocations = NULL;   // dynamic array to store the allocations
size_t alloc_count = 0;             // number of current allocations
int idNum = 1;                      // the id of the next item, for automatically assigning IDs

// this function will allocate memory and store the metadata of that entry into a dynamic array
void *add_allocation (size_t size) {
    void *arr = malloc(size);
    if (!arr)                       // if theres insufficient memory it'll return NULL :)
        return NULL;
    
    allocation_t *temp = realloc(allocations, (alloc_count + 1) * sizeof(allocation_t));     //set the realloc to a temp in case theres any problems
    if (!temp) {
        free (arr);
        return NULL;
    }
    allocations = temp;             //sets allocations to the reallocated array, basically resizing it kinda

    //add all the new metadata to the new item
    allocations[alloc_count].id = idNum++;
    allocations[alloc_count].addr = arr;
    allocations[alloc_count].size = size;
    alloc_count++;
}

// this function will free memory using the free operator and remove the struct by ID
int remove_allocation(int id) {
    for (size_t i = 0; i < alloc_count; i++) {  //run a for loop to check for that ID number
        if (allocations[i].id == id) {
            free (allocations[i].addr);

            for (size_t j = i; j < alloc_count - 1; j++) { //this will shift all the remaining items, hopefully
                allocations[j] = allocations[j + 1];
            }
            alloc_count--;

            if (alloc_count == 0) {
                free(allocations);
                allocations = NULL;
            } else {
                allocations = realloc(allocations, alloc_count * sizeof(allocation_t));
            }
            return 1;   //returns 1 as succes
        }
    }
    return 0;           //returns 0 as item not found
}

// this function says the number of structs and prints out the stored metadata
void print_allocations() {
    printf("Active Allocations (%zu):\n", alloc_count);         //says how many items are in allocations
    for (size_t i = 0; i < alloc_count; i++) {
        printf("ID=%d | Size=%zu | Addr=%p\n", allocations[i].id, allocations[i].size, allocations[i].addr); //literally prints everything out in a for loop
    }
}

int main(void) {
    char *a = add_allocation(32);
    int  *b = add_allocation(10 * sizeof(int));
    double *c = add_allocation(5 * sizeof(double));

    print_allocations();

    printf("\nRemoving ID 2...\n");
    remove_allocation(2);

    print_allocations();

    printf("\nAdding something afterward...\n");
    int *d = add_allocation(10 * sizeof(int));
    print_allocations();

    printf("\nRemoving Everything...\n");
    while (alloc_count > 0) {
        remove_allocation(allocations[0].id);
    }

    print_allocations();

    return 0;
}