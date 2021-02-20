/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 * Lab Section: 51
 */

/**
 * Make a class of Address
 */
public class Address {
    // Instance variables
    private String name;
    private String street;
    private String location;
    private String postCode;
    
    // Constructors
    /**
     * This is the default constructor
     */
    public Address(){
        this.name = "";
        this.street = "";
        this.location = "";
        this.postCode = "";
    }

    /**
     * This is the second constructor
     * @param address The address of the invoice
     */
    public Address(String name, String street, String location, String postCode){
        this.name = name;
        this.street = street;
        this.location = location;
        this.postCode = postCode;
    }

    // Methods
    // Getters
    /**
     * Get the company name of the invoice
     * @return The company name of the invoice
     */
    public String getName(){
        return this.name;
    }

    /**
     * Get the street location of the invoice
     * @return The street location of the invoice
     */
    public String getStreet(){
        return this.street;
    }

    /**
     * Get the company location of the invoice
     * @return The company location of the invoice
     */
    public String getLocation(){
        return this.location;
    }

    /**
     * Get the company name of the invoice
     * @return The company name of the invoice
     */
    public String getPostCode(){
        return this.postCode;
    }

    /**
     * Format the address as a string
     * @return The address formatted as a string
     */
    public String format(){
        return this.name + "\n" + this.street + "\n" + this.location + "\n" + this.postCode;
    }

    // Setters
    /**
     * Set the address of the invoice
     * @param address The address of the invoice
     */
    public void setAddress(String name, String street, String location, String postCode){
        this.name = name;
        this.street = street;
        this.location = location;
        this.postCode = postCode;
    }



}
