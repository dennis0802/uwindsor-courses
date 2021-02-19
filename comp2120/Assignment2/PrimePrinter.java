/**
 * Developer: Dennis Dao
 * Date: Oct 22, 2020
 * Student Number: 110010116
 */

import java.util.Scanner;

/**
 * This class tests the methods of the PrimeGenerator class
 */
public class PrimePrinter {
    /**
     * Test the methods
     * @param args not used.
     */
    public static void main(String[] args){
        // Read the user's input.
        Scanner in = new Scanner(System.in);
        System.out.printf("Enter upper limit: ");
        int limit = in.nextInt();

        PrimeGenerator myGenerator = new PrimeGenerator();

        // Get the prime numbers up to the upper limit
        // ex. 10 -> 2,3,5,7
        System.out.println("The prime numbers up to " + limit + ".");
        for(int nums : myGenerator.getPrimeNumbers(limit)){
            System.out.printf("%d, ", nums);
        }
        System.out.println();

        if(PrimeGenerator.isPrime(limit) == true){
            System.out.printf("The upper limit %d is prime.\n", limit);
        }
        else{
            System.out.printf("The upper limit %d is not prime.\n", limit);
        }

        System.out.println("The first " + limit + " prime numbers.");
        for(int i = 1; i <= limit; i++){
            System.out.printf("%d, ", myGenerator.nextPrime());
        }

        // Close the scanner.
        in.close();
    }
}
