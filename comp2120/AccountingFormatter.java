/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

public class AccountingFormatter implements NumberFormatter{
    /**
     * Format an integer into a string in terms of accounting
     * @param n The integer to be formatted
     * @return The formatted integer as a string
     */
    @Override
    public String format(int n){
        // Helper variable
        String str = Integer.toString(n);

        // Read the number from left to right
        for(int i = 0; i < str.length(); i++){
            // If a negative sign is found, enclose the main number in brackets and leave the loop.
            if(str.charAt(i) == '-'){
                String mainNumber = str.substring(i+1);
                str = "("+ mainNumber + ")";
                break;
            }
        }
        return str;
    }
}
