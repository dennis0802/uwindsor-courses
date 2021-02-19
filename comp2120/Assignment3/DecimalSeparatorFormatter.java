/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

/**
 * This makes a DecimalSeparatorFormatter class implementing NumberFormatter
 */
public class DecimalSeparatorFormatter implements NumberFormatter{
    /**
     * Format an integer into a string
     * @param n The integer to be formatted
     * @return The formatted integer as a string
     */
    @Override
    public String format(int n){
        // Helper variables
        int count = 0;
        String str = Integer.toString(n);

        // Read the number from right to left
        for(int i = str.length() - 1; i >= 0; i--){
            // If the next character is a negative sign, ignore it and leave the loop
            if(str.charAt(i) == '-'){
                break;
            }
            count++;
            // If 3 digits have passed, add a comma to format with decimal separators
            if(count == 3){
                // Get both sections as substrings 
                // (the section before where the comma should be and the section after where the comma should be)
                String preComma = str.substring(0, i);
                String postComma = str.substring(i);
                // Merge the two strings
                str = preComma + "," + postComma;
                // Reset counter
                count = 0;
            }
        }
        return str;
    }
 }