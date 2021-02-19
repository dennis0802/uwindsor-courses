/**
 * Developer: Dennis Dao
 * Date: Oct 26, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.ArrayList;

// This program tests the methods of Company, Employee, and Manager classes

// This class tests the methods of Company, Employee, and Manager
public class MyCompany {
    /**
     * Test the methods
     * @param args not used
     */
    public static void main(String args[]){
        // Part 1 - set up the people (Person, Employee, Manager) for the company
        Person employee1 = new Employee(2010, 14.50, 2, 8, "John Kehoe", "2264098765", "May 23");
        Person employee2 = new Employee(2012, 14.50, 0, 10, "Ben Armaly", "2264098765", "October 3");
        Person employee3 = new Employee(2015, 14.50, 1, 9, "Teena T", "2264098765", "May 7");
        Person employee4 = new Employee(2011, 14.50, 0, 10, "Kate Leung", "2264098765", "July 26");
        Person employee5 = new Employee(2017, 14.50, 2, 8, "Madison Bromaroff", "2264098765", "May 10");
        Person employee6 = new Employee(2018, 14.50, 1, 9, "Nolan Morris", "2264098765", "October 15");

        Person manager1 = new Manager(5.00, 2008, 15.50, 0, 12, "Massimo Chiodo", "5322345678", "August 21");
        Person manager2 = new Manager(5.00, 2007, 15.50, 1, 11, "Anthony Fanara", "5326942567", "January 14");
        Person manager3 = new Manager(5.00, 2006, 15.50, 2, 10, "Brianna Bucasas", "5276027207", "January 26");

        ArrayList<Person> managerThenEmployee = new ArrayList<Person>();

        ((Manager)manager1).addEmployee((Employee)employee2);
        ((Manager)manager1).addEmployee((Employee)employee6);
        ((Manager)manager2).addEmployee((Employee)employee1);
        ((Manager)manager2).addEmployee((Employee)employee5);
        ((Manager)manager3).addEmployee((Employee)employee3);
        ((Manager)manager3).addEmployee((Employee)employee4);

        // Check the properties of a manager's employees
        System.out.println("Expected: Massimo Chiodo's employees and their characteristics");
        System.out.println();
        System.out.println("Actual: Massimo Chiodo's employees and their characteristics: ");
        for(int i = 0; i < ((Manager)manager1).getEmployeeList().size(); i++){
            System.out.println("Employee: " + ((Manager)manager1).getEmployeeList().get(i).getName());
            System.out.println("Birthday: " + ((Manager)manager1).getEmployeeList().get(i).getBirthDate());
            System.out.println("Cell Number: " + ((Manager)manager1).getEmployeeList().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Employee)((Manager)manager1).getEmployeeList().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Employee)((Manager)manager1).getEmployeeList().get(i)).getSalary());
            System.out.println("Unused Vacation Days: " + ((Employee)((Manager)manager1).getEmployeeList().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Employee)((Manager)manager1).getEmployeeList().get(i)).getVacationDays());
            System.out.println();
        }

        System.out.println("Expected: Anthony Fanara's employees and their characteristics");
        System.out.println();
        System.out.println("Actual: Anthony Fanara's employees and their characteristics: ");
        for(int i = 0; i < ((Manager)manager2).getEmployeeList().size(); i++){
            System.out.println("Employee: " + ((Manager)manager2).getEmployeeList().get(i).getName());
            System.out.println("Birthday: " + ((Manager)manager2).getEmployeeList().get(i).getBirthDate());
            System.out.println("Cell Number: " + ((Manager)manager2).getEmployeeList().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Employee)((Manager)manager2).getEmployeeList().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Employee)((Manager)manager2).getEmployeeList().get(i)).getSalary());
            System.out.println("Unused Vacation Days: " + ((Employee)((Manager)manager2).getEmployeeList().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Employee)((Manager)manager2).getEmployeeList().get(i)).getVacationDays());
            System.out.println();
        }

        System.out.println("Expected: Brianna Bucasas's employees and their characteristics");
        System.out.println();
        System.out.println("Actual: Brianna Bucasas's employees and their characteristics: ");
        for(int i = 0; i < ((Manager)manager3).getEmployeeList().size(); i++){
            System.out.println("Employee: " + ((Manager)manager3).getEmployeeList().get(i).getName());
            System.out.println("Birthday: " + ((Manager)manager3).getEmployeeList().get(i).getBirthDate());
            System.out.println("Cell Number: " + ((Manager)manager3).getEmployeeList().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Employee)((Manager)manager3).getEmployeeList().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Employee)((Manager)manager3).getEmployeeList().get(i)).getSalary());
            System.out.println("Unused Vacation Days: " + ((Employee)((Manager)manager3).getEmployeeList().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Employee)((Manager)manager3).getEmployeeList().get(i)).getVacationDays());
            System.out.println();
        }
      
        // Part 2 - Setting up the company and testing the methods
        Company company1 = new Company();
        company1.setCompanyName("University Papers and Co.");
        company1.addEmployee(employee1);
        company1.addEmployee(employee2);
        company1.addEmployee(employee3);
        company1.addEmployee(employee4);
        company1.addEmployee(employee5);
        company1.addEmployee(employee6);
        company1.addEmployee(manager1);
        company1.addEmployee(manager2);
        company1.addEmployee(manager3);
        company1.addManager(manager1);
        company1.addManager(manager2);
        company1.addManager(manager3);


        // Check the properties
        System.out.println("Expected: The managers of University Papers and Co. and their characteristics");
        System.out.println("Actual: The managers of University Papers and Co. and their characteristics:");
        for(int i = 0; i < company1.getManagers().size(); i++){
            System.out.println("Manager: " + company1.getManagers().get(i).getName());
            System.out.println("Birthday: " + company1.getManagers().get(i).getBirthDate());
            System.out.println("Cell Number: " + company1.getManagers().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Manager)company1.getManagers().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Manager)company1.getManagers().get(i)).getSalary());
            System.out.printf("Monthly Bonus: $%.2f\n", ((Manager)company1.getManagers().get(i)).getMonthlyBonus());
            System.out.println("Unused Vacation Days: " + ((Manager)company1.getManagers().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Manager)company1.getManagers().get(i)).getVacationDays());
            System.out.println();
        }

        System.out.println("Expected: The employees of University Papers and Co. and their characteristics");
        System.out.println("Actual: The employees of University Papers and Co. and their characteristics:");
        for(int i = 0; i < company1.getEmployees().size(); i++){
            System.out.println("Employee: " + company1.getEmployees().get(i).getName());
            System.out.println("Birthday: " + company1.getEmployees().get(i).getBirthDate());
            System.out.println("Cell Number: " + company1.getEmployees().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Employee)company1.getEmployees().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Employee)company1.getEmployees().get(i)).getSalary());
            System.out.println("Unused Vacation Days: " + ((Employee)company1.getEmployees().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Employee)company1.getEmployees().get(i)).getVacationDays());
            System.out.println();
        }

        
        // Sort by last names
        company1.sortEmployeesByLastName();
        company1.sortManagersByLastName();

        // Check the properties after sorting
        System.out.println("Actual: The managers of University Papers and Co. and their characteristics sorted by last name:");
        for(int i = 0; i < company1.getManagers().size(); i++){
            System.out.println("Manager: " + company1.getManagers().get(i).getName());
            System.out.println("Birthday: " + company1.getManagers().get(i).getBirthDate());
            System.out.println("Cell Number: " + company1.getManagers().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Manager)company1.getManagers().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Manager)company1.getManagers().get(i)).getSalary());
            System.out.printf("Monthly Bonus: $%.2f\n", ((Manager)company1.getManagers().get(i)).getMonthlyBonus());
            System.out.println("Unused Vacation Days: " + ((Manager)company1.getManagers().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Manager)company1.getManagers().get(i)).getVacationDays());
            System.out.println();
        }

        System.out.println("Actual: The employees of University Papers and Co. and their characteristics sorted by last name:");
        for(int i = 0; i < company1.getEmployees().size(); i++){
            System.out.println("Hired as: " + company1.getEmployees().get(i).getClass()); 
            System.out.println("Name: " + company1.getEmployees().get(i).getName());
            System.out.println("Birthday: " + company1.getEmployees().get(i).getBirthDate());
            System.out.println("Cell Number: " + company1.getEmployees().get(i).getCellNum());
            System.out.println("Year Hired: " + ((Employee)company1.getEmployees().get(i)).getHiringYear());
            System.out.printf("Salary: $%.2f\n", ((Employee)company1.getEmployees().get(i)).getSalary());
            System.out.println("Unused Vacation Days: " + ((Employee)company1.getEmployees().get(i)).getUnusedVacationDays());
            System.out.println("Vacation Days: " + ((Employee)company1.getEmployees().get(i)).getVacationDays());
            System.out.println();
        }

        // Get the employees of the managers.
        System.out.println("Actual: The employees of a manager at the company:");
        for(int i = 0; i < company1.getManagers().size(); i++){
            System.out.println("Manager: " + company1.getManagers().get(i).getName());
            System.out.println("Employees: ");
            for(int j = 0; j < ((Manager)company1.getManagers().get(i)).getEmployeeList().size(); j++){
                System.out.println("Name: " + ((Manager)company1.getManagers().get(i)).getEmployeeList().get(j).getName());
            }
            System.out.println();
        }

        // Get a list of employees by manager, and then their employees
        managerThenEmployee = company1.sortEmployeesByManager();

        // Get the list going by employee then manager
        for(int i = 0; i < managerThenEmployee.size(); i++){
            System.out.println(managerThenEmployee.get(i).getName());
        }
    }
    
}
