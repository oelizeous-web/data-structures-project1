#ifndef UI_H
#define UI_H

#define MAX_POPUPS 5     /* most popups that can be open at once */
#define TITLE_LEN  30
#define MSG_LEN    60

/* One popup window */
typedef struct {
    char title[TITLE_LEN];
    char message[MSG_LEN];
} Popup;

/* The stack: an array of popups plus the index of the front one */
typedef struct {
    Popup popups[MAX_POPUPS];
    int top;                 /* index of the front popup, -1 = no popups */
} PopupStack;

void        initStack(PopupStack *s);
int         isEmpty(const PopupStack *s);
int         isFull(const PopupStack *s);
int         size(const PopupStack *s);                 /* how many are open */
int         push(PopupStack *s, Popup p);              /* 1 = opened, 0 = full  */
int         pop(PopupStack *s, Popup *closed);         /* 1 = closed, 0 = empty */
int         peek(const PopupStack *s, Popup *front);   /* 1 = ok,     0 = empty */
void        display(const PopupStack *s);              /* draws popups as boxes */

#endif