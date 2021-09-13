/**
 * MCS Improved
 * Developer: Dennis Dao
 * Date: Jan 28, 2021
 * version 1.0
 */

/**
 * Class to run the improved algorithm of MCS
 */
public class MCS_Improved {
    public static void main(String args[]){
        // Variable defintions
        // NOTE - elements 1-5 are technically elements 0-4 with the array
        int[] a = {-2, 2, -2, -2, 3, 2};
        int i = 0, n = a.length, end = -1, start = end, sum = 0, maxSum = 0, iterations = 0;

        for(int j = 0; j < n; j++){
            sum = sum + a[j];
            if(sum > maxSum){
                maxSum = sum;
                start = i;
                end = j;
            }
            if(sum < 0){
                i = j + 1;
                sum = 0;
            }
            iterations++;
        }

        // No sum was found
        if(start == -1){
            System.out.println("Improved Algorithm for MCS:");
            for(int k = 0; k < a.length; k++){
                System.out.printf("%d, ", a[k]);
            }
            System.out.println("\n");

            System.out.println("No start index found");
            System.out.println("No end index found");
            System.out.println("Max Sum: " + maxSum);
            System.out.println("Iterations: " + iterations);
        }
        // A sum was found
        else{
            System.out.println("Improved Algorithm for MCS:");
            System.out.println("Array: ");
            for(int k = 0; k < a.length; k++){
                System.out.printf("%d, ", a[k]);
            }
            System.out.println("\n");
            System.out.println("Subsequence: ");
            for(int k = start; k <= end; k++){
                System.out.printf("%d, ", a[k]);
            }
            System.out.println("\n");
            System.out.println("Start index: " + start);
            System.out.println("End index: " + end);
            System.out.println("Max Sum: " + maxSum);
            System.out.println("Iterations: " + iterations);
        }
    }
}
