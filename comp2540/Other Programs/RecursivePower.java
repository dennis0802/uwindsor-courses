public class RecursivePower {
    static int recurPower(int x, int n){
        if(n == 0){
            return 1;
        }
        if(n == 1){
            return x;
        }

        if(n % 2 == 0){
            int y = recurPower(x, n/2);
            return y * y;
        }
        else{
            int y = recurPower(x, (n-1)/2);
            return y * y * x;
        }
    }

    public static void main(String args[]){
        System.out.println(recurPower(2, 3));
        System.out.println(recurPower(2, 4));
        System.out.println(recurPower(2, 1));
        System.out.println(recurPower(2, 0));
    }
}
