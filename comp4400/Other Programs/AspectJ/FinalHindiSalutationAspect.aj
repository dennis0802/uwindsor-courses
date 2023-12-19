public aspect FinalHindiSalutationAspect {
    pointcut sayToPerson(String person, String message) : call(void FinalMessageCommunicator.deliver(String, String)) && args(person, message);
    void around(String person, String message) : sayToPerson(person, message) { 
        proceed("Hello " + person, "your message is: " + message);
    }
}
