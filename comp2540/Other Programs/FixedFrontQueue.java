
// Flaw with this approach - it takes O(n) time to move all elements one to the left
// for all elements 0 to length-1
// arr[i] = arr[i+1];

public class FixedFrontQueue<E> {
    private int front = 0;
    private int back = 0;
    private E[] queue;
    private int maxSize = 1000;

    /**
     * Default constructor
     */
    public FixedFrontQueue(){
        queue = (E[]) new Object[maxSize];
    }

    /**
     * Second constructor - size specified queue
     * @param size The user-specified size of the queue
     */
    public FixedFrontQueue(int size){
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
            for(int i = 1; i < back-1; i++){
                queue[i-1] = queue[i];
            }
            back--;
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
