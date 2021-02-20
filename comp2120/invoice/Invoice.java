/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 */

// Imports
import java.util.ArrayList;

/**
 * Make a class of Invoice
 */
public class Invoice {
    // Instance variables
    private double totalAmount;
    private Address address;
    private ArrayList<LineItem> lineList;
    
    // Constructors
    /**
     * This is the default constructor
     */
    public Invoice(){

    }

    /**
     * This is the second constructor
     * @param lineList The list of lines on the invoice
     */
    public Invoice(Address address){
        this.address = address;
        this.lineList = new ArrayList<LineItem>();
    }

    // Methods
    // Getters
    /**
     * Get the total amount due of an invoice
     * @return The total amount due
     */
    public double getTotalAmount(){
        this.totalAmount = 0;
        for(LineItem line : lineList){
            this.totalAmount += line.getTotalPrice();
        }
        return this.totalAmount;
    }
    
    /**
     * Format the invoice as a string
     * @return The data formatted as a string
     */
    public String format(){
        // Variable to help format the invoice
        String data = String.format("%30s", "INVOICE\n") + this.address.format() + "\n" + String.format("\n%-30s%8s%5s%8s\n", "Description", "Price ", "Amt", "Total");

        // Add data from the list of items to the invoice
        for(LineItem line : lineList){
            data = data + line.format() + "\n";
        }

        // Add total amount
        data = data + String.format("\nTOTAL: $%8.2f", getTotalAmount());
        return data;
    }

    // Setters
    /**
     * Set the line item of the invoice
     * @param lineItem The line item of the invoice
     */
    public void setLineList(ArrayList<LineItem> lineList){
        this.lineList = lineList;
    }

    // Add an item to the list.
    public void setLineItem(LineItem lineItem){
        this.lineList.add(lineItem);
    }

    public void setAddress(Address address){
        this.address = address;
    }

    /**
     * Add a new item to the invoice
     * @param line The line item of the invoice
     * @param product The product of the line
     * @return A flag showing if the item was added. (1 = success, -1 = out of stock)
     */
    public int addProduct(Product product, int amount){
        if(amount <= 0){
            return -1;
        }
        else{
            LineItem item = new LineItem(product, amount);
            this.lineList.add(item);
            return 1;
        }
    }

}
