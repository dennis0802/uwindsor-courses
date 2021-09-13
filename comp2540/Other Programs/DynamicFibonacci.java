public class DynamicFibonacci {
    static int fibonacci(int n){
        if(n == 0 || n == 1){
            return n;
        }
        else{
            int fib2 = 0, fib1 = 1, fib = 0;
            for(int i = 2; i <= n; i++){
                fib = fib1 + fib2;
                fib2 = fib1;
                fib1 = fib;
            }
            return fib;
        }
    }

    public static void main(String args[]){
        System.out.println(fibonacci(10));
    }
}
