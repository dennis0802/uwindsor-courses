/**
 * Developer: Dennis Dao
 * Date: Feb 4, 2021
 * version 1.0
 */

/**
 * Make a linked list stack class
*/
public class LinkedListStack<E> implements StackInterface<E>{
    // Instance variables
    private int maxSize = 1000;
    private LinkedList<E> stack = new LinkedList<E>();

    @Override
    /**
     * Push an element onto the stack
     * @param element The element to push
     */
    public void push(E element){
        if(isFull() == false){
            stack.insert(stack, element);
        }
    }

    @Override
    /**
     * Pop an element off the stack
     * @return The popped element, or 0 if the stack is empty
     */
    public E pop(){
        if(isEmpty() == false){
            E element = top();
            // Only the head remains
            if(stack.getNumElements(stack) == 1){
                stack.deleteAtHead(stack);
            }
            // There is more than 1 element
            else{
                stack.deleteAtEnd(stack);
            }
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
            return stack.getLastElement(stack);
        }
        return null;
    }

    @Override
    /**
     * Get the size of the stack
     * @return The number of elements in the stack (1 added if not empty to compensate for array implementation element 0)
     */
    public int size(){
        return stack.getNumElements(stack);
    }

    @Override
    /**
     * Check if the stack is empty
     * @return Whether the stack is empty
     */
    public Boolean isEmpty(){
        if(stack.getNumElements(stack) == 0){
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
        if(stack.getNumElements(stack) >= maxSize){
            return true;
        }
        return false;    
    }

    /**
     * Print the elements of the stack
     * @return The elements of the stack as a string
     */
    public String printStack(){
        return stack.getElements(stack);
    }
}