/**
 * Developer: Dennis Dao
 * Date: Oct 26, 2020
 * Student Number: 110010116
 */

// This program makes an Employee class, subclass of Person

// This class makes an Employee, a subclass of Person
public class Employee extends Person{
    // Instance variables
    private int hiredYear;
    private double salary;
    private int vacationDays;
    private int unusedVacationDays;

    // Constructors
    /**
     * This is the default constructor
     */
    public Employee(){
        super();
        this.hiredYear = 0;
        this.salary = 0;
        this.vacationDays = 0;
        this.unusedVacationDays = 0;
    }

    /**
     * This is the second constructor
     * @param year The year of hiring
     * @param salary Their salary
     * @param vacationDays Amount of vacation days
     * @param unusedVacationDays Amount of vacation days unused.
     */
    public Employee(int year, double salary, int vacationDays, int unusedVacationDays){
        super();
        this.hiredYear = year;
        this.salary = salary;
        this.vacationDays = vacationDays;
        this.unusedVacationDays = unusedVacationDays;
    }

    /**
     * This is the second constructor
     * @param year The year of hiring
     * @param salary Their salary
     * @param vacationDays Amount of vacation days
     * @param unusedVacationDays Amount of vacation days unused.
     * @param name The name of the employee
     * @param cellNum Their cellphone number
     * @param birthDate Their birth date
     */
    public Employee(int year, double salary, int vacationDays, int unusedVacationDays, String name, String cellNum, String birthDate){
        super(name, cellNum, birthDate);
        this.hiredYear = year;
        this.salary = salary;
        this.vacationDays = vacationDays;
        this.unusedVacationDays = unusedVacationDays;
    }

    // Getters
    /**
     * Get the hiring year
     * @return hiring year
     */
    public int getHiringYear(){
        return this.hiredYear;
    }

    /**
     * Get the salary
     * @return salary
     */
    public double getSalary(){
        return this.salary;
    }

    /**
     * Get the vacation days
     * @return vacation days
     */
    public int getVacationDays(){
        return vacationDays;
    }

    /**
     * Get the unused vacation days
     * @return unused vacation days
     */
    public int getUnusedVacationDays(){
        return unusedVacationDays;
    }

    // Setters
    /**
     * Set the year of hiring
     * @param year Hiring year
     */
    public void setHiringYear(int year){
        this.hiredYear = year;
    }

    /**
     * Set the salary
     * @param salary Salary of the employee
     */
    public void setSalary(double salary){
        this.salary = salary;
    }

    /**
     * Set the vacation days.
     * @param days The amount of vacation days
     */
    public void setVacationDays(int days){
        this.vacationDays = days;
    }

    /**
     * Set the unused vacation days
     * @param unusedDays The amount of unused vacation days
     */
    public void setUnusedVacationDays(int unusedDays){
        this.unusedVacationDays = unusedDays;
    }

}
