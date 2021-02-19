/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * This makes a CSVReader class (Comma Seperated Value)
 */
public class CSVReader {
    // Instance variables
    private String fileName = "";

    // Constructor
    public CSVReader(String file){
        this.fileName = file;
    }

    // Methods
    // Getters
    /**
     * Return the number of lines in the CSV file
     * @return The number of lines in the CSV file
     */
    public int numberOfRows(){
        // Counter for rows
        int numRows = 0;

        try{
            // Read the file
            File inFile = new File(fileName);
            // Throws exception if file not found.
            Scanner in = new Scanner(inFile);
            
            // While there is more to be read, increment rows
            while(in.hasNextLine()){
                numRows++;
                in.nextLine();
            }
            in.close();
        }
        // Catch exception
        catch(FileNotFoundException exception){
            System.out.println("File not found");
        }
        return numRows;
    }

    /**
     * Return the number of fields in a particular row
     * @param targetRow The row of the file to be read
     * @return The number of fields in the row
     */
    public int numberOfFields(int targetRow){
        // Counter for rows
        int rowNum = 0;
        int numFields = 0;

        try{
            // Read the file
            File inFile = new File(fileName);
            // Throws exception if file not found.
            Scanner in = new Scanner(inFile);
            String allFields;
            // Flag for the field being quoted
            Boolean quotesFound = false;

            // While there is more to be read, increment rows
            while(in.hasNextLine()){
                // If current row is the target row
                if(rowNum == targetRow){
                    allFields = in.nextLine();
                    // Process characters within that string and leave the loop
                    for(int i = 0; i < allFields.length(); i++){
                        // Switch the flag based on whether the quote started or ended.
                        if(allFields.charAt(i) == '\"' && quotesFound == false){
                            quotesFound = true;
                        }
                        else if (allFields.charAt(i) == '\"' && quotesFound == true){
                            quotesFound = false;
                        }
                        // First field
                        if(i == 0){
                            numFields++;
                        }
                        // If a comma is found and it isn't quoted
                        else if(allFields.charAt(i) == ',' && quotesFound == false){
                            numFields++;
                        }
                    }
                    break;
                }
                // Increment if not the target row
                else{
                    rowNum++;
                    in.nextLine();
                }
            }
            in.close();
        }
        // Catch exception
        catch(FileNotFoundException exception){
            System.out.println("File not found");
        }
        return numFields;
    }

    /**
     * Returns the field in a particular row and column
     * @param targetRow The row of the file
     * @param targetColumn The column of the file
     * @return The field in the row and column
     */
    public String field(int targetRow, int targetColumn){
        // Counter for rows and columns
        int rowNum = 0;
        int colNum = 0;
        String field;

        try{
            // Read the file
            File inFile = new File(fileName);
            // Throws exception if file not found.
            Scanner in = new Scanner(inFile);
            String allFields;

            // Flag for the field being quoted
            Boolean quotesFound = false;

            // While there is more to be read, increment rows
            while(in.hasNextLine()){
                // If current row is the target row
                if(rowNum == targetRow){
                    allFields = in.nextLine();

                    // Process characters within that string and leave the loop
                    for(int i = 0; i < allFields.length(); i++){
                        // Switch the flag based on whether the quote started or ended.
                        if(allFields.charAt(i) == '\"' && quotesFound == false){
                            quotesFound = true;
                        }
                        else if (allFields.charAt(i) == '\"' && quotesFound == true){
                            quotesFound = false;
                        }
                        // If the start of the field is found and the comma that is found is not quoted
                        if((i == 0) || (allFields.charAt(i) == ',' && quotesFound == false)){ 
                            // If target column matches
                            if(colNum == targetColumn){
                                // Make a substring at the start of the column
                                field = allFields.substring(i+1);
                                // Look for where the column ends
                                for(int j = 0; j < field.length(); j++){
                                    // If the field starts with a quote
                                    if(field.charAt(j) == '\"'){
                                        // Look for the end of the quote
                                        for(int k = j+1; k < field.length(); k++){
                                            // If the field ends with a quote and the character after is not a quote.
                                            if(field.charAt(k) == '\"' && field.charAt(k+1) != '\"'){
                                                field = field.substring(j+1, k);
                                                in.close();
                                                return field;
                                            }
                                            // If the field ends with a quote but the character after is a quote
                                            // A quote within a quote
                                            if(field.charAt(k) == '\"' && field.charAt(k+1) == '\"'){
                                                // Start is the section before the quote within the quote
                                                String start = field.substring(j+1, k);
                                                // End is the quote within the quote
                                                String end = field.substring(k+1);
                                                // Find the end of the quote within the quote - that is the end of the quoted field
                                                for(int m = 1; m < end.length(); m++){
                                                    if(end.charAt(m) == '\"'){
                                                        end = end.substring(0, m+1);
                                                        in.close();
                                                        return start + end;
                                                    }
                                                }

                                            }
                                        }
                                    }

                                    // If there are no quotes and a comma is found, the target field is found.
                                    if(field.charAt(j) == ',' && quotesFound == false){
                                        field = field.substring(0, j);
                                        in.close();
                                        return field;
                                    }
                                }
                            }
                            // Increment column if no match.
                            else{
                                colNum++;
                            }
                        }
                    }
                    break;
                }
                // Increment row and move to the next row
                else{
                    rowNum++;
                    in.nextLine();
                }
            }
            in.close();
        }
        // Catch exception
        catch(FileNotFoundException exception){
            System.out.println("File not found");
        }
        return "NULL";
    }
}
