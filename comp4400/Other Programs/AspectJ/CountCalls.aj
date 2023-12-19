public aspect CountCalls{
    int count = 0;

    before() : call (* foo(..)){
        count++;
    }

    after() : execution (public static * main(..)){
        System.out.println("Count = " + count);
    }
}