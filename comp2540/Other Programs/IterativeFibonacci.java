public class IterativeFibonacci {
    static int fibonacci(int n){
        int fib1 = 0;
        int fib2 = 1;
        int temp;
        if(n == 0 || n == 1){
            return n;
        }

        for(int i = 0; i < n; i++){
            temp = fib1 + fib2;
            fib1 = fib2;
            fib2 = temp;
        }
        
        return fib1;
    }

    public static void main(String args[]){
        System.out.println(fibonacci(10));
    }
}
