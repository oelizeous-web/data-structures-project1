/* Popup Manager - application code only.
   Popups stack on the screen (LIFO): the most recently opened popup is in
   front and must be closed first. All array/top handling lives in UI.c. */
#include <stdio.h>
#include <string.h>
#include "UI.h"

static void readLine(const char *prompt, char *dest, int maxLen) {
    printf("%s", prompt);
    fgets(dest, maxLen, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

static void openPopup(PopupStack *screen) {
    Popup p;

    readLine("Popup title: ", p.title, TITLE_LEN);
    readLine("Popup message: ", p.message, MSG_LEN);

    if (push(screen, p)) {
        printf("Opened popup: \"%s\"\n", p.title);
        if (size(screen) >= 3)
            printf("Note: %d popups are open - the screen is getting crowded.\n", size(screen));
    } else {
        printf("WARNING: Screen is full (%d popups). Close one first.\n", MAX_POPUPS);
    }
}

static void closeTop(PopupStack *screen) {
    Popup closed;
    if (pop(screen, &closed)) printf("Closed popup: \"%s\"\n", closed.title);
    else printf("WARNING: No popups to close.\n");
}

static void viewFront(const PopupStack *screen) {
    Popup front;
    if (peek(screen, &front)) printf("Front popup: \"%s\" - %s\n", front.title, front.message);
    else printf("WARNING: No popups are open.\n");
}

static void closeAll(PopupStack *screen) {
    Popup closed;
    if (isEmpty(screen)) { printf("WARNING: No popups to close.\n"); return; }
    while (pop(screen, &closed))                  /* newest closes first */
        printf("Closed popup: \"%s\"\n", closed.title);
    printf("Screen is now clear.\n");
}

int main(void) {
    PopupStack screen;
    int choice;

    initStack(&screen);

    do {
        printf("\n=== Popup Manager ===\n");
        printf("1. Open a popup      (push)\n2. Close front popup   (pop)\n");
        printf("3. View front popup  (peek)\n4. Show screen\n5. Close all popups\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {          /* not a number */
            while (getchar() != '\n');
            printf("Please enter a number.\n");
            choice = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: openPopup(&screen);  break;
            case 2: closeTop(&screen);   break;
            case 3: viewFront(&screen);  break;
            case 4: display(&screen);    break;
            case 5: closeAll(&screen);   break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}