import java.util.Scanner;
import java.io.*;

/**
 * Utility class to avoid having to glance into the a5.output every test input
 * Automatically prints a5.output's contents
 */
public class Reader {
    public static void main(String args[]) throws Exception{
        File inFile = new File("a5.output");
        Scanner in = new Scanner(inFile);
        System.out.println(in.nextLine() + " program");
        in.close();
    }
}
