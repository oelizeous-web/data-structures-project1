/* Popup Manager - application code only.
   Popups stack on the screen (LIFO): the most recently opened popup is in
   front and must be closed (the [x] button) before the one behind it can be
   seen. All array/top handling lives in UI.c. */
#include <stdio.h>
#include <string.h>
#include "UI.h"

/* Throw away the rest of the current input line. */
static void flushLine(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Read one line of text into dest (at most maxLen-1 characters).
   Returns 0 if input has ended (EOF), 1 otherwise.
   Extra characters are discarded so they cannot leak into the next prompt. */
static int readLine(const char *prompt, char *dest, int maxLen) {
    printf("%s", prompt);
    if (fgets(dest, maxLen, stdin) == NULL) return 0;       /* EOF / Ctrl+D */

    if (strchr(dest, '\n') == NULL) {                       /* line was too long */
        flushLine();
        printf("(Text was longer than %d characters and was shortened.)\n", maxLen - 1);
    }
    dest[strcspn(dest, "\n")] = '\0';
    return 1;
}

/* Read a menu choice. Returns -1 for non-numeric input, 0 (Exit) on EOF. */
static int readChoice(void) {
    char buf[32];
    int value;

    printf("Choice: ");
    if (fgets(buf, sizeof buf, stdin) == NULL) return 0;    /* EOF -> exit */
    if (strchr(buf, '\n') == NULL) flushLine();
    if (sscanf(buf, "%d", &value) != 1) return -1;
    return value;
}

static void openPopup(PopupStack *screen) {
    Popup p;

    /* Check BEFORE asking for text, so the user doesn't type a popup
       only to be told there is no room for it. */
    if (isFull(screen)) {
        printf("WARNING: Screen is full (%d popups). Close one first.\n", MAX_POPUPS);
        return;
    }

    if (!readLine("Popup title: ", p.title, TITLE_LEN))     return;
    if (!readLine("Popup message: ", p.message, MSG_LEN))   return;
    if (p.title[0]   == '\0') strcpy(p.title, "Untitled");
    if (p.message[0] == '\0') strcpy(p.message, "(no message)");

    if (push(screen, p)) {
        printf("Opened popup: \"%s\" - it is now in front.\n", p.title);
        if (size(screen) >= 3)
            printf("Note: %d popups are open - the screen is getting crowded.\n", size(screen));
    } else {
        printf("WARNING: Screen is full (%d popups). Close one first.\n", MAX_POPUPS);
    }
}

/* Clicking [x] on the front popup: it disappears and the one that was
   hidden behind it is revealed. This is the LIFO behaviour made visible. */
static void closeTop(PopupStack *screen) {
    Popup closed, revealed;

    if (!pop(screen, &closed)) {
        printf("WARNING: No popups to close.\n");
        return;
    }
    printf("Closed popup: \"%s\"\n", closed.title);

    if (peek(screen, &revealed))
        printf("Now in front: \"%s\" - %s\n", revealed.title, revealed.message);
    else
        printf("Screen is now clear.\n");
}

static void viewFront(const PopupStack *screen) {
    Popup front;
    if (peek(screen, &front)) printf("Front popup: \"%s\" - %s\n", front.title, front.message);
    else printf("WARNING: No popups are open.\n");
}

int main(void) {
    PopupStack screen;
    int choice;

    initStack(&screen);

    do {
        printf("\n=== Popup Manager ===\n");
        printf("1. Open a popup         (push)\n2. Close front popup [x] (pop)\n");
        printf("3. View front popup     (peek)\n4. Show screen\n0. Exit\n");
        choice = readChoice();

        switch (choice) {
            case 1: openPopup(&screen);  break;
            case 2: closeTop(&screen);   break;
            case 3: viewFront(&screen);  break;
            case 4: display(&screen);    break;
            case 0: printf("Goodbye!\n"); break;
            case -1: printf("Please enter a number.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}