#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main(int argc, char **argv) {
    printf("Running tests...\n\n");

    Node *head = NULL;

    /*********** reverse_list test ***********/
    reverse_list(&head);
    for (int i = 0; i < 5; ++i) {
        add_to_front(&head, i);
        reverse_list(&head);
    }

    int expected_values[] = {3, 1, 0, 2, 4};
    Node *curr = head;
    for (int i = 0; i < 5; ++i) {
        assert(curr->data == expected_values[i]);
        curr = curr->next;
    }
    free_list(head);

    printf("Congrats! All of the test cases passed!\n");
    return 0;
}
