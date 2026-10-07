# BSSE II Data Structures Project: LIFO & FIFO Implementation

**Group:** B2

This submission contains two programs, one for each abstract data type (ADT). Both are written from scratch with no built-in Stack or Queue classes, and both are menu-driven: they keep showing a menu until the user chooses Exit.

| | Project A | Project B |
| --- | --- | --- |
| **ADT** | Stack (LIFO) | Queue (FIFO) |
| **Application** | Popup Manager | Call Centre Support Queue |
| **Language** | C | Java |
| **Underlying structure** | Array | Linked list |
| **Folder** | `Project_A_Stack/` | `Project_B_Queue/` |

## Folder Structure

```
Project_A_Stack/
    Main.c      menu and user input only
    UI.c        stack operations (push, pop, peek, ...) and drawing
    UI.h        Popup and PopupStack definitions, function declarations
Project_B_Queue/
    src/
        Main.java            menu and user input only
        CallCenterQueue.java queue operations (front, rear, size)
        CallNode.java        one link in the linked list
        Call.java            the data stored: caller name, issue, timestamp
```

## How to Compile and Run

**Project A (C)** needs `gcc`:

```
cd Project_A_Stack
gcc Main.c UI.c -o popup
./popup            (on Windows: popup.exe)
```

**Project B (Java)** needs the JDK (`javac`):

```
cd Project_B_Queue/src
javac *.java
java Main
```

---

# Project A: Popup Manager (Stack, C, Array)

## The Real-World Problem

Popup windows on a PC screen stack on top of each other. A new popup opens in front and covers the ones behind it, and the only way to see the previous popup is to close the front one with its **[x]** button. The most recently opened popup is always closed first, which is **Last In, First Out**.

## Menu

| Option | Action | Stack operation |
| --- | --- | --- |
| 1 | Open a popup (asks for a title and a message) | `push` |
| 2 | Close the front popup [x] | `pop` |
| 3 | View the front popup without closing it | `peek` |
| 4 | Show the screen (all popups, front first) | `display` |
| 0 | Exit | |

## How the Stack Works

The stack is a `PopupStack` structure holding an array `popups` (up to `MAX_POPUPS` = 5) and an integer `top`, the index of the front popup. `top == -1` means the stack is empty.

- **push:** if the stack is full, refuse. Otherwise increase `top` by 1 first, then store the popup at `popups[top]`.
- **pop:** if the stack is empty, refuse. Otherwise copy out the popup at `popups[top]` first, then decrease `top` by 1.
- **peek:** read `popups[top]` without moving `top`.
- **isEmpty:** `top == -1`. **isFull:** `top == MAX_POPUPS - 1`. **size:** `top + 1`.

## Edge Cases Handled

- Closing or viewing when no popups are open prints a warning.
- Opening a 6th popup is refused with a "screen is full" warning, before the user types anything.
- Non-numbers and unknown menu choices are rejected.
- Text longer than the limits (title 29 characters, message 59) is shortened and does not spill into the next prompt.
- A blank title or message gets a default.
- End of input exits cleanly.

---

# Project B: Call Centre Support Queue (Queue, Java, Linked List)

## The Real-World Problem

A helpdesk call centre answers callers **first come, first served**. Callers join the back of the waiting line, and each time an agent is free they answer the caller who has waited longest. This is **First In, First Out**.

## Menu

| Option | Action | Queue operation |
| --- | --- | --- |
| 1 | Receive a call (asks for caller name and issue type) | `enqueue` (`receiveCall`) |
| 2 | Answer the next call | `dequeue` (`answerCall`) |
| 3 | View the next caller without answering | `front` (`viewFront`) |
| 4 | Show all waiting calls | `printFullQueue` |
| 0 | Exit | |

`isEmpty()` is also implemented and is used by the other operations as their empty check.

## How the Queue Works

The queue is a chain of `CallNode` objects, each holding one `Call` and a `next` reference to the node behind it. `CallCenterQueue` keeps `front` (head), `rear` (tail) and `size`. Both `front` and `rear` are `null` when the queue is empty.

- **enqueue:** create a new node. If the queue is empty, `front` and `rear` both point to it. Otherwise attach it to `rear.next`, then move `rear` forward to the new node.
- **dequeue:** if the queue is empty, warn. Otherwise save the call at `front` and reassign `front` to `front.next`. If `front` becomes `null`, also set `rear` to `null`.
- **front (view):** return the call at `front` without removing it.
- **printFullQueue:** walk the list from `front` using a temporary pointer, so `front` itself never moves.

Each `Call` stores the caller's name, the issue type, and a timestamp recorded when the call is created.

## Edge Cases Handled

- Answering or viewing when no calls are waiting prints "No calls in the queue." and does not crash.
- Showing an empty queue prints a clear message.
- A blank caller name or issue type is rejected.
- Non-numbers and unknown menu choices are rejected.
- No "full" check is needed, because a linked list grows as needed.

---

## Notes

- Both projects keep the data structure code separate from the menu code in `Main`.
- The implementation report (PDF) explains the push/pop and enqueue/dequeue mechanics in plain English and includes screenshots of both programs running.
