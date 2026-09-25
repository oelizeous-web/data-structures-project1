/**
 *
 * Identify each call uniquely using the given data below
 *
 */

public class Call {
    String callerName;
    String issueType;
    long timestamp;

    public Call(String callerName, String issueType) {
        this.callerName = callerName;
        this.issueType = issueType;
        this.timestamp = System.currentTimeMillis(); //time the call is made, represented from epoch
    }

    public String toString(){
        return "Caller Name: " + callerName + ", Issue Type: " + issueType + ", Timestamp: " + timestamp;
    }
}
