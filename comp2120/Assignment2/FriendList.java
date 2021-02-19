/**
 * Developer: Dennis Dao
 * Student Number: 110010116
 * Date: Oct 11, 2020
 */

import java.util.ArrayList; 
import java.util.Collections;

// This program makes the FriendList class.

// This class makes a FriendList
public class FriendList {
    // Instance variables
    ArrayList<Person> friends;
    ArrayList<Person> friendsByBirthMonth;
    ArrayList<Person> friendsByBirthDay;

    // Constructors
    /**
     * This is the default constructor
     */
    public FriendList(){
        this.friends = new ArrayList<Person>();
        this.friendsByBirthMonth = new ArrayList<Person>();
        this.friendsByBirthDay = new ArrayList<Person>();
    }

    /**
     * This is the second constructor
     * @param friends The given list of friends
     */
    public FriendList(ArrayList<Person> friends){
        this.friends = friends;
        this.friendsByBirthMonth = new ArrayList<Person>();
        this.friendsByBirthDay = new ArrayList<Person>();
    }

    // Methods
    // Getters
    /**
     * Get the number of friends.
     * @return The size of the friends list.
     */
    public int getNumFriends(){
        return this.friends.size();
    }

    /**
     * Get the name of the friend.
     * @param friend The friend whose name you wish to get.
     * @return The name of the friend
     */
    public String getName(Person friend){
        return friend.getName();
    }

    /**
     * Get the birth date of the friend.
     * @param friend The friend whose birth date you wish to get.
     * @return The birth date of the friend
     */
    public String getBirthDate(Person friend){
        return friend.getBirthDate();
    }

    /**
     * Get the cell number of the friend.
     * @param friend The friend whose cell number you wish to get.
     * @return The cell number of the friend.
     */
    public String getCellNum(Person friend){
        return friend.getCellNum();
    }

    /**
     * Get the cell number of the friend by their name
     * @param name The name of the friend whose cell number you wish to get.
     * @return The cell number of the friend.
     */
    public String getCellNum(String name){
        for(Person friend : friends){
            if(name.equals(friend.getName())){
                return friend.getCellNum();
            }
        }
        return "N/A";
    }

    /**
     * Get the whole list of friends.
     * @return The whole list.
     */
    public ArrayList<Person> getList(){
        return friends;
    }

    // Setters / Adders / Removers
    /**
     * Add a friend to the list
     * @param friend The friend of class Person to be added
     */
    public void addFriend(Person friend){
        this.friends.add(friend);
    }

    /**
     * Remove a friend from the list.
     * @param friend The friend of class Person to be removed.
     */
    public void removeFriend(Person friend){
        this.friends.remove(friend);
    }

    /**
     * Remove all friends of a certain name from the list.
     * @param friend The friend of class Person to be removed.
     */
    public void removeAllByName(String name){
        for(int i = 0; i < friends.size(); i++){
            // Get the first name of each person in the list.
            Person friend = new Person();
            friend = friends.get(i);
            int index = (friend.getName()).indexOf(" ");
            String firstName = friend.getName().substring(0, index);

            // Remove and lower the upper bounds of the loop if a match is found.
            if(firstName.equals(name)){
                this.friends.remove(friend);
                i--;
            }
        }
    }

    /**
     * Change the name of the friend.
     * @param friend The friend of the name to be changed.
     * @param name The new name.
     */
    public void changeFriendName(Person friend, String name){
        friend.setName(name);
    }

    /**
     * Change the cell num of the friend.
     * @param friend The friend of the cell num to be changed.
     * @param cellNum The new cell num.
     */
    public void changeFriendCellNum(Person friend, String cellNum){
        friend.setName(cellNum);
    }

    /**
     * Change the birth date of the friend.
     * @param friend The friend of the birth date to be changed.
     * @param birthDate The new birth date.
     */
    public void changeFriendBirth(Person friend, String birthDate){
        friend.setName(birthDate);
    }

    /**
     * Sort the list by last names
     */
    public void sortByLastName(){
        // Note - simply calling sort function from the Collections import will not work - the FriendList class is a custom object
        // Perform bubble swap with the last names
        for(int i = 0; i < this.friends.size() - 1; i++){
            for(int j = 0; j < this.friends.size() - 1 - i; j++){
                if((this.friends.get(j).getLastName()).compareTo(this.friends.get(j+1).getLastName()) >= 1){
                    Collections.swap(this.friends, j, j+1);
                }     
            }
        }     
    }

    /**
     * Sort the list by birthdays in a month
     * @param month The month to check
     * @return The list of friends in a month sorted by day
     */
    public ArrayList<Person> sortByDayOfBirth(String month){
        // Clear any previous use of the list.
        this.friendsByBirthMonth.clear();

        // Get only the friends for the month in question.
        for(int i = 0; i < this.friends.size() - 1; i++){
            if(this.friends.get(i).getBirthMonth().equals(month)){
                this.friendsByBirthMonth.add(this.friends.get(i));
            }
        }

        // Note - simply calling sort function from the Collections import will not work - the FriendList class is a custom object
        // Perform bubble swap with the birth days
        for(int i = 0; i < this.friendsByBirthMonth.size() - 1; i++){
            for(int j = 0; j < this.friendsByBirthMonth.size() - 1 - i; j++){
                if((this.friendsByBirthMonth.get(j).getBirthDay()).compareTo(this.friendsByBirthMonth.get(j+1).getBirthDay()) >= 1){
                    Collections.swap(this.friendsByBirthMonth, j, j+1);
                }
            }
        }
        return this.friendsByBirthMonth;
    }

    /**
     * Sort the list by last names on a specific birth date
     * @param birthday The specific date to check
     * @return The list of friends sorted by last name
     */
    public ArrayList<Person> sortByDay(String birthday){
        // Clear any previous use of the list.
        this.friendsByBirthDay.clear();

        // Get only the friends for the month in question.
        for(int i = 0; i < this.friends.size() - 1; i++){
            if(this.friends.get(i).getBirthDate().equals(birthday)){
                this.friendsByBirthDay.add(friends.get(i));
            }
        }
        // Note - simply calling sort function from the Collections import will not work - the FriendList class is a custom object
        // Perform bubble swap with the birth days
        for(int i = 0; i < this.friendsByBirthDay.size() - 1; i++){
            for(int j = 0; j < this.friendsByBirthDay.size() - 1 - i; j++){
                if((this.friendsByBirthDay.get(j).getLastName()).compareTo(this.friendsByBirthDay.get(j+1).getLastName()) >= 1){ 
                    Collections.swap(this.friendsByBirthDay, j, j+1);
                }
            }
        }
        return this.friendsByBirthDay;
    }
}
