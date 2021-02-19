/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

/**
 * Make a DefaultFormatter class implementing the NumberFormatter
 */
public class DefaultFormatter implements NumberFormatter{
    /**
     * Format an integer into a string
     * @param n The integer to be formatted
     * @return The formatted integer as a string
     */
    @Override
    public String format(int n){
        String str = Integer.toString(n);
        return str;
    }
}
