public class Main {
    public static void main(String[] args) {
        CallCenterQueue supportQueue = new CallCenterQueue();

        // Incoming calls
        supportQueue.receiveCall(new Call("Alice", "Billing Issue"));
        supportQueue.receiveCall(new Call("Bob", "Technical Support"));
        supportQueue.receiveCall(new Call("Charlie", "Password Reset"));

        //show the elements in wait
        supportQueue.printFullQueue();

        // Agents answering calls
        supportQueue.answerCall();
        supportQueue.answerCall();

        supportQueue.printFullQueue();

        // Another caller joins
        supportQueue.receiveCall(new Call("Diana", "Sales Inquiry"));

        // Agents finish the queue
        supportQueue.answerCall();
        supportQueue.answerCall();
        supportQueue.answerCall(); // Should indicate empty
    }
}