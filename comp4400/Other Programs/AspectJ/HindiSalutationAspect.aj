//Listing 2.4 HindiSalutationAspect.java

public aspect HindiSalutationAspect {
    pointcut sayToPerson(String person)
	: call(void MessageCommunicator.deliver(String, String))
	&& args(person, String);

    void around(String person) : sayToPerson(person) {
	    proceed(person + " -ji");
    }
}