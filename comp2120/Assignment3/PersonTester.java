/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.Scanner;
import java.util.Collections;
import java.util.ArrayList;

/**
 * Test the methods of the Person class, in particular the compareTo method
 */
public class PersonTester {
    /**
     * Test the methods of the class
     * @param args not used
     */
    public static void main(String args[]){
        // Variables
        String name;
        int numNames = 1;
        ArrayList<Person> personList = new ArrayList<Person>();
        Scanner in = new Scanner(System.in);

        // Allow the user to enter the 10 names
        while(numNames != 11){
            System.out.println("Enter a name for person #" + numNames + ": ");
            name = in.nextLine();
            Person person1 = new Person(name);
            personList.add(person1);
            numNames++;
        }
        // Close the input stream
        in.close();

        // Go through the list and compare the Persons by their names alphabetically
        for(int i = 0; i < personList.size(); i++){
            for(int j = 0; j < personList.size() - 1 - i; j++){
                if(personList.get(j).compareTo(personList.get(j+1)) >= 1){
                    Collections.swap(personList, j, j+1);
                }
            }
        }

        // Output the first and last person.
        System.out.println("The first person is: " + personList.get(0).getName());
        System.out.println("The last person is: " + personList.get(personList.size() - 1).getName());




    }
}
