public aspect HomeSecurityAspect{
    before() : call(void Home.exit()){
        System.out.println("Engaging");
    }

    after() : call(void Home.enter()){
        System.out.println("Disengaging");
    }
    
}