/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;

/**
 * This makes a class to test the methods of the ArrayListUtil class
 */
public class ArrayListUtilTester {
    /**
     * Test the methods of the class
     * @param args not used
     */
    public static void main(String args[]){
        // Declare some lists
        ArrayList<Integer> list1 = new ArrayList<Integer>();
        ArrayList<Integer> list2 = new ArrayList<Integer>();
        ArrayList<String> list3 = new ArrayList<String>();
        ArrayList<String> list4 = new ArrayList<String>();

        // Add content to the lists
        list1.add(1);
        list1.add(2);
        list1.add(3);
        list1.add(4);
        list1.add(5);
        list3.add("Anthony");
        list3.add("Massimo");
        list3.add("Ben");
        list3.add("Dennis");
        list3.add("Brianna");
        list3.add("Kate");
        list3.add("Nolan");
        list3.add("Chloe");
        list3.add("Brandon");

        // Test integers
        System.out.println("List 1 (Start): ");
        for(int num : list1){
            System.out.printf(num + ", ");
        }
        System.out.println();

        list2 = ArrayListUtil.reverseCopy(list1);
        System.out.println("List 1 (copy reversed): ");
        for(int num : list2){
            System.out.printf(num + ", ");
        }
        System.out.println();

        System.out.println("List 1: ");
        for(int num : list1){
            System.out.printf(num + ", ");
        }
        System.out.println();

        ArrayListUtil.reverseModify(list1);
        System.out.println("List 1 (modify reversed): ");
        for(int num : list1){
            System.out.printf(num + ", ");
        }
        System.out.println();

        System.out.println("List 1 (End): ");
        for(int num : list1){
            System.out.printf(num + ", ");
        }
        System.out.println();
        System.out.println();

        // Test strings
        System.out.println("List 3 (Start): ");
        for(String name : list3){
            System.out.printf(name + ", ");
        }
        System.out.println();

        list4 = ArrayListUtil.reverseCopy(list3);
        System.out.println("List 3 (copy reverse): ");
        for(String name : list4){
            System.out.printf(name + ", ");
        }
        System.out.println();

        System.out.println("List 3: ");
        for(String name : list3){
            System.out.printf(name + ", ");
        }
        System.out.println();

        ArrayListUtil.reverseModify(list3);
        System.out.println("List 3 (modify reversed): ");
        for(String name : list3){
            System.out.printf(name + ", ");
        }
        System.out.println();

        System.out.println("List 3 (End): ");
        for(String name : list3){
            System.out.printf(name + ", ");
        }
        System.out.println();
        System.out.println();
    }
}

