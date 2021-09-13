/**
 * Developer: Dennis Dao
 * Date: Mar 1, 2021
 * version 1.0
 */

// Imports
import java.util.Random;

/**
 * Run the LCS algorithm
 */
public class LCS{
    /**
     * Get the length of the LCS
     * @param x A string
     * @param y A string
     * @param m The size of string x
     * @param n The size of string y
     * @return The length of the LCS
     */
    static int lcs(char[] x, char[] y, int m, int n){
        int[][] subsequence = new int[m+1][n+1]; 

        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                if(i == 0 || j == 0){
                    subsequence[i][j] = 0;
                }
                else if(x[i-1] == y[j-1]){
                    subsequence[i][j] = subsequence[i-1][j-1] + 1;
                }
                else{
                    subsequence[i][j] = Math.max(subsequence[i-1][j], subsequence[i][j-1]);
                }
            }
        }
        return subsequence[m][n];
    }

    public static void main(String args[]){
        Random in = new Random();

        // Run 100 pairs of strings (generated as char arrays) with varying lengths and varying characters
        for(int i = 0; i < 100; i++){
            int size1 = in.nextInt(100)+1;
            int size2 = in.nextInt(100)+1;
            char[] c1 = new char[size1];
            char[] c2 = new char[size2];

            // (in.nextInt(6) + 13) * 5 for uppercase
            // ((in.nextInt(6)+19)*5) + 2 for lowercase 
            for(int j = 0; j < size1; j++){
                int character = ((in.nextInt(6) + 19) * 5) + 2;
                c1[j] = (char)character;
            }

            for(int k = 0; k < size2; k++){
                int character = ((in.nextInt(6) + 19) * 5) + 2;
                c2[k] = (char)character;
            }

            System.out.println("Compared strings: " + new String(c1) + " and " + new String(c2));
            System.out.println("The length of the LCS is " + lcs(c1, c2, size1, size2));
        }
    }
}