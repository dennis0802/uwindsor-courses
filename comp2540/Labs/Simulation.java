import java.util.Random;

/**
 * To be used for generating random numbers for the simulations
 */
public class Simulation{
    public static void main(String args[]){
        Random gen = new Random();
        int num;
        int[] arrivals = new int[100];
        int[] services = new int[100];

        
        // Generate
        for(int i = 0; i < 100; i++){
            num = gen.nextInt(20) + 1;
            services[i] = num;
        }
        for(int i = 0; i < 100; i++){
            num = gen.nextInt(20) + 1;
            arrivals[i] = num;
        }

        // Print
        System.out.println("Services");
        for(int i = 0; i < 100; i++){
            if(i == 99){
                System.out.printf("%d", services[i]);
            }
            else{
                System.out.printf("%d, ", services[i]);
            }
        }
        System.out.println("\nArrivals");
        for(int i = 0; i < 100; i++){
            if(i == 99){
                System.out.printf("%d", arrivals[i]);
            }
            else{
                System.out.printf("%d, ", arrivals[i]);
            }
        }
    }
}
