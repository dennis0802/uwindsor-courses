/**
 * Developer: Dennis Dao
 * Date: Oct 22, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;

/**
 * This class generates all prime numbers.
 */
public class PrimeGenerator{
    // Instance variables
    private int current;

    // Constructors
    /**
     * This is the default constructor
     */
    public PrimeGenerator(){
        this.current = 1;
    }

    /**
     * Calculates the next prime number.
     * @return the next prime number.
     */
    public int nextPrime(){
        // Helper variable to determine if a given number is prime.
        boolean prime;

        // Change current to 2 to check for the next prime since 1 is neither prime or not prime.
        if(current == 1){
            current++;
        }

        // Infinitely go up until the next prime number is found.
        for(int i = current; ; i++){
            prime = true;
            // Divide i by numbers up to half of i (ex. 25/2 = 12) to check if it is prime.
            for(int j = 2; j <= i/2; j++){
                if(i % j == 0){
                    prime = false;
                }
            }
            this.current++;
            // If the number was prime, return the number.
            if(prime == true){
                return i;
            }
        }
    }

    /** 
     * Check if n is a prime number
     * @param n to check whether it is prime or not
     * @return true if n is prime.
     */
    public static boolean isPrime(int n){
        // Divide n by numbers up to half of n (ex. 25/2 = 12) to check if it is prime.
        for(int i = 2; i <= n/2; i++){
            if(n % i == 0){
                return false;
            }
        }
        return true;
    }

    /**
     * Return the list of prime numbers to be printed up to number n.
     * @param n The number of prime numbers.
     * @return An array list of the prime numbers.
     */
    public ArrayList<Integer> getPrimeNumbers(int n){
        // List to store the list of prime numbers.
        ArrayList<Integer> primeNumbers = new ArrayList<Integer>();
        // Flag for prime numbers.
        boolean prime;

        // If 0 or 1 is inputted
        if(n == 0 || n == 1){
            return primeNumbers;
        }

        // Note: i starts at 2 as 0 and 1 are neither prime or not prime.
        // The prime numbers up to n
        for(int i = 2; i <= n; i++){
            prime = true;
            // Divide the prime number up to half of itself.
            for(int j = 2; j <= i/2; j++){
                // If the prime number divides with the numbers, the number is not prime.
                if(i % j == 0){
                    prime = false;
                }
            }
            // If the number is prime, add it to the list.
            if(prime == true){
                primeNumbers.add(i);
            }
        }
        return primeNumbers;
    }
}