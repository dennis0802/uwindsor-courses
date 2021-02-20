/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 * Lab Section: 51
 */

/**
 * Make a class of LineItem
 */
public class LineItem {
    // Instance variables
    private int amount;
    private Product product;
    private boolean outOfStock;
    
    // Constructors
    /**
     * This is the second constructor
     * NOTE: The object will be successfully created if there is available product amount (at least 1)
     * @param product The product on the line
     * @param amount The amount of product
     */
    public LineItem(Product product, int amount){
        if(amount <= 0){
            this.outOfStock = true;
        }
        if(this.outOfStock == false){
            this.product = product;
            this.amount = amount;
        }
    }

    // Methods
    // Getters
    /**
     * Get the product of the line
     * @return The product of the line
     */
    public Product getProduct(){
        return this.product;
    }

    /**
     * Get the total amount for one product
     * @return The total price for one line
     */
    public double getTotalPrice(){
        return this.product.getUnitPrice() * this.amount;
    }

    /**
     * Format each line as a string
     * @return The lineItem formatted as a string
     */
    public String format(){
        return String.format("%-30s%8.2f%5d%8.2f", this.product.getDescription(), this.product.getUnitPrice(), this.amount, this.getTotalPrice());
    }

    // Setters
    /**
     * Set a product to the line
     * @param product The product on the line
     */
    public void setProduct(Product product){
        this.product = product;
    }
}
