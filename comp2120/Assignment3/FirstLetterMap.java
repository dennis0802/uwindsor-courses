/**
 * Developer: Dennis Dao
 * Date: Nov 16, 2020
 * Student Number: 110010116
 */

// Imports
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

/**
 * This makes a FirstLetterMap class
 */
public class FirstLetterMap{
    /**
     * Test the class
     * @param args not used
     */
    public static void main(String args[]){
        // Map of character and set of words
        Map<Character, Set<String>> letterMap = new TreeMap<>();
        // Sets of every letter
        Set<String> aWordsSet = new TreeSet<>();
        Set<String> bWordsSet = new TreeSet<>();
        Set<String> cWordsSet = new TreeSet<>();
        Set<String> dWordsSet = new TreeSet<>();
        Set<String> eWordsSet = new TreeSet<>();
        Set<String> fWordsSet = new TreeSet<>();
        Set<String> gWordsSet = new TreeSet<>();
        Set<String> hWordsSet = new TreeSet<>();
        Set<String> iWordsSet = new TreeSet<>();
        Set<String> jWordsSet = new TreeSet<>();
        Set<String> kWordsSet = new TreeSet<>();
        Set<String> lWordsSet = new TreeSet<>();
        Set<String> mWordsSet = new TreeSet<>();
        Set<String> nWordsSet = new TreeSet<>();
        Set<String> oWordsSet = new TreeSet<>();
        Set<String> pWordsSet = new TreeSet<>();
        Set<String> qWordsSet = new TreeSet<>();
        Set<String> rWordsSet = new TreeSet<>();
        Set<String> sWordsSet = new TreeSet<>();
        Set<String> tWordsSet = new TreeSet<>();
        Set<String> uWordsSet = new TreeSet<>();
        Set<String> vWordsSet = new TreeSet<>();
        Set<String> wWordsSet = new TreeSet<>();
        Set<String> xWordsSet = new TreeSet<>();
        Set<String> yWordsSet = new TreeSet<>();
        Set<String> zWordsSet = new TreeSet<>();

        // Read the file
        try{
            // File and scanner can throw FileNotFound exceptions
            File inputFile = new File("test2.txt");
            Scanner in = new Scanner(inputFile);

            // Add any words to the set of words
            while(in.hasNextLine()){
                String line = in.next().toLowerCase();
                // Edit the read data so it contains only the whole word (no symbols)
                // Symbols at the start of the word
                if(line.charAt(0) < 97 || line.charAt(0) > 122){
                    line = line.substring(1);
                }
                // Symbols at the end of the word
                if(line.charAt(line.length()-1) < 97 || line.charAt(line.length()-1) > 122){
                    line = line.substring(0, line.length()-1);
                    // Run the if statement a 2nd time to catch any straggling symbols (ex. marmalade', will turn into marmalade' after the first if)
                    // Also to avoid erasing any actual letters when done in the first if statement
                    if(line.charAt(line.length()-1) < 97 || line.charAt(line.length()-1) > 122){
                        line = line.substring(0, line.length()-1);
                    }
                }

                // Check the first letter and place it into the corresponding set
                if(line.charAt(0) == 'a'){
                    aWordsSet.add(line);
                }
                else if(line.charAt(0) == 'b'){
                    bWordsSet.add(line);
                }
                else if(line.charAt(0) == 'c'){
                    cWordsSet.add(line);
                }
                else if(line.charAt(0) == 'd'){
                    dWordsSet.add(line);
                }
                else if(line.charAt(0) == 'e'){
                    eWordsSet.add(line);
                }
                else if(line.charAt(0) == 'f'){
                    fWordsSet.add(line);
                }
                else if(line.charAt(0) == 'g'){
                    gWordsSet.add(line);
                }
                else if(line.charAt(0) == 'h'){
                    hWordsSet.add(line);
                }
                else if(line.charAt(0) == 'i'){
                    iWordsSet.add(line);
                }
                else if(line.charAt(0) == 'j'){
                    jWordsSet.add(line);
                }
                else if(line.charAt(0) == 'k'){
                    kWordsSet.add(line);
                }
                else if(line.charAt(0) == 'l'){
                    lWordsSet.add(line);
                }
                else if(line.charAt(0) == 'm'){
                    mWordsSet.add(line);
                }
                else if(line.charAt(0) == 'n'){
                    nWordsSet.add(line);
                }
                else if(line.charAt(0) == 'o'){
                    oWordsSet.add(line);
                }
                else if(line.charAt(0) == 'p'){
                    pWordsSet.add(line);
                }
                else if(line.charAt(0) == 'q'){
                    qWordsSet.add(line);
                }
                else if(line.charAt(0) == 'r'){
                    rWordsSet.add(line);
                }
                else if(line.charAt(0) == 's'){
                    sWordsSet.add(line);
                }
                else if(line.charAt(0) == 't'){
                    tWordsSet.add(line);
                }
                else if(line.charAt(0) == 'u'){
                    uWordsSet.add(line);
                }
                else if(line.charAt(0) == 'v'){
                    vWordsSet.add(line);
                }
                else if(line.charAt(0) == 'w'){
                    wWordsSet.add(line);
                }
                else if(line.charAt(0) == 'x'){
                    xWordsSet.add(line);
                }
                else if(line.charAt(0) == 'y'){
                    yWordsSet.add(line);
                }
                else if(line.charAt(0) == 'z'){
                    zWordsSet.add(line);
                }
            }
            in.close();
        }
        // Catch exceptions
        catch(FileNotFoundException exception){
            System.out.println("File not found");
            return;
        }

        // Place the key and the set of words into the map if they have at least one element present (not empty)
        if(aWordsSet.isEmpty() == false){
            letterMap.put('a', aWordsSet);
        }
        if(bWordsSet.isEmpty() == false){
            letterMap.put('b', bWordsSet);
        }
        if(cWordsSet.isEmpty() == false){
            letterMap.put('c', cWordsSet);
        }
        if(dWordsSet.isEmpty() == false){
            letterMap.put('d', dWordsSet);
        }
        if(eWordsSet.isEmpty() == false){
            letterMap.put('e', eWordsSet);
        }
        if(fWordsSet.isEmpty() == false){
            letterMap.put('f', fWordsSet);
        }
        if(gWordsSet.isEmpty() == false){
            letterMap.put('g', gWordsSet);
        }
        if(hWordsSet.isEmpty() == false){
            letterMap.put('h', hWordsSet);
        }
        if(iWordsSet.isEmpty() == false){
            letterMap.put('i', iWordsSet);
        }
        if(jWordsSet.isEmpty() == false){
            letterMap.put('j', jWordsSet);
        }
        if(kWordsSet.isEmpty() == false){
            letterMap.put('k', kWordsSet);
        }
        if(lWordsSet.isEmpty() == false){
            letterMap.put('l', lWordsSet);
        }
        if(mWordsSet.isEmpty() == false){
            letterMap.put('m', mWordsSet);
        }
        if(nWordsSet.isEmpty() == false){
            letterMap.put('n', nWordsSet);
        }
        if(oWordsSet.isEmpty() == false){
            letterMap.put('o', oWordsSet);
        }
        if(pWordsSet.isEmpty() == false){
            letterMap.put('p', pWordsSet);
        }
        if(qWordsSet.isEmpty() == false){
            letterMap.put('q', qWordsSet);
        }
        if(rWordsSet.isEmpty() == false){
            letterMap.put('r', rWordsSet);
        }
        if(sWordsSet.isEmpty() == false){
            letterMap.put('s', sWordsSet);
        }
        if(tWordsSet.isEmpty() == false){
            letterMap.put('t', tWordsSet);
        }
        if(uWordsSet.isEmpty() == false){
            letterMap.put('u', uWordsSet);
        }
        if(vWordsSet.isEmpty() == false){
            letterMap.put('v', vWordsSet);
        }
        if(wWordsSet.isEmpty() == false){
            letterMap.put('w', wWordsSet);
        }
        if(xWordsSet.isEmpty() == false){
            letterMap.put('x', xWordsSet);
        }
        if(yWordsSet.isEmpty() == false){
            letterMap.put('y', yWordsSet);
        }
        if(zWordsSet.isEmpty() == false){
            letterMap.put('z', zWordsSet);
        }

        // Print the keys and values of the map
        Set<Character> keySet = letterMap.keySet();
        for(char key : keySet){
            Set<String> words = letterMap.get(key);
            System.out.println(key + ": " + words);
        }     
    }
}
