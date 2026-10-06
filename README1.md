# Project A - Popup UI Stack (C, Array)

A popup manager for a user interface. Popups stack on the screen (LIFO): the most
recently opened popup is in front and must be closed first. 
## Real world Application 
 A student study website for example Muele where by I open the Home first then i open the dashboard then after i open courses it follows the LIFO where by the last to be opened is the first to be closed.

## Files
- UI.h  - Popup and PopupStack (the stack is represented by an array,and an index records the current top item), function declarations(it tells the compiler a function's name , input and what it returns) eg int isEmpty(const PopupStack *s) {
    return s->top == -1;
}


- UI.c  - Stack operations: initStack, isEmpty, isFull, size, push, pop, peek, display

- main.c - Popup Manager menu (application code and rules)

## Build and run
This is how we run our appplication in the terminal
   cd data-structures-project1
   gcc .\main.c .\UI.c -o ..\myprogram.exe
   ..\myprogram.exe


