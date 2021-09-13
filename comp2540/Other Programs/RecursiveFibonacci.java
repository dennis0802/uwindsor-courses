public class RecursiveFibonacci {
    static int recurFib(int n){
        if(n == 0 || n == 1){
            return n;
        }
        else{
            return recurFib(n-1) + recurFib(n-2);
        }
    }

    public static void main(String args[]){
        System.out.println(recurFib(10));
    }
}
