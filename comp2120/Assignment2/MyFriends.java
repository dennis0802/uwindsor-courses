/**
 * Developer: Dennis Dao
 * Date: Oct 8, 2020
 * Student Number: 110010116
 */

// This program tests the FriendList Class.

// This makes a MyFriends class to test the FriendList Class.
public class MyFriends {
    /**
     * Tests the methods of the FriendsList Class
     * @param args not used
     */
    public static void main(String args[]){
        FriendList myList = new FriendList();
        Person myFriend = new Person();
        Person aFriend = new Person();

        myFriend.setName("John Doe");
        myFriend.setBirthDate("April 2");
        myFriend.setCellNum("5197274689");
        aFriend.setName("Jane Doe");
        aFriend.setBirthDate("August 2");
        aFriend.setCellNum("5195380657");

        myList.addFriend(myFriend);
        myList.addFriend(aFriend);

        System.out.println("Expected: You have 2 friends.");
        System.out.println("You have " + myList.getNumFriends() + " friends.");
        System.out.println(myList.getName(aFriend));
        myList.changeFriendName(aFriend, "Jane Brown");
        System.out.println("Expected: Jane Brown");
        System.out.println(myList.getName(aFriend));
        System.out.println("Expected Phone Number for Jane Brown: 5195380657");
        System.out.println(myList.getName(aFriend) + "'s " + "phone number: " + myList.getCellNum("Jane Brown"));
        System.out.println();

        // Part 2 - Removing names of friends who have the first name "Shane" and testing various sorting behaviour
        FriendList anotherList = new FriendList();
        
        Person friend1 = new Person("Shane Smith", "1234567890", "April 3");
        Person friend2 = new Person("Shane Brown", "1234316905", "April 4");
        Person friend3 = new Person("Brandon Mailloux", "1558975355", "August 2");
        Person friend4 = new Person("Shane Greene", "4561426413", "April 3");
        Person friend5 = new Person("Joshua Parent", "4206901098", "May 11");
        Person friend6 = new Person("Chloe Chang", "0137659667", "June 8");

        anotherList.addFriend(friend1);
        anotherList.addFriend(friend2);
        anotherList.addFriend(friend3);
        anotherList.addFriend(friend4);
        anotherList.addFriend(friend5);
        anotherList.addFriend(friend6);

        FriendList birthMonthList = new FriendList(anotherList.sortByDayOfBirth("April"));
        FriendList birthDayList = new FriendList(anotherList.sortByDay("April 3"));

        // Output the results for the 5 friends.
        System.out.println("Expected: The information for the 5 friends.");
        for(Person person : anotherList.getList()){
            System.out.println("Name: " + anotherList.getName(person));
            System.out.println("Birth Date: " + anotherList.getBirthDate(person));
            System.out.println("Cell Num: " + anotherList.getCellNum(person));
            System.out.println();
        }

        // Output the results after sorting by last names on a certain birthday
        System.out.println("Expected: The information for friends with the same birthday sorted by last names.");
        for(Person person : birthDayList.getList()){
            System.out.println("Name: " + birthDayList.getName(person));
            System.out.println("Birth Date: " + birthDayList.getBirthDate(person));
            System.out.println("Cell Num: " + birthDayList.getCellNum(person));
            System.out.println();
        }

        // Output the results after sorting by birthdays in a month.
        System.out.println("Expected: The information for friends arranged in order by days in a certain month.");
        for(Person person : birthMonthList.getList()){
            System.out.println("Name: " + birthMonthList.getName(person));
            System.out.println("Birth Date: " + birthMonthList.getBirthDate(person));
            System.out.println("Cell Num: " + birthMonthList.getCellNum(person));
            System.out.println();
        }
        
        anotherList.sortByLastName();
        // Output the results after sorting by last name.
        System.out.println("Expected: The information for friends arranged in order by last name.");
        for(Person person : anotherList.getList()){
            System.out.println("Name: " + anotherList.getName(person));
            System.out.println("Birth Date: " + anotherList.getBirthDate(person));
            System.out.println("Cell Num: " + anotherList.getCellNum(person));
            System.out.println();
        }

        anotherList.removeAllByName("Shane");
        // Output the results after removing anyone with the name "Shane"
        System.out.println("Expected: The information for friends whose names weren't Shane.");
        for(Person person : anotherList.getList()){
            System.out.println("Name: " + anotherList.getName(person));
            System.out.println("Birth Date: " + anotherList.getBirthDate(person));
            System.out.println("Cell Num: " + anotherList.getCellNum(person));
            System.out.println();
        }
        
    }
}
