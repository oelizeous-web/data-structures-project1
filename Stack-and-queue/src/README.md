# Project B: Queue Implementation (Java / Linked List)

## 1. Real-World Application Description
Our application models a helpdesk ticketing system for a customer support call center. This scenario heavily relies on a "first come, first served" processing model, which specifically requires Queue (FIFO) logic. Incoming support requests are queued in the exact sequence they are received, guaranteeing that the queue outputs the oldest addition first.

## 2. Core Structure Mechanics
The core operations were developed entirely from scratch in Java, strictly avoiding any built-in Java `Queue` classes. The underlying physical structure uses a dynamically allocated Linked List to connect elements via node references. The structural boundaries are maintained using a `front` (`head`) pointer and a `rear` (`tail`) pointer.

*   **Enqueue (`receiveCall`):** When a new call arrives, we create a custom node. To process the addition, we attach the new Node to the current `tail.next` (in our code, `rear.next`) and then move the `tail` reference forward so it accurately points to the newly added back of the line.
*   **Dequeue (`answerCall`):** When an agent is available, the queue outputs the data by removing nodes directly from the `head`. We capture the data at the `front` node, reassign the `front` reference to `front.next`, and allow the removed node to drop off the list.
*   **Edge Case Handling:** To ensure robust edge-case management, the dequeue function checks if the queue is empty first; if an agent attempts to answer a call when the structure is empty, the program prints a clear warning instead of triggering a null pointer exception crash.

## 3. Code Separation and Operation Mapping
The internal data structure functions are cleanly separated from the `main()` application logic, and variables are named descriptively to reflect their internal state.
*   `front`: Pointer tracking the head of the linked list.
*   `rear`: Pointer tracking the tail of the linked list.
*   `receiveCall(Call)`: Serves as the raw `enqueue` operation.
*   `answerCall()`: Serves as the raw `dequeue` operation.
*   `printFullQueue()`: Traverses the active nodes using a temporary reference to safely display the queue state without losing the actual `head` pointer.

## 4. Application Execution & Proof of Logic
*(Attach images left)*