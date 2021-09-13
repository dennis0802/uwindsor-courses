/**
 * Developer: Dennis Dao
 * Date: Feb 4, 2021
 * version 1.0
 */

/**
 * Test the methods of a linked list stack - same instructions as the StackDemo.java file
 * but the stack uses a linked list.
 */
public class LinkedListStackDemo{
    public static void main(String args[]){
        LinkedListStack<Integer> myStack = new LinkedListStack<Integer>();

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
        System.out.println("The stack contains: " + myStack.printStack());

        if(myStack.isEmpty() == true){
            System.out.println("The stack is empty");
        }
        else{
            System.out.println("The stack is not empty");
        }        
    }
}