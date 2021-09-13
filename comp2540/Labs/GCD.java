/**
 * Developer: Dennis Dao
 * Date: Jan 11, 2021
 * version 1.0
 */

// Imports
import java.util.Scanner;

/**
 * A class to implement the greater common divisor algorithm
 */
public class GCD{
    // Function to determine number of iterations
    /**
     * Get the number of iterations
     * @param m An integer
     * @param n An integer
     * @return The number of iterations done
     */
    public static int GCDIterations(int m, int n){
        // Helper variables to determine number of iterations
        int r, whileCount = 0;

        // Continue trying to divide until a divisble number is found
        while((r = m % n) != 0){
            whileCount++;
            m = n;
            n = r;
        }
        return whileCount;
    }

    public static void main(String args[]){
        // Variable definitions
        Scanner in = new Scanner(System.in);
        int m, n, r;

        // Ask the user for two positive integers.
        System.out.printf("Enter two positive integers: ");
        m = in.nextInt();
        n = in.nextInt();
        // If invalid input is received on either input
        while(m <= 0 || n <= 0){
            System.out.printf("One or both of the integers was not valid.\nEnter two positive integers: ");
            m = in.nextInt();
            n = in.nextInt();
        }
        // Get amount of iterations necessary
        int whileCount = GCDIterations(m, n);
        in.close();

        // Continue trying to divide until a divisble number is found
        while((r = m % n) != 0){
            m = n;
            n = r;
        }

        // Output result
        System.out.println("The GCD is " + n);
        System.out.println("The while loop is executed " + whileCount + " times");
    }
}