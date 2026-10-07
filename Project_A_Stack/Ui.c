#include <stdio.h>
#include <string.h>
#include "UI.h"

void initStack(PopupStack *s) {
    s->top = -1;                          /* -1 means no popups are open */
}

int isEmpty(const PopupStack *s) {
    return s->top == -1;
}

int isFull(const PopupStack *s) {
    return s->top == MAX_POPUPS - 1;      /* last valid index */
}

int size(const PopupStack *s) {
    return s->top + 1;                    /* indexes start at 0 */
}

/* PUSH (open): move top up by 1 FIRST, then store the popup at the new top */
int push(PopupStack *s, Popup p) {
    if (isFull(s)) return 0;              /* overflow guard */
    s->top++;
    s->popups[s->top] = p;
    return 1;
}

/* POP (close): read the popup at top FIRST, then move top down by 1 */
int pop(PopupStack *s, Popup *closed) {
    if (isEmpty(s)) return 0;             /* underflow guard */
    *closed = s->popups[s->top];
    s->top--;
    return 1;
}

/* PEEK: look at the front popup, top does NOT move */
int peek(const PopupStack *s, Popup *front) {
    if (isEmpty(s)) return 0;
    *front = s->popups[s->top];
    return 1;
}

/* ---- Drawing -------------------------------------------------------------
   Box width is derived from MSG_LEN so the longest allowed message always
   fits inside the box. Only the FRONT popup shows a [x] button, because only
   the front popup can be closed - the ones behind it are covered. */
#define INNER (MSG_LEN - 1)               /* usable characters per row */

static void drawBorder(void) {
    putchar('+');
    for (int k = 0; k < INNER + 2; k++) putchar('-');
    puts("+");
}

/* Draw popups from the front (top) down to the back (index 0) */
void display(const PopupStack *s) {
    if (isEmpty(s)) { printf("  (screen is clear - no popups open)\n"); return; }
    for (int i = s->top; i >= 0; i--) {
        const Popup *p = &s->popups[i];
        int isFront = (i == s->top);

        printf("  "); drawBorder();
        /* title bar: title on the left, [x] close button on the right */
        printf("  | %-*s %s |\n", INNER - 4, p->title, isFront ? "[x]" : "   ");
        printf("  | %-*s |\n", INNER, p->message);
        printf("  "); drawBorder();
        if (isFront) printf("    ^ FRONT (top) - the only popup you can close\n");
        else         printf("    (behind - hidden until the popups in front are closed)\n");
    }
}