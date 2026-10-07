import java.util.Scanner;

/* Call Centre Support Queue
   Calls are answered first come, first served (FIFO). All pointer handling
   (front, rear, nodes) lives in CallCenterQueue. */
public class Main {

    public static void main(String[] args) {
        CallCenterQueue supportQueue = new CallCenterQueue();
        Scanner input = new Scanner(System.in);
        int choice = -1;

        do {
            System.out.println("\n=== Call Centre Support Queue ===");
            System.out.println("1. Receive a call");
            System.out.println("2. Answer next call");
            System.out.println("3. View next caller");
            System.out.println("4. Show waiting calls");
            System.out.println("0. Exit");
            System.out.print("Choice: ");

            if (!input.hasNextLine()) {          // input ended, so stop cleanly
                System.out.println("\nInput ended. Goodbye!");
                break;
            }

            try {
                choice = Integer.parseInt(input.nextLine().trim());
            } catch (NumberFormatException e) {
                System.out.println("Please enter a number.");
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: receiveNewCall(supportQueue, input); break;
                case 2: supportQueue.answerCall();           break;
                case 3: viewNextCaller(supportQueue);        break;
                case 4: supportQueue.printFullQueue();       break;
                case 0: System.out.println("Goodbye!");      break;
                default: System.out.println("Invalid choice.");
            }
        } while (choice != 0);

        input.close();
    }

    // ask the user for the caller's details, then add the call to the back of the queue
    private static void receiveNewCall(CallCenterQueue queue, Scanner input) {
        System.out.print("Caller name: ");
        if (!input.hasNextLine()) return;
        String name = input.nextLine().trim();

        System.out.print("Issue type: ");
        if (!input.hasNextLine()) return;
        String issue = input.nextLine().trim();

        if (name.isEmpty() || issue.isEmpty()) {
            System.out.println("WARNING: Name and issue type cannot be blank. Call not added.");
            return;
        }
        queue.receiveCall(new Call(name, issue));
    }

    // view the caller at the front without removing them
    private static void viewNextCaller(CallCenterQueue queue) {
        Call next = queue.viewFront();           // prints a warning itself if the queue is empty
        if (next != null) {
            System.out.println("Next in line: " + next.callerName + " - " + next.issueType);
        }
    }
}