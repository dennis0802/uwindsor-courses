/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;
import java.util.Collections;

/**
 * Make a utility class for ArrayList
 */
public class ArrayListUtil<E>{
    /**
     * Reverse the list while modifying the original list
     * @param list The list to be reversed
     */
    public static <E> ArrayList<E> reverseModify(ArrayList<E> list){
        Collections.reverse(list);
        return list;
    }

    /**
     * Reverse the list without modifying the original list
     * @param list The list to be reversed
     */
    public static <E> ArrayList<E> reverseCopy(ArrayList <E> list){
        ArrayList<E> newList = new ArrayList<E>();

        for(E object : list){
            newList.add(object);
        }
        Collections.reverse(newList);
        return newList;
    }
}
