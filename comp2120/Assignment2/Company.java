/**
 * Developer: Dennis Dao
 * Date: Oct 26, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;
import java.util.Collections;

// This program makes a Company class.

// This class makes a company.
public class Company {
    // Instance variables
    private String name;
    private int startYear;
    private ArrayList<Person> employeeList;
    private ArrayList<Person> managerList;
    private ArrayList<Person> managerThenEmployeeList;

    // Constructors
    /**
     * This is the default constructor.
     */
    public Company(){
        this.name = "";
        this.startYear = 0;
        this.employeeList = new ArrayList<Person>();
        this.managerList = new ArrayList<Person>();
        this.managerThenEmployeeList = new ArrayList<Person>();
    }

    /**
     * This is the 2nd constructor
     * @param name Name of the company
     * @param startYear Starting year of the company
     * @param employees Employees in the company
     * @param managers Managers in the company
     */
    public Company(String name, int startYear, ArrayList<Person> employees, ArrayList<Person> managers){
        this.name = name;
        this.startYear = startYear;
        this.employeeList = employees;
        this.managerList = managers;
    }

    // Methods
    /**
     * Get the company name
     * @return The name of the company
     */
    public String getName(){
        return this.name;
    }

    /**
     * Get the starting year of the company
     * @return Starting year of the company
     */
    public int getStartYear(){
        return this.startYear;
    }

    /**
     * Get the list of employees.
     * @return The list of employees
     */
    public ArrayList<Person> getEmployees(){
        return this.employeeList;
    }

    /**
     * Get the list of managers
     * @return The list of managers
     */
    public ArrayList<Person> getManagers(){
        return this.managerList;
    }

    // Setters
    /**
     * Set the company name
     * @param name Name of the company
     */
    public void setCompanyName(String name){
        this.name = name;
    }

    /**
     * Set the starting year of the company
     * @param year Starting year of the company
     */
    public void setStartYear(int year){
        this.startYear = year;
    }

    /**
     * Set the employees of the company.
     * @param employees Employees of the company
     */
    public void setEmployees(ArrayList<Person> employees){
        this.employeeList = employees;
    }

    /**
     * Set the managers of the company
     * @param managers Managers of the company
     */
    public void setManagers(ArrayList<Person> managers){
        this.managerList = managers;
    }

    /**
     * Add an employee to the employee list
     * @param employee The new employee
     */
    public void addEmployee(Person employee){
        this.employeeList.add(employee);
    }

    /**
     * Add a manager to the manager list
     * @param manager The new manager
     */
    public void addManager(Person manager){
        this.managerList.add(manager);
    }

    /**
     * Remove an employee from the list
     * @param employee The employee to be removed
     */
    public void removeEmployee(Person employee){
        this.employeeList.remove(employee);
    }

    /**
     * Remove a manager from the list
     * @param manager The manager to be removed.
     */
    public void removeManager(Person manager){
        this.managerList.remove(manager);
    }

    /**
     * Sort the managers based on their last name.
     */
    public void sortManagersByLastName(){
        // Bubble swap the managers based on their last name.
        for(int i = 0; i < this.managerList.size(); i++){
            for(int j = 0; j < this.managerList.size() - 1 - i; j++){
                if(this.managerList.get(j).getLastName().compareTo(this.managerList.get(j+1).getLastName()) >= 1){
                    Collections.swap(this.managerList, j , j+1);
                }
            }
        }
    }

    /**
     * Sort the employees based on their last name.
     */
    public void sortEmployeesByLastName(){
        // Bubble swap the employees based on their last name.
        for(int i = 0; i < this.employeeList.size(); i++){
            for(int j = 0; j < this.employeeList.size() - 1 - i; j++){
                if(this.employeeList.get(j).getLastName().compareTo(this.employeeList.get(j+1).getLastName()) >= 1){
                    Collections.swap(employeeList, j , j+1);
                }
            }
        }
    }

    /**
     * Create a list of the employees by the manager, then the employees
     */
    public ArrayList<Person> sortEmployeesByManager(){
        // Clear any previous uses
        managerThenEmployeeList.clear();
        this.managerList.get(1);

        for(int i = 0; i < this.managerList.size(); i++){
            managerThenEmployeeList.add(this.managerList.get(i));
            for(int j = 0; j < ((Manager)this.managerList.get(i)).getEmployeeList().size(); j++){
                managerThenEmployeeList.add(((Manager)this.managerList.get(i)).getEmployeeList().get(j));
            }
        }
        return managerThenEmployeeList;
    }
}
