/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.LinkedList;

/**
 This class supplies a utility method to reverse the entries in a linked list.
*/
public class ListUtil{
    /**
     * Reverses the elements in a linked list
     * @param strings the linked list to reverse
     */
    public static void reverse(LinkedList<String> strings){
    // Complete this static method based on its JavaDoc comment.
        // Go through the list in reverse (2nd last to first)
        for(int i = strings.size() - 2; i >= 0; i--){
            // Get the current name
            String name = strings.get(i);
            // Remove the current name
            strings.remove(i);

            // Add the name to the last position
            strings.addLast(name);
        }
    }
}
