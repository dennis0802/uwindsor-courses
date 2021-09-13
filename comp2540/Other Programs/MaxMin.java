
/**
 * Find the max and min of an array
 */
public class MaxMin {
    /**
     * Determine the max and min
     * @param arr The array to search
     * @return The max and min as a pair (max, min)
     */
    static Pair<Integer, Integer> maxMin(int[] arr){
        Pair<Integer, Integer> maxMin1;
        Pair<Integer, Integer> maxMin2;

        // Base case A: one element remains in the array, it is both the max and min
        if(arr.length == 1){
            return new Pair<Integer, Integer>(arr[0], arr[0]);
        }
        // Base case B: two elements remain in the array, compare
        else if(arr.length == 2){
            return new Pair<Integer, Integer>(Math.max(arr[0], arr[1]), Math.min(arr[0], arr[1]));
        }
        else{
            // Divide into two subsets
            int[] arr1 = new int[arr.length/2], arr2;

            // Even numbered lengths
            if(arr.length % 2 == 0){
                arr2 = new int[arr.length/2];
                for(int i = 0; i < arr.length/2; i++){
                    arr1[i] = arr[i];
                    arr2[i] = arr[arr.length/2 + i];
                }
            }
            // Odd numbered lengths
            else{
                arr2 = new int[arr.length/2 + 1];
                for(int i = 0; i < arr.length/2; i++){
                    arr1[i] = arr[i];
                }
                for(int i = 0; i < arr.length/2 + 1; i++){
                    arr2[i] = arr[arr.length/2 + i];
                }
            }

            // Recursive cases
            maxMin1 = maxMin(arr1);
            maxMin2 = maxMin(arr2);
            return new Pair<Integer, Integer>(Math.max(maxMin1.getFirst(), maxMin2.getFirst()), Math.min(maxMin1.getSecond(), maxMin2.getSecond()));
        }
    }

    public static void main(String args[]){
        int[] arr = {1, 4, 6, 4, 9, 2, 3, 0};
        System.out.println(maxMin(arr));
    }
}
