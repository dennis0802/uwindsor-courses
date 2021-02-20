/**
 * Developer: Dennis Dao 
 * Date: Nov 19, 2020
 * Lab Section: 51
 */

/**
 * Test the methods of the Invoice class and its related classes.
 */
public class InvoiceTester {
    /**
     * Test the methods of the class
     * @param args not used
     */
    public static void main(String args[]){
        // Make an invoice
        Address address = new Address("Java Graphics", "1300 Java Rd.", "Anytown, CA", "12345");
        Invoice invoice = new Invoice(address);
       
        // Test adding products in stock and out of stock
        if(invoice.addProduct(new Product(20.99, "Brushes"), 10) == 1){
            System.out.println("Item added successfully.");
        }
        else{
            System.out.println("Item is out of stock");
        }
        if(invoice.addProduct(new Product(10.99, "Paints"), 10) == 1){
            System.out.println("Item added successfully.");
        }
        else{
            System.out.println("Item is out of stock.");
        }
        if(invoice.addProduct(new Product(10.99, "Oil Pastels"), 0) == 1){
            System.out.println("Item added successfully.");
        }
        else{
            System.out.println("Item is out of stock.");
        }
        System.out.println();

        // Print the invoice.
        System.out.println(invoice.format());



    }
}
