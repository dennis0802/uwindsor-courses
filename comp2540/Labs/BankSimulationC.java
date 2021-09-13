/**
 * Developer: Dennis Dao
 * Date: Feb 8, 2021
 * version 1.0
 */

/**
 * Make a bank simulation class (3 tellers, three lines)
 */
public class BankSimulationC {
    /**
     * Function to help determine the queue the customer should go to
     * Goes to the smallest queue unless it is a special case
     * @param queue1 A queue
     * @param queue2 A queue
     * @param queue3 A queue
     * @param teller1 A teller
     * @param teller2 A teller
     * @param teller3 A teller
     * @return The queue the customer should go to
     */
    static Queue<Customer> minQueue(Queue<Customer> queue1, Queue<Customer> queue2, Queue<Customer> queue3, Teller teller1, Teller teller2, Teller teller3){
        Queue<Customer> smallest = queue1;
        int queueNum = 1;

        if(queue2.size() < smallest.size()){
            smallest = queue2;
            queueNum = 2;
        }
        if(queue3.size() < smallest.size()){
            smallest = queue3;
            queueNum = 3;
        }

        // Special case: all 3 queues are empty - check which teller is free
        if(queue1.isEmpty() && queue2.isEmpty() && queue3.isEmpty()){
            if(teller1.getWorkTime() == 0){
                System.out.println("Customer went to queue 1");
                return queue1;
            }
            else if(teller2.getWorkTime() == 0){
                System.out.println("Customer went to queue 2");
                return queue2;
            }
            else if(teller3.getWorkTime() == 0){
                System.out.println("Customer went to queue 3");
                return queue3;
            }
        }
        
        System.out.println("Customer went to queue " + queueNum);
        return smallest;
    }

    public static void main(String args[]){
        // Variable definitions
        int arrivalCountdown = 0, customersServed = 0, customersGenerated = 1, i = 0, m = -1, clock = 0;
        int[] waitingTimes = new int[100];
        double avg = 0;

        Queue<Customer> teller1Line = new Queue<Customer>(101), teller2Line = new Queue<Customer>(101), teller3Line = new Queue<Customer>(101);
        Teller teller1 = new Teller(), teller2 = new Teller(), teller3 = new Teller();

        int [] serviceTimes = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        int [] arrivalTimes = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        while(customersServed != 100){
            // Customer arrives
            if(arrivalCountdown == 0 && customersGenerated != 101){ 
                m++;
                arrivalCountdown = arrivalTimes[m];
                int service = serviceTimes[m];

                minQueue(teller1Line, teller2Line, teller3Line, teller1, teller2, teller3).enqueue(new Customer(service, clock));
                System.out.println("Current time: " + clock + " unit(s)");
                System.out.println("Teller Status: (1): " + teller1.getWorkTime() + " (2): " + teller2.getWorkTime() + " (3): " + teller3.getWorkTime());
                System.out.println("Customer " + customersGenerated + " arrived with service time of " + service + " unit(s) required.");
                if(customersGenerated + 1 != 101){
                    System.out.println("Time of " + arrivalCountdown + " unit(s) before next customer arrives.\n");
                }
                customersGenerated++;
            }

            // Dequeue waiting customers in each line
            if(teller1.getWorkTime() == 0 && teller1Line.front() != null){
                Customer patron = teller1Line.dequeue();
                teller1.setWorkTime(patron.getServiceTime());
                waitingTimes[i] = clock - patron.getArrivalTime();
                i++;
            }
            if(teller2.getWorkTime() == 0 && teller2Line.front() != null){
                Customer patron = teller2Line.dequeue();
                teller2.setWorkTime(patron.getServiceTime());
                waitingTimes[i] = clock - patron.getArrivalTime();
                i++;
            }
            if(teller3.getWorkTime() == 0 && teller3Line.front() != null){
                Customer patron = teller3Line.dequeue();
                teller3.setWorkTime(patron.getServiceTime());
                waitingTimes[i] = clock - patron.getArrivalTime();
                i++;
            }

            // Update time status
            if(teller1.getWorkTime() > 0){
                teller1.decrementWorkTime();
                if(teller1.getWorkTime() == 0){
                    customersServed++;
                }
            }
            if(teller2.getWorkTime() > 0){
                teller2.decrementWorkTime();;
                if(teller2.getWorkTime() == 0){
                    customersServed++;
                }
            }
            if(teller3.getWorkTime() > 0){
                teller3.decrementWorkTime();
                if(teller3.getWorkTime() == 0){
                    customersServed++;
                }
            }
            arrivalCountdown--;
            clock++;
        }

        // Get the average waiting time
        System.out.println("\nService complete.");
        System.out.println("Service took " + clock + " unit(s)");
        System.out.println("Wait times: ");
        for(int j = 0; j < waitingTimes.length; j++){
            if(j != waitingTimes.length-1){
                System.out.printf(waitingTimes[j] + ", ");
            }
            else{
                System.out.printf("%d", waitingTimes[j]);
            }
            avg += waitingTimes[j];
        }
        avg /= (double)waitingTimes.length;
        System.out.println("\n\nAverage wait time in the queue: " + avg + " unit(s) of time");
    }    
}
