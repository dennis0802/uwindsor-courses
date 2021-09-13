/**
 * Developer: Dennis Dao
 * Date: Feb 3, 2021
 * version 1.0
 */

// Imports
import java.util.Scanner;

/**
 * Class to make a stack based postfix calculator
 */
public class PostFix {
    public static void main(String args[]){
        // Variable defintions
        Stack<Integer> postFixCalc = new Stack<Integer>();
        Scanner in = new Scanner(System.in);
        int result = 0;
        String exprInput = "";
        String input = "";

        // Get the input / expression to evaluate
        System.out.println("Enter a postfix expression (whole expression on one line or one item of the expression per line)");
        System.out.println("Enter an input containing '=' to stop input");
        do{
            exprInput = in.next();
            input += exprInput + " ";
        } while (!exprInput.contains("="));
        in.close();

        // Read the expression and calculate
        System.out.println("Evaluating: " + input);
        for(int i = 0; i < input.length(); i++){
            // Multiplication
            if(input.charAt(i) == '*'){
                // Too few operands
                if(postFixCalc.size() <= 1){
                    System.out.println("Too few operands to perform multiplication.");
                    return;
                }
                postFixCalc.push(postFixCalc.pop()*postFixCalc.pop());
            }

            // Addition
            else if(input.charAt(i) == '+'){
                // Too few operands
                if(postFixCalc.size() <= 1){
                    System.out.println("Too few operands to perform addition.");
                    return;
                }
                postFixCalc.push(postFixCalc.pop()+postFixCalc.pop());
            }

            // Negative numbers or subtraction
            else if(input.charAt(i) == '-'){
                i++;
                // Check if a negative number
                if(Character.isDigit(input.charAt(i))){
                    // Helper variable to form the number
                    int num = 0;
                    // Read all digits
                    for(; Character.isDigit(input.charAt(i)) != false; i++){
                        num = num * 10 + (input.charAt(i) - '0');
                    }
                    postFixCalc.push(num * -1);                
                }
                // Input was a minus sign operation
                // Decrement i to avoid errors with the for loop.
                // Too few operands
                else if(postFixCalc.size() <= 1){
                    i--;
                    System.out.println("Too few operands to perform subtraction.");
                    return;
                }
                else{
                    i--;
                    postFixCalc.push(postFixCalc.pop()-postFixCalc.pop());    
                }        
            }

            // Equals operation
            else if(input.charAt(i) == '='){
                if(postFixCalc.size() > 1){
                    System.out.println("The stack is not empty, the result cannot be outputted");
                    return;
                }
                result = postFixCalc.pop();
                break;
            }

            // An integer - subtract by character 0 to avoid placing the ASCII value
            // due to reading the string char by char
            else if(Character.isDigit(input.charAt(i))){
                // Helper variable to form the number
                int num = 0;
                // Read all digits
                for(; Character.isDigit(input.charAt(i)) != false; i++){
                    num = num * 10 + (input.charAt(i) - '0');
                }
                postFixCalc.push(num);
            }

            // Ignore spaces
            else if(input.charAt(i) == ' '){
                continue;
            }

            // Invalid characters
            else{
                System.out.println("The expression has an invalid character");
                return;
            }
        }

        // If anything remains in the stack, the input was invalid (ie. inputting just numbers and no operations)
        if(postFixCalc.isEmpty() == false){
            System.out.println("The input was invalid - there were no operations.");
            return;
        }
        System.out.println("The result is " + result);
    }
}
