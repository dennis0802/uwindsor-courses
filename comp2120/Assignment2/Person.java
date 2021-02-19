/**
 * Developer: Dennis Dao
 * Student Number: 110010116
 * Date: Oct 11, 2020
 */

// This program makes the Person class.

// This class makes a Person
public class Person{
    // Instance variables
    private String name;
    private String cellNum;
    private String birthDate;

    // Constructors
    /**
     * This is the default constructor
     */
    public Person(){
        this.name = "";
        this.cellNum = "";
        this.birthDate = "";
    }

     /**
      * This is the second constructor
      * @param name The name of the person
      * @param cellNum The cellphone number of the person
      * @param birthDate The birthdate of the person
      */
    public Person(String name, String cellNum, String birthDate){
        this.name = name;
        this.cellNum = cellNum;
        this.birthDate = birthDate;
    }

    // Methods - Getters
    /**
     * Get the name of the person.
     */
    public String getName(){
        return name;
    }

    /**
     * Get the cell number of the person.
     */
    public String getCellNum(){
        return cellNum;
    }

    /**
     * Get the birth date of the person
     */
    public String getBirthDate(){
        return birthDate;
    }

    /**
     * Get the last name of the person
     * @return
     */
    public String getLastName(){
        int index = (this.getName()).indexOf(" ");
        String lastName = this.getName().substring(index + 1, this.getName().length());
        return lastName;
    }

    /**
     * Get the birth month of the person ie. May, June, July...
     * @return
     */
    public String getBirthMonth(){
        int index = (this.getBirthDate()).indexOf(" ");
        String month = this.getBirthDate().substring(0, index);
        return month;
    }

    /**
     * Get the birth day of the person ie. 14, 15, 16...
     * @return
     */
    public String getBirthDay(){
        int index = (this.getBirthDate()).indexOf(" ");
        String month = this.getBirthDate().substring(index + 1, this.getBirthDate().length());
        return month;
    }

    // Methods - Setters
    /**
     * Set the first name of the person.
     * @param name The name of the person
     */
    public void setName(String name){
        this.name = name;
    }

    /**
     * Set the first name of the person.
     * @param cellNum The cellphone number of the person
     */
    public void setCellNum(String cellNum){
        this.cellNum = cellNum;
    }

    /**
     * Set the birth date of the person.
     * @param birthDate The birth date of the person
     */
    public void setBirthDate(String birthDate){
        this.birthDate = birthDate;
    }
}