/**
 * Developer: Dennis Dao
 * Date: Feb 8, 2021
 * version 1.0
 */

/**
 * Make a Queue implementation class
 */
public class Queue<E>{
    // Instance variables
    private int maxSize = 1000;
    private int front = 0;
    private int back = 0;
    private E[] queue;

    /**
     * Default constructor
     */
    public Queue(){
        queue = (E[]) new Object[maxSize];
    }

    /**
     * Second constructor - size specified queue
     * @param size The user-specified size of the queue
     */
    public Queue(int size){
        this.maxSize = size;
        queue = (E[]) new Object[maxSize];
    }

    /**
     * Add a value to the queue
     * @param value The value to be added
     */
    public void enqueue(E value){
        if(!isFull()){
            queue[back] = value;
            back = (back+1)%maxSize;
        }
    }

    /**
     * Remove a value from the queue
     * @return The value to be removed
     */
    public E dequeue(){
        if(!isEmpty()){
            E value = queue[front];
            front = (front+1)%maxSize;
            return value;
        }
        return null;
    }

    /**
     * Get the element at the front of the queue
     * @return The element at the front, or -1 if the queue is empty.
     */
    public E front(){
        if(isEmpty()){
            return null;
        }
        return queue[front];
    }

    /**
     * Get the size of the queue
     * @return The size of the queue
     */
    public int size(){
        return (back - front + maxSize) % maxSize;
    }
    
    /**
     * Check whether the queue is empty
     * @return Whether the queue is empty
     */
    public Boolean isEmpty(){
        if(this.front == this.back){
            return true;
        }
        return false;
    }

    /**
     * Check whether the queue is full
     * @return Whether the queue is full
     */
    public Boolean isFull(){
        if((this.back + 1) % this.maxSize == this.front){
            return true;
        }
        return false;
    }
}