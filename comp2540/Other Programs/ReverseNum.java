public class ReverseNum {
    static void printReverse(int num){
        System.out.printf("%d", num%10);
        if(num >= 10){
            printReverse(num / 10);
        }
    }

    public static void main(String args[]){
        printReverse(1234);
    }
}
