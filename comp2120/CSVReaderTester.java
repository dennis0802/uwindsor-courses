/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

/**
   This program demonstrates and tests methods of the CSVReader class.
*/
public class CSVReaderTester{
   /**
    * Test the methods
    * @param args not used
    */
   public static void main(String[] args){
      // Define readers
      CSVReader reader1 = new CSVReader("att2007.csv");
      CSVReader reader2 = new CSVReader("quotes.csv");
   
      // Test the methods
      System.out.println("Number of rows: " + reader1.numberOfRows());
      System.out.println("Expected: 214");
      System.out.println("Number of fields in row 10: " + reader1.numberOfFields(10));
      System.out.println("Expected: 7");
      System.out.println("Row 10, Col 2: " + reader1.field(10, 2));
      System.out.println("Expected: 24.95");

      System.out.println("Number of rows: " + reader2.numberOfRows());
      System.out.println("Expected: 2");
      System.out.println("Number of fields in row 1: " + reader2.numberOfFields(1));
      System.out.println("Expected: 4");
      System.out.println("Row 1, Col 2: " + reader2.field(1, 2));
      System.out.println("Expected: Hello, World");
      System.out.println("Row 1, Col 3: " + reader2.field(1, 3));
      System.out.println("Expected: He asked: \"Quo vadis?\"");
      System.out.println("Row 0, Col 3: " + reader2.field(0, 3));
      System.out.println("Expected: \"..., that all men are created equal, ...\"");
   }
}