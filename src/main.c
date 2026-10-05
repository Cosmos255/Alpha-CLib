#include <stdio.h>
#include <string.h>
#include "../alfa/gamma.h"
#include "../alfa/stack.h"

// Example custom element type that requires cleanup
typedef struct {
    int id;
    char *name;
} Item;

// Destructor for our custom item
void item_destructor(Item *item) {
    printf("-> Destroying item id: %d, name: %s\n", item->id, item->name);
    free(item->name);
}

int main(void) {
    // 1. Initialize the dynamic array
    Gamma(Item) list = {0};
    list.destructor = item_destructor;

    // 2. Test Resize & Push (manual or via resize)
    printf("--- Resizing and Adding Items ---\n");
    gamma_resize(&list, 3);
    
    list.items[0] = (Item){10, strdup("Apple")};
    list.items[1] = (Item){20, strdup("Banana")};
    list.items[2] = (Item){30, strdup("Cherry")};
    list.size = 3;

    printf("Array size: %zu, capacity: %zu\n", list.size, list.capacity);

    // 3. Test Remove (middle element)
    printf("\n--- Removing Index 1 (Banana) ---\n");
    gamma_remove(&list, 1);
    printf("New size after remove: %zu\n", list.size);
    for (size_t i = 0; i < list.size; i++) {
        printf("Index %zu: {id: %d, name: %s}\n", i, list.items[i].id, list.items[i].name);
    }

    // 4. Test Shrinking Resize
    printf("\n--- Shrinking Array to size 1 ---\n");
    gamma_resize(&list, 1);
    printf("Size after shrink: %zu, capacity: %zu\n", list.size, list.capacity);

    // 5. Clean up remaining items
    printf("\n--- Final Cleanup ---\n");
    gamma_resize(&list, 0);
    free(list.items);

    return 0;
}

