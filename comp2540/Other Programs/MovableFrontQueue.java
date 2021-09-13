
// Flaw with this approach - O(1) to dequeue but large space complexity and waste (left are unused, lots of right needed)

public class MovableFrontQueue<E> {
    private int front = 0;
    private int back = 0;
    private E[] queue;
    private int maxSize = 1000;

    /**
     * Default constructor
     */
    public MovableFrontQueue(){
        queue = (E[]) new Object[maxSize];
    }

    /**
     * Second constructor - size specified queue
     * @param size The user-specified size of the queue
     */
    public MovableFrontQueue(int size){
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
            back++;
        }
    }

    /**
     * Remove a value from the queue
     * @return The value to be removed
     */
    public E dequeue(){
        if(!isEmpty()){
            E value = queue[front];
            front++;
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
        return back-front;
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
        if(back == this.maxSize){
            return true;
        }
        return false;
    }
}
