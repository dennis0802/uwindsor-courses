/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 * Lab Section: 51
 */

/**
 * Make a generic class of Pair.
 */
public class Pair<T, S>{
    // Instance variables
    private T first;
    private S second;

    // Constructors
    public Pair(){
        this.first = null;
        this.second = null;
    }

    public Pair(T first, S second){
        this.first = first;
        this.second = second;
    }

    // Methods
    // Getters
    /**
     * Get the first element of the pair
     * @return The first element of the pair
     */
    public T getFirst(){
        return this.first;
    }

    /**
     * Get the second element of the pair
     * @return The second element of the pair
     */
    public S getSecond(){
        return this.second;
    }

    // Setters
    /**
     * Set the first element of the pair
     * @param first The first element of the pair
     */
    public void setFirst(T first){
        this.first = first;
    }

    /**
     * Set the second element of the pair
     * @param second The second element of the pair
     */
    public void setSecond(S second){
        this.second = second;
    }

    /**
     * Override the toString method
     * @return The object as a String, used in the print stream
     */
    @Override
    public String toString(){
        return "(" + this.first + ", " + this.second + ")";
    }

    /**
     * Override the equals method
     * @param o An object to compare
     * @return The truth value if the two objects are equal
     */
    @Override
    public boolean equals(Object o){
        Pair <T,S> other = (Pair <T,S>) o;
        return this.first.equals(other.first) && this.second.equals(other.second);
    }

}