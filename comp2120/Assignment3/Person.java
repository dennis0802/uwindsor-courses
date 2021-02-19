/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

/**
 * This makes a class Person implementing Comparable
 */
public class Person implements Comparable<Person>{
    // Instance variables
    private String name;

    // Constructors
    /**
     * This is the default constructor
     */
    public Person(){
        this.name = "";
    }

    /**
     * This is the second constructor
     * @param name The name of the person
     */
    public Person(String name){
        this.name = name;
    }

    // Methods
    // Getter
    /**
     * Get the name of the person
     * @return The name of the person
     */
    public String getName(){
        return this.name;
    }

    /**
     * Compare persons by their name
     */
    public int compareTo(Person person){
        // The order is: this.name, person.name
        if(this.name.compareTo(person.getName()) < 0){
            return -1;
        }
        // The order is: person.name, this.name
        if(this.name.compareTo(person.getName()) > 0){
            return 1;
        }
        return 0;
    }
}
