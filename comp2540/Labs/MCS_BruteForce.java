/**
 * MCS Brute Force
 * Developer: Dennis Dao
 * Date: Jan 28, 2021
 * version 1.0
 */

/**
 * Class to run the brute force algorithm of MCS
 */
public class MCS_BruteForce{
    public static void main(String args[]){
        // Variable defintions
        // NOTE - elements 1-5 are technically elements 0-4 with the array
        int[] a = {-2, 2, -2, -2, 3, 2};
        int start = 0, end = 0, maxSum = 0, n = a.length, iterations = 0;

        for(int i = 0; i < n; i++){
            int sum = 0;
            for(int j = i; j < n; j++){
                sum = sum + a[j];
                if(sum > maxSum){
                    maxSum = sum;
                    start = i;
                    end = j;
                }
                iterations++;
            }
        }

        // Output results
        System.out.println("Brute Force Algorithm for MCS:");
        System.out.println("Array: ");
        for(int i = 0; i < a.length; i++){
            System.out.printf("%d, ", a[i]);
        }
        System.out.println("\n");
        System.out.println("Subsequence: ");
        for(int i = start; i <= end; i++){
            System.out.printf("%d, ", a[i]);
        }
        System.out.println("\n");
        System.out.println("Start index: " + start);
        System.out.println("End index: " + end);
        System.out.println("Max Sum: " + maxSum);
        System.out.println("Iterations: " + iterations);
    }
}