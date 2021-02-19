/**
 * Developer: Dennis Dao
 * Date: Dec 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.Queue;
import java.util.LinkedList;
import java.util.ArrayList;

public class Airport {
    // Instance variables
    Queue<String> takeOff;
    Queue<String> landing;
    ArrayList<String> activity;

    /**
     * This is the default constructor
     */
    public Airport(){
        this.takeOff = new LinkedList<String>();
        this.landing = new LinkedList<String>();
        this.activity = new ArrayList<String>();
    }

    /**
     * Let a plane take off
     * @param flightNum Number of the flight
     */
    public void addTakeOff(String flightNum){
        this.takeOff.add(flightNum);
    }

    /**
     * Land a plane
     * @param flightNum Number of the flight
     */
    public void addLanding(String flightNum){
        this.landing.add(flightNum);
    }

    /**
     * Handle next action
     * @return Next action of the airport
     */
    public String handleNextAction(){
        String message;
        if(this.landing.size() > 0){
            String flightNum = landing.remove();
            message = "Flight " + flightNum + " is landing.";
            this.activity.add("Flight " + flightNum + " landed.");
            return message;
        }
        else if(this.takeOff.size() > 0){
            String flightNum = takeOff.remove();
            message = "Flight " + flightNum + " is taking off.";
            this.activity.add("Flight " + flightNum + " taken-off.");
            return message;
        }
        else{
            return "No planes are waiting to land or take off.";
        }
    }

    /**
     * Check waiting planes
     * @return List of waiting planes
     */
    public String waitingPlanes(){
        if(this.takeOff.size() == 0 && this.landing.size() == 0){
            return "No plane is in the landing and take-off queues.";
        }
        else{
            String waiting = "";
            if(this.landing.size() > 0){
                waiting = "Planes waiting for landing\n-----------------------------------\n";
                for(String flightNum : this.landing){
                    waiting += flightNum + "\n";
                }
            }
            if(this.takeOff.size() > 0){
                waiting += "\nPlanes waiting for take-off\n-----------------------------------\n";
                for(String flightNum : this.takeOff){
                    waiting += flightNum + "\n";
                }
            }
            return waiting;
        }
    }

    /**
     * Get history
     * @return History of actions
     */
    public String log(){
        if(this.activity.size() == 0){
            return "No activity exists.";
        }
        else{
            String log = "List of the landing/take-off activities\n------------------------------------------\n";
            for(String history : this.activity){
                log += history + "\n";
            }
            return log;
        }
    }
}
