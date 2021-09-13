/**
 * Developer: Dennis Dao
 * Date: Feb 8, 2021
 * version 1.0
 */

/**
 * Make a bank simulation class (3 tellers, one line)
 */
public class BankSimulationB {

    public static void main(String args[]){
        // Variable definitions
        int arrivalCountdown = 0, customersServed = 0, customersGenerated = 1, i = 0, m = -1, clock = 0;
        int[] waitingTimes = new int[100];
        double avg = 0;
        Queue<Customer> bankQueue = new Queue<Customer>(101);
        Teller teller1 = new Teller(), teller2 = new Teller(), teller3 = new Teller();

        int [] serviceTimes = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
        int [] arrivalTimes = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        while(customersServed != 100){
            // Customer arrives
            if(arrivalCountdown == 0 && customersGenerated != 101){ 
                m++;
                arrivalCountdown = arrivalTimes[m];
                int service = serviceTimes[m];
                bankQueue.enqueue(new Customer(service, clock));
                System.out.println("Current time: " + clock + " unit(s)");
                System.out.println("Teller Status: (1):" + teller1.getWorkTime() + " (2):" + teller2.getWorkTime() + " (3)" + teller3.getWorkTime());
                System.out.println("Customer " + customersGenerated + " arrived with service time of " + service + " unit(s) required.");
                System.out.println("The queue contains: " + bankQueue.size() + " customers");
                if(customersGenerated + 1 != 101){
                    System.out.println("Time of " + arrivalCountdown + " unit(s) before next customer arrives.\n");
                }
                customersGenerated++;
            }
            
            // Dequeue if available
            if(!bankQueue.isEmpty()){
                if(teller1.getWorkTime() == 0){
                    Customer patron = bankQueue.dequeue();
                    teller1.setWorkTime(patron.getServiceTime());
                    waitingTimes[i] = clock - patron.getArrivalTime();
                    i++;
                }
                if(teller2.getWorkTime() == 0 && bankQueue.front() != null){
                    Customer patron = bankQueue.dequeue();
                    teller2.setWorkTime(patron.getServiceTime());
                    waitingTimes[i] = clock - patron.getArrivalTime();
                    i++;
                }
                if(teller3.getWorkTime() == 0 && bankQueue.front() != null){
                    Customer patron = bankQueue.dequeue();
                    teller3.setWorkTime(patron.getServiceTime());
                    waitingTimes[i] = clock - patron.getArrivalTime();
                    i++;
                }
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
