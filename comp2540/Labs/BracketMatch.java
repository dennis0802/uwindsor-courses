/**
 * Developer: Dennis Dao
 * Date: Feb 3, 2021
 * version 1.0
 */

/**
 * Implement an array-based stack
 */
public class BracketMatch{
    public static void main(String args[]){
        // Variable defintions
        String input = "((((()(";
        Stack<Character> brackets = new Stack<Character>();
        // Indices stack to store position of opening brackets if required for error messages
        Stack<Integer> indices = new Stack<Integer>();
        int rightBracketPos = 0;
        Boolean unmatchedFlag = false;

        System.out.println("Bracket input: " + input);
        // Scan the string
        for(int i = 0; i < input.length(); i++){
            // Opening bracket found
            if(input.charAt(i) == '('){
                brackets.push('(');
                indices.push(i);
            }
            // Closing bracket found and stack is not empty
            else if(input.charAt(i) == ')' && brackets.isEmpty() == false){
                brackets.pop();
                indices.pop();
            }
            // Closing bracket found and stack is empty
            else if(input.charAt(i) == ')' && brackets.isEmpty() == true){
                unmatchedFlag = true;
                rightBracketPos = i;
                System.out.println("Mismatched closing bracket at position " + rightBracketPos);
            }

            // End of the input but the stack still has elements
            if(i == input.length()-1 && brackets.isEmpty() == false){
                for(int j = 0; j < brackets.size(); j++){
                    unmatchedFlag = true;
                    System.out.println("Mismatched opening bracket at position " + indices.pop());
                }
            }
        }

        // All brackets matched
        if(brackets.size() == 0 && brackets.isEmpty() == true && unmatchedFlag == false){
            System.out.println("All brackets matched");
        }

    }
}