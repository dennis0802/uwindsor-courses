/**
 * Developer: Dennis Dao
 * Date: Feb 9, 2021
 * version 1.0
 */

/**
 * Creates a customer class to work with the Bank simulation classes
 */
public class Customer{
    // Instance variables
    private int serviceTime;
    private int arrivalTime;

    /**
     * Constructor with specified service time
     * @param serviceTime The amount of units the customer needs to be serviced
     * @param arrivalTime The time the customer arrived
     */
    public Customer(int serviceTime, int arrivalTime){
        this.serviceTime = serviceTime;
        this.arrivalTime = arrivalTime;
    }

    /**
     * Get the amount of service time
     * @return The amount of service time
     */
    public int getServiceTime(){
        return this.serviceTime;
    }

    /**
     * Get the arrival time
     * @return The arrival time
     */
    public int getArrivalTime(){
        return this.arrivalTime;
    }
}