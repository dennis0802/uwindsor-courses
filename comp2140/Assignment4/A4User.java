import java.io.*;
import java_cup.runtime.Symbol;

public class A4User {
    public static void main(String args[])  throws Exception{
        File inputFile = new File("A4.tiny");
        A4Parser parser = new A4Parser(new A4Scanner(new FileInputStream(inputFile)));
        String javaProgram = (String)parser.debug_parse().value;
        FileWriter fw = new FileWriter(new File("A4.java"));
        fw.write(javaProgram);
        fw.close();
    }
}
