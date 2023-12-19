public aspect With{
    before() : call (void Hello.greeting()){
        System.out.print("AOP>> ");
    }
}