/**
 * Developer: Dennis Dao
 * Date: Feb 8, 2021
 * version 1.0
 */

/**
 * Test the methods of the Queue implementation
 */
public class QueueDemo {
    public static void main(String args[]){
        Queue<Integer> myQueue = new Queue<Integer>(10);

        if(myQueue.isEmpty()){
            System.out.println("The queue is empty");
        }
        else{
            System.out.println("The queue is not empty");
        }

        if(myQueue.isFull()){
            System.out.println("The queue is full");
        }
        else{
            System.out.println("The queue is not full");
        }
        myQueue.enqueue(10);
        myQueue.enqueue(11);
        myQueue.enqueue(12);
        myQueue.enqueue(13);
        myQueue.enqueue(14);
        myQueue.enqueue(15);
        myQueue.enqueue(16);
        myQueue.enqueue(17);
        myQueue.enqueue(18);
        myQueue.enqueue(19);

        if(myQueue.isFull()){
            System.out.println("The queue is full");
        }
        else{
            System.out.println("The queue is not full");
        }

        System.out.println("The queue contains " + myQueue.size() + " elements");

        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();
        System.out.println("At the front of the queue: " + myQueue.front());
        myQueue.dequeue();

        if(myQueue.isFull()){
            System.out.println("The queue is full");
        }
        else{
            System.out.println("The queue is not full");
        }

        if(myQueue.isEmpty()){
            System.out.println("The queue is empty");
        }
        else{
            System.out.println("The queue is not empty");
        }
    }
}
