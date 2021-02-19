/**
 * Developer: Dennis Dao
 * Date: Oct 26, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;

// This program makes an Manager class, subclass of Employee

// This class makes a Manager, subclass of Employee
public class Manager extends Employee{
    // Instance variables
    private ArrayList<Person> employeeList;
    private double monthlyBonus;

    // Constructors
    /**
     * This is the default constructor
     */
    public Manager(){
        super();
        employeeList = new ArrayList<Person>();
        this.monthlyBonus = 0;
    }

    /**
     * This is the 2nd constructor
     * @param employeeList List of employees
     * @param monthlyBonus Monthly bonus of the manager.
     */
    public Manager(ArrayList<Person> employeeList, double monthlyBonus){
        super();
        this.employeeList = employeeList;
        this.monthlyBonus = monthlyBonus;
    }

    /**
     * This is the 3rd constructor
     * @param employeeList List of employees
     * @param monthlyBonus Monthly bonus of the manager.
     * @param year The year of hiring
     * @param salary Their salary
     * @param vacationDays Amount of vacation days
     * @param unusedVacationDays Amount of vacation days unused.
     * @param name The name of the manager
     * @param cellNum Their cellphone number
     * @param birthDate Their birth date
     */
    public Manager(ArrayList<Person> employeeList, double monthlyBonus, int year, double salary, int vacationDays, int unusedVacationDays, String name, String cellNum, String birthDate){
        this.employeeList = employeeList;
        this.monthlyBonus = monthlyBonus;
        super.setHiringYear(year);
        super.setSalary(salary);
        super.setVacationDays(vacationDays);
        super.setUnusedVacationDays(unusedVacationDays);
        super.setName(name);
        super.setBirthDate(birthDate);
        super.setCellNum(cellNum);
    }

    /**
     * This is the 4th constructor
     * @param monthlyBonus Monthly bonus of the manager.
     * @param year The year of hiring
     * @param salary Their salary
     * @param vacationDays Amount of vacation days
     * @param unusedVacationDays Amount of vacation days unused.
     * @param name The name of the manager
     * @param cellNum Their cellphone number
     * @param birthDate Their birth date
     */
    public Manager(double monthlyBonus, int year, double salary, int vacationDays, int unusedVacationDays, String name, String cellNum, String birthDate){
        employeeList = new ArrayList<Person>();
        this.monthlyBonus = monthlyBonus;
        super.setHiringYear(year);
        super.setSalary(salary);
        super.setVacationDays(vacationDays);
        super.setUnusedVacationDays(unusedVacationDays);
        super.setName(name);
        super.setBirthDate(birthDate);
        super.setCellNum(cellNum);
    }

    // Getters
    /**
     * Get the employee list
     * @return The employee list.
     */
    public ArrayList<Person> getEmployeeList(){
        return this.employeeList;
    }

    /**
     * Get the monthly bonus
     * @return The monthly bonus.
     */
    public double getMonthlyBonus(){
        return this.monthlyBonus;
    }

    // Setters
    /**
     * Set the list of employees.
     * @param employeeList The list of employees for a manager.
     */
    public void setEmployeeList(ArrayList<Person> employeeList){
        this.employeeList = employeeList;
    }

    /**
     * Set the monthly bonus
     * @param bonus The monthly bonus of the manager
     */
    public void setMonthlyBonus(double bonus){
        this.monthlyBonus = bonus;
    }

    /**
     * Add an employee to the employee list.
     * @param employee An employee
     */
    public void addEmployee(Person employee){
        this.employeeList.add(employee);
    }

    /**
     * Remove an employee from the employee list.
     * @param employee An employee.
     */
    public void removeEmployee(Person employee){
        this.employeeList.remove(employee);
    }

    
}
