/**
 * Developer: Dennis Dao
 * Date: Feb 21, 2021
 * version 1.0
 */

/**
 * Creates a teller class to work with the Bank simulation classes
 */
public class Teller {
    // Instance variables
    private int workTime;

    /**
     * Default constructor
     */
    public Teller(){}

    /**
     * Set time for teller to work
     * @param workTime Amount of time to work
     */
    public void setWorkTime(int workTime){
        this.workTime = workTime;
    }

    /**
     * Decrement work time by 1
     */
    public void decrementWorkTime(){
        this.workTime--;
    }

    /**
     * Get teller's work time
     * @return Current work time of teller
     */
    public int getWorkTime(){
        return workTime;
    }
}
