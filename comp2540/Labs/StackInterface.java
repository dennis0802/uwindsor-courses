/**
 * Developer: Dennis Dao
 * Date: Feb 9, 2021
 * version 1.1
 */

/**
 * Make a stack interface
 * 1.1 edit: Swapped to generics so stack can handle any type
 */
public interface StackInterface<E> {
    /**
     * Pop the last element from the stack
     * @return The popped element, or 0 if the stack is empty
     */
    E pop();

    /**
     * Push an element onto the stack
     * @param element The element to push
     */
    void push(E element);

    /**
     * Get the top of the stack
     */
    E top();

    /**
     * Get the size of the stack
     * @return The element at the top of the stack, or 0 if empty
     */
    int size();
    
    /**
     * Check if the stack is empty
     * @return Whether the stack is empty
     */
    Boolean isEmpty();

    /**
     * Check if the stack is full
     * @return Whether the stack is full
     */
    Boolean isFull();

    /**
     * Print the stack's elements
     * @return The stack's elements as a string
     */
    String printStack();
}
