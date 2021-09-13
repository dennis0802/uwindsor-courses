import java.util.ArrayList;

public class Median{
    public static void main(String args[]){
        ArrayList<Integer> list = new ArrayList<Integer>();
        int totalElements = 20;
        for(int i = 0; i < totalElements; i++){
            list.add(i);
        }

        if(totalElements % 2 != 0){
            System.out.println("The median is " + list.get(totalElements/2));
        }
        else{
            System.out.println("The median is " + (double)(list.get((totalElements/2) - 1) + list.get(totalElements/2))/2);

        }
    }
}