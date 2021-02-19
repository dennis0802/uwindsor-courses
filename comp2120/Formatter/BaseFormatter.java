/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.math.BigInteger;
import java.util.ArrayList;

/**
 * Make the BaseFormatter class implementing the NumberFormatter interface
 */
public class BaseFormatter implements NumberFormatter{
    // Instance variables
    private int base;

    // Constructors
    /**
     * This is the default constructor
     * @param base The base to convert the numbers to
     */
    public BaseFormatter(int base){
        this.base = base;
    }

    // Methods
    /**
     * Get the number base of the formatter decimal (10), hexadecimal (16), binary (2), octal (8)...)
     * @return The number base of the formatter
     */
    public int getBase() {
        return base;
    }

    /**
     * Format the integer into a new base, then into a string
     * @param n The integer to be formatted
     * @return The formatted integer as a string
     */
    @Override
    public String format(int n){
        // Declare variables as BigIntegers since overflow can occur depending on original number length
        // ex. 1000000
        BigInteger base = new BigInteger(Integer.toString(this.base));
        BigInteger oldNum = new BigInteger(Integer.toString(n));
        BigInteger newNum = new BigInteger("0");
        BigInteger rem;
        BigInteger temp = new BigInteger("1");
        BigInteger temp2 = new BigInteger("10");

        // If the base is 11-16, the digits will be stored in the arraylist, then outputted to the string
        String highBase = "";
        ArrayList<String> characters = new ArrayList<String>();
        // Flag for a negative number
        boolean negative = false;

        if(oldNum.intValue() < 0){
            negative = true;
        }

        // Check validity of base
        if(this.base <= 1 || this.base > 16){
            return "Invalid base";
        }
        // If the entered base is 10, no need to convert
        else if(this.base == 10){
            String str = Integer.toString(n);
            return str;
        }

        // Bases 2-9
        if(this.base < 10){
            // Go through the process of converting decimal to the new base
            while(oldNum.intValue() != 0){
                rem = oldNum.remainder(base);
                oldNum = oldNum.divide(base);
                newNum = newNum.add(rem.multiply(temp));
                temp = temp.multiply(temp2);
            }
            // Format the number into a string and return
            String str = newNum.toString();
            return str;
        }
        // Bases 11-16
        else{
            while(oldNum.intValue() != 0){
                // Go through the process of convertind decimal to the new base
                rem = oldNum.remainder(base);
                oldNum = oldNum.divide(base);

                // Check the absolute value of each digit and see if it needs to be a letter or a number
                if(rem.abs().intValue() >= 0 && rem.abs().intValue() < 10){
                    characters.add(rem.abs().toString());
                }
                else if(rem.abs().intValue() == 10){
                    characters.add("A");
                }
                else if(rem.abs().intValue() == 11){
                    characters.add("B");
                }
                else if(rem.abs().intValue() == 12){
                    characters.add("C");
                }
                else if(rem.abs().intValue() == 13){
                    characters.add("D");
                }
                else if(rem.abs().intValue() == 14){
                    characters.add("E");
                }
                else if(rem.abs().intValue() == 15){
                    characters.add("F");
                }
            }

            // If the number was negative, stick a negative sign at the start
            if(negative == true){
                highBase += "-";
            }
            // Go through the array backwards to get the new number.
            for(int i = characters.size() - 1; i >= 0; i--){
                highBase += characters.get(i);
            }
            return highBase;
        }
    }
}
