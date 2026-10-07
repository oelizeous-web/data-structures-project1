public class CallCenterQueue {
    private CallNode front;
    private CallNode rear;
    private int size;

    public CallCenterQueue(){
        this.front = null;  //Track the first on the queue
        this.rear = null;  //Track the last in the queue
        this.size = 0; //Track calls in the queue
    }

    //checks whether any calls are waiting (an empty queue has no front node)
    public boolean isEmpty(){
        return this.front == null;
    }

    //adding a new call to the queue at the back
    public void receiveCall(Call newCall){
        CallNode newNode = new CallNode(newCall);
        if (this.isEmpty()) {

            /*the front is the same as the back since its the first element being added
            since the queue was empty */
            this.front = this.rear = newNode;
        } else {
            this.rear.next = newNode;
            this.rear = newNode;
        }
        this.size++;
        System.out.println("Received: " + newCall.callerName + " | Queue size: " + this.size);
    }

    //view (peek at) the caller at the front WITHOUT removing them from the queue
    public Call viewFront(){
        if (this.isEmpty()) {
            System.out.println("No calls in the queue.");
            return null; //nothing to view
        }
        return this.front.call;
    }

    public void answerCall(){
        if (this.isEmpty()) {
            System.out.println("No calls in the queue.");
            return; //exit the method answerCall since none
        }

        //point to the front node to be removed and return its call
        Call answeredCall = this.front.call;
        this.front = this.front.next;

        // If the front becomes null, then the queue is empty, so set rear to null as well
        if (this.front == null) {
            this.rear = null;
        }
        this.size--;
        System.out.println("Answered: " + answeredCall.callerName + " | Queue size: " + this.size);
    }

    public void printFullQueue() {
        if (this.isEmpty()) {
            System.out.println("The queue is currently empty.");
            return;
        }

        System.out.println("\n--- Current Call Queue (" + size + " waiting) ---");

        // 1. Create a temporary pointer starting at the front
        //do not use this.front directly as it might just be deleting people in the queue
        CallNode current = this.front;
        int position = 1;

        // 2. Walk through the list until we run out of nodes
        while (current != null) {
            System.out.println(position + ". " + current.call.callerName + " - " + current.call.issueType);

            // Move the temporary pointer to the next person in line
            current = current.next;
            position++;
        }
        System.out.println("----------------------------------------\n");
    }
}