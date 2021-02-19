/**
 * Developer: Dennis Dao 
 * Date: Oct 13, 2020
 * Student Number: 110010116
 */

// This program makes a ComboLock class.

// This makes a ComboLock class.
public class ComboLock {
    // Instance variables
    private int secret1;
    private int secret2;
    private int secret3;
    private int dialPosition;
    private boolean hitSecret1;
    private boolean hitSecret2;
    private boolean hitSecret3;

    /**
     * This is the default constructor
     * @param secret1 The first part of the combination lock.
     * @param secret2 The second part of the combination lock.
     * @param secret3 The third part of the combination lock.
     */
    public ComboLock(int secret1, int secret2, int secret3){
        this.secret1 = secret1;
        this.secret2 = secret2;
        this.secret3 = secret3;
        this.dialPosition = 0;
        this.hitSecret1 = false;
        this.hitSecret2 = false;
        this.hitSecret3 = false;
    }

    /**
     * Reset the dial position
     */
    public void reset(){
        this.dialPosition = 0;
    }

    /**
     * Turn the combination lock to the left and check if any numbers were hit.
     * @param ticks The amount of ticks to turn
     */
    public void turnLeft(int ticks){
        // Check if dial needs to be set to 39
        if(this.dialPosition - ticks < 0){
            ticks = ticks - dialPosition;
            this.dialPosition = 40;
            this.dialPosition = this.dialPosition - ticks;     
        }
        else{
            this.dialPosition = this.dialPosition  - ticks;
        }

        // Check if second part of the lock is hit
        if(this.dialPosition == this.secret2 && this.hitSecret1 == true){
            this.hitSecret2 = true;
        }
        else{
            this.hitSecret1 = false;
        }
    }

    /**
     * Turn the combination lock to the right and check if any numbers were hit.
     * @param ticks The amount of ticks to turn
     */
    public void turnRight(int ticks){
        // Check if dial needs to be set to 0
        if(this.dialPosition + ticks > 39){
            ticks = ticks - (39 - this.dialPosition);
            this.dialPosition = -1;
            this.dialPosition = this.dialPosition + ticks;
        }
        else{
            this.dialPosition = this.dialPosition  + ticks;
        }

        // Check if first part of the lock is hit
        if(this.dialPosition == this.secret1 && hitSecret1 == false){
            hitSecret1 = true;
        }
        // Ensure when checking the third part, it doesn't overlap.
        else if(hitSecret2 == false){
            hitSecret1 = false;
        }

        // Check if third part of the lock is hit
        if(this.dialPosition == this.secret3 && hitSecret1 == true && hitSecret2 == true){
            hitSecret3 = true;
        }
        // Ensure when checking the first part, it doesn't overlap.
        else if(hitSecret1 == true && hitSecret2 == true){
            hitSecret1 = false;
            hitSecret2 = false;
        }
    }

    /**
     * Open the lock if the three secret numbers were hit.
     * @return
     */
    public boolean open(){
        if(hitSecret1 == true && hitSecret2 == true && hitSecret3 == true){
            return true;
        }
        else{
            return false;
        }
    }
}
