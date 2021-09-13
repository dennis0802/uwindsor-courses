/**
 * Developer: Dennis Dao
 * Date: Feb 3, 2021
 * version 1.0
 */

/**
 * Test the methods of the stack class and interface
 */
public class StackDemo {
    public static void main(String args[]){
        // Variable defintions
        Stack<Integer> myStack = new Stack<Integer>();
        // Additonal stack to test hitting limit
        Stack<Integer> anotherStack = new Stack<Integer>(4);
        
        System.out.println("Testing methods with myStack\n");
        if(myStack.isEmpty() == true){
            System.out.println("The stack is empty");
        }
        else{
            System.out.println("The stack is not empty");
        }
        myStack.push(10);
        myStack.push(12);
        myStack.push(4);
        myStack.push(7);
        myStack.push(13);
        myStack.push(240);
        System.out.println("The stack has " + myStack.size() + " elements");
        System.out.println("The element at the top of the stack is " + myStack.top());
        System.out.println("The stack contains: " + myStack.printStack());
        if(myStack.isFull() == true){
            System.out.println("The stack is full");
        }
        else{
            System.out.println("The stack is not full");
        }
        for(int i = 0; i < 6; i++){
            myStack.pop();
        }

        if(myStack.isEmpty() == true){
            System.out.println("The stack is empty");
        }
        else{
            System.out.println("The stack is not empty");
        }

        System.out.println("\n------------------------------------------");
        System.out.println("Testing methods with anotherStack\n");
        anotherStack.push(10);
        anotherStack.push(12);
        anotherStack.push(4);
        anotherStack.push(7);
        anotherStack.push(13);
        anotherStack.push(240);
        System.out.println("The stack has " + anotherStack.size() + " elements");
        System.out.println("The element at the top of the stack is " + anotherStack.top());
        System.out.println("The stack contains: " + anotherStack.printStack());

        if(anotherStack.isEmpty() == true){
            System.out.println("The stack is empty");
        }
        else{
            System.out.println("The stack is not empty");
        }

    }
    
}
