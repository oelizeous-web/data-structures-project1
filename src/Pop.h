#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 5      /* max popups open at once */
#define TEXT_LEN 50   /* popup title length */

typedef struct {
    char data[MAX_SIZE][TEXT_LEN]; /* the underlying array */
    int top;                       /* index of the newest item, -1 = empty */
} Stack;

void initStack(Stack *s);
int  isEmpty(const Stack *s);
int  isFull(const Stack *s);
int  push(Stack *s, const char *text);            /* 1 = ok, 0 = full  */
int  pop(Stack *s, char *out);                    /* 1 = ok, 0 = empty */
int  peek(const Stack *s, char *out);             /* 1 = ok, 0 = empty */
void display(const Stack *s);

#endif