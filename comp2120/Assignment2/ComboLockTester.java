/**
 * Developer: Dennis Dao
 * Date: Oct 13, 2020
 * Student Number: 110010116
 */

// Import the Scanner package
import java.util.Scanner;

// This program tests the ComboLock class.

// This makes a ComboLockTester class
public class ComboLockTester {
    /**
     * Test the methods of ComboLock class.
     * @param args
     */
    public static void main(String args[]){
        // Variable definitions
        int input1 = 1;
        int input2 = 1;
        int input3 = 1;
        String direction;
        ComboLock myLock = new ComboLock(39, 5, 23);
        Scanner num1 =  new Scanner(System.in);
        Scanner num2 =  new Scanner(System.in);
        Scanner num3 =  new Scanner(System.in);
        Scanner str = new Scanner(System.in);

        System.out.println("The lock dial is currently pointing at 0 by default.");
        System.out.println("Enter zero for every tick prompt to exit the program.");

        // Loop until the user enters 3 zeroes.
        while(input1 != 0 || input2 != 0 || input3 != 0){
            // Input the number and direction.
            System.out.println("Enter the first amount of ticks to turn between 0-39: ");
            input1 = num1.nextInt();
            System.out.println("Enter a direction to turn: ");
            direction = str.nextLine();
            // Check the number and direction input forced to lowercase.
            if(input1 >= 0 && input1 <= 39 && (direction.toLowerCase()).equals("right")){
                System.out.println(input1 + " ticks have been turned to the right.");
                myLock.turnRight(input1);
            }
            else if(input1 >= 0 && input1 <= 39 && (direction.toLowerCase()).equals("left")){
                System.out.println(input1 + " ticks have been turned to the left.");
                myLock.turnLeft(input1);
            }
            else{
                System.out.println("Invalid amount of ticks or direction. Please try again.");
                System.out.println("The dial has been reset to 0.");
                myLock.reset();
                continue;
            }

            // Input the number and direction.
            System.out.println("Enter the second amount of ticks to turn between 0-39: ");
            input2 = num2.nextInt();
            System.out.println("Enter a direction to turn: ");
            direction = str.nextLine();
            // Check the number and direction input forced to lowercase.
            if(input2 >= 0 && input2 <= 39 && (direction.toLowerCase()).equals("right")){
                System.out.println(input2 + " ticks have been turned to the right.");
                myLock.turnRight(input2);
            }
            else if(input2 >= 0 && input2 <= 39 && (direction.toLowerCase()).equals("left")){
                System.out.println(input2 + " ticks have been turned to the left.");
                myLock.turnLeft(input2);
            }
            else{
                System.out.println("Invalid amount of ticks or direction. Please try again.");
                System.out.println("The dial has been reset to 0.");
                myLock.reset();
                continue;
            }

            // Input the number and direction.
            System.out.println("Enter the third amount of ticks to turn between 0-39: ");
            input3 = num3.nextInt();
            System.out.println("Enter a direction to turn: ");
            direction = str.nextLine();
            // Check the number and direction input forced to lowercase.
            if(input3 >= 0 && input3 <= 39 && (direction.toLowerCase()).equals("right")){
                System.out.println(input3 + " ticks have been turned to the right.");
                myLock.turnRight(input3);
            }
            else if(input3 >= 0 && input3 <= 39 && (direction.toLowerCase()).equals("left")){
                System.out.println(input3 + " ticks have been turned to the left.");
                myLock.turnLeft(input3);
            }
            else{
                System.out.println("Invalid amount of ticks or direction. Please try again.");
                System.out.println("The dial has been reset to 0.");
                myLock.reset();
                continue;
            }
            
            // Check that the input wasn't all 0's
            if(input1 != 0 || input2 != 0 || input3 != 0){
                // Check if the lock can be opened.
                if(myLock.open() == true){
                    System.out.println("The lock has been opened.");
                    break;
                }
                else{
                    System.out.println("That was not the right combination. Try again. The dial has been reset to 0.");
                    System.out.println();
                    myLock.reset();
                }
            }
        }
        // Close the input-taking.
        num1.close();
        num2.close();
        num3.close();
        str.close();
    }   
}
