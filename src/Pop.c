#include <stdio.h>
#include <string.h>
#include "pop.h"

void initStack(Stack *s) {
    s->top = -1;                         /* -1 means no items yet */
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int push(Stack *s, const char *text) {
    if (isFull(s)) return 0;             /* overflow guard */
    s->top++;                            /* move top up FIRST ...   */
    strncpy(s->data[s->top], text, TEXT_LEN - 1);   /* ... then store */
    s->data[s->top][TEXT_LEN - 1] = '\0';
    return 1;
}

int pop(Stack *s, char *out) {
    if (isEmpty(s)) return 0;            /* underflow guard */
    strcpy(out, s->data[s->top]);        /* read the newest item FIRST ... */
    s->top--;                            /* ... then move top down */
    return 1;
}

int peek(const Stack *s, char *out) {
    if (isEmpty(s)) return 0;
    strcpy(out, s->data[s->top]);        /* top is NOT changed */
    return 1;
}

void display(const Stack *s) {
    if (isEmpty(s)) { printf("  (no popups open)\n"); return; }
    for (int i = s->top; i >= 0; i--)    /* newest first */
        printf("  [%d] %s%s\n", i, s->data[i], i == s->top ? "   <-- top" : "");
}