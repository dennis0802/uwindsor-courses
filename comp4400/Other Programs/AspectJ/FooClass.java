public class FooClass {
    void foo(){}
    void bar(){}

    public static void main(String args[]){
        FooClass c1 = new FooClass();
        FooClass c2 = new FooClass();

        c1.foo();
        c1.foo();
        c1.bar();
        c2.foo();
        c2.foo();
        c2.foo();
        c2.foo();
        c2.bar();
        System.out.println("Done");
    }
}
