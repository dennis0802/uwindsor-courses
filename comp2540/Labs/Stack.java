/**
 * Developer: Dennis Dao
 * Date: Feb 9, 2021
 * version 1.1
 */

/**
 * Make a stack class implementing an interface
 * 1.1 edit: Swapped to generics so stack can handle any type
 */
public class Stack<E> implements StackInterface<E>{
    // Instance variables
    private int index = -1;
    private int maxSize = 1000;
    private E[] stack;

    /**
     * Default constructor - size limit 1000 elements
     */
    public Stack(){
        this.stack = (E[]) new Object [maxSize];
    }

    /**
     * Second constructor - specify a specific stack size limit
     * @param size A user-specified stack size limit
     */
    public Stack(int size){
        this.maxSize = size;
        this.stack = (E[]) new Object [maxSize];
    }

    @Override
    /**
     * Push an element onto the stack
     * @param element The element to push
     */
    public void push(E element){
        if(isFull() == false){
            this.index++;
            this.stack[this.index] = element;
        }
    }

    @Override
    /**
     * Pop an element off the stack
     * @return The popped element, or 0 if the stack is empty
     */
    public E pop(){
        E element;
        if(isEmpty() == false){
            element = top();
            this.index--;
            return element;
        }
        return null;
    }

    @Override
    /**
     * Get the top of the stack
     * @return The element at the top of the stack, or 0 if empty
     */
    public E top(){
        if(isEmpty() == false){
            return this.stack[this.index];
        }
        return null;
    }

    @Override
    /**
     * Get the size of the stack
     * @return The number of elements in the stack (1 added if not empty to compensate for array implementation element 0)
     */
    public int size(){
        if(isEmpty() == true){
            return 0;
        }
        return this.index + 1;
    }

    @Override
    /**
     * Check if the stack is empty
     * @return Whether the stack is empty
     */
    public Boolean isEmpty(){
        if(this.index == -1){
            return true;
        }
        return false;
    }

    @Override
    /**
     * Check if the stack is full
     * @return Whether the stack is full
     */
    public Boolean isFull(){
        if(this.index >= this.maxSize - 1){
            return true;
        }
        return false;    
    }

    @Override
    /**
     * Print the stack's elements
     * @return The stack's elements as a string
     */
    public String printStack(){
        String message = "";
        for(int i = 0; i <= this.index; i++){
            if(i != this.index){
                message += this.stack[i] + ", ";
            }
            else{
                message += this.stack[i];
            }
        }
        return message;
    }
}