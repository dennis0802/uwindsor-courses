/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * This tests the Formatter classes
 */
public class FormatTester {
    /**
     * Test the methods of the class
     * @param args not used
     */
    public static void main(String args[]){
        // Set up formatters
        DefaultFormatter defaultFormat = new DefaultFormatter();
        DecimalSeparatorFormatter decimalFormat = new DecimalSeparatorFormatter();
        AccountingFormatter accountingFormat = new AccountingFormatter();
        BaseFormatter binaryFormat = new BaseFormatter(2);
        BaseFormatter octalFormat = new BaseFormatter(8);
        BaseFormatter hexaFormat = new BaseFormatter(16);

        // Set up the list of numbers from the file.
        ArrayList<Integer> numbers = new ArrayList<Integer>();

        // Read the input file and start an output file
        try{
            // Files, PrintWriter, and Scanner can throw FileNotFound Exception
            File inputFile = new File("Numbers.txt");
            File outputFile = new File("FormattedNumbers.txt");
            PrintWriter out = new PrintWriter(outputFile);
            Scanner in = new Scanner(inputFile);
            
            // Process data and output
            while(in.hasNext()){
                int data = in.nextInt();
                numbers.add(data);
            }
            // Close the input file
            in.close();

            // Default Format
            out.printf("Default Format: ");
            for(int data : numbers){
                String output = defaultFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Decimal Format
            out.printf("Decimal Format: ");
            for(int data : numbers){
                String output = decimalFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Accounting Format
            out.printf("Accounting Format: ");
            for(int data : numbers){
                String output = accountingFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Base-8 Format
            out.printf("Base-" + octalFormat.getBase() + " Format: ");
            for(int data : numbers){
                String output = octalFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Base-2 Format
            out.printf("Base-" + binaryFormat.getBase() + " Format: ");
            for(int data : numbers){
                String output = binaryFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Base-16 Format
            out.printf("Base-" + hexaFormat.getBase() + " Format: ");
            for(int data : numbers){
                String output = hexaFormat.format(data);
                out.printf(output + " ");
            }
            out.println();

            // Close the file
            out.close();

        }
        // Catch exceptions
        catch(FileNotFoundException exception){
            System.out.println("File not found");
            return;
        }
        catch(NullPointerException exception){
            System.out.println("NULL file found");
            return;
        }
        System.out.println("Formatting successful.");
    }
}
