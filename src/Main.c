/* Popup UI Stack - open popups are stacked on screen (LIFO).
   Only the TOP popup can be closed; the most recently opened closes first. */
#include <stdio.h>
#include <string.h>
#include "pop.h"

int main(void) {
    Stack popups;
    char title[TEXT_LEN], closed[TEXT_LEN];
    int choice;

    initStack(&popups);

    do {
        printf("\n=== Popup Manager ===\n");
        printf("1. Open a popup   (push)\n2. Close top popup (pop)\n");
        printf("3. View top popup (peek)\n4. Show all open popups\n0. Exit\nChoice: ");
        fflush(stdout);                              /* show prompt before waiting for input */
        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) break;                  /* stop cleanly when no input is available */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF); /* discard invalid input */
            printf("Please enter a number.\n");
            choice = -1;
            continue;
        }
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); /* clear leftover input */

        switch (choice) {
        case 1:
            printf("Popup title: ");
            fflush(stdout);
            if (fgets(title, sizeof title, stdin) == NULL) {
                if (feof(stdin)) { choice = 0; break; }
                printf("Could not read popup title.\n");
                break;
            }
            title[strcspn(title, "\n")] = '\0';
            if (push(&popups, title)) printf("Opened popup: \"%s\"\n", title);
            else printf("WARNING: Too many popups open! Close one first.\n");
            break;
        case 2:
            if (pop(&popups, closed)) printf("Closed popup: \"%s\"\n", closed);
            else printf("WARNING: No popups to close.\n");
            break;
        case 3:
            if (peek(&popups, closed)) printf("Top popup: \"%s\"\n", closed);
            else printf("WARNING: No popups open.\n");
            break;
        case 4: display(&popups); break;
        case 0: printf("Goodbye!\n"); break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}