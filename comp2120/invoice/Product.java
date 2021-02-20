/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 * Lab Section: 51
 */

/**
 * Make a class of Product
 */
public class Product {
    // Instance variables
    private double unitPrice;
    private String description;

    // Constructors
    /**
     * This is the default constructor
     */
    public Product(){
        this.unitPrice = 0.0;
        this.description = "N/A";
    }

    /**
     * This is the second constructor
     * @param amountOfProduct The amount of product
     * @param unitPrice The unit price for the product
     * @param description The description of the product
     */
    public Product(double unitPrice, String description){
        this.unitPrice = unitPrice;
        this.description = description;
    }

    // Methods
    // Getters
    /**
     * Get the unit price of the product
     * @return The unit price of the product
     */
    public double getUnitPrice(){
        return this.unitPrice;
    }

    /**
     * Get the description of the product
     * @return The description of the product
     */
    public String getDescription(){
        return this.description;
    }

    // Setters
    /**
     * Set the unit price of the product
     * @param unitPrice The unit price for the product
     */
    public void setUnitPrice(double unitPrice){
        this.unitPrice = unitPrice;
    }

    /**
     * Set the description of the product
     * @param description The description of the product
     */
    public void setDescription(String description){
        this.description = description;
    }

}
