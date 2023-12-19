//Listing 2.3 MannersAspect.java
public aspect MannersAspect {
    pointcut deliverMessage() : call(* deliver(..));

    before() : deliverMessage() {
	    System.out.print("Hello! ");
    }
}
