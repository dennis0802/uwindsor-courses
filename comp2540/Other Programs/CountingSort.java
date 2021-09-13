import java.util.Arrays;

// Assumption: The numbers range from 1 to N, where N is the largest number in the array
public class CountingSort {
    /**
     * Perform counting sort
     * @param arrA An unsorted array
     * @param arrB Outputted array
     * @param largest Largest element in the array
     * @param size Size of the array
     */
    static void countingSort(int arrA[], int arrB[], int largest, int size){
        int arrC[] = new int[largest];

        // Count how many times i shows up
        for(int i = 0; i < size; i++){
            arrC[arrA[i]-1]++;
        }

        // Count how many elements are less than i
        for(int i = 1; i <= largest-1; i++){
            arrC[i] += arrC[i-1];
        }

        for(int num: arrC){
            System.out.printf("%d, ", num);
        }
        System.out.println("\n");

        for(int i = size-1; i >= 0; i--){
            arrB[arrC[arrA[i]-1]-1] = arrA[i];
            arrC[arrA[i]-1]--;
        }
    }

    /**
     * Perform counting sort without a second array
     * @param arrA An unsorted array
     * @param largest Largest element in the array
     * @param size Size of the array
     */
    static void countingSortB(int arrA[], int largest, int size){
        int arrC[] = new int[largest + 1];
        for(int i = 0 ; i < size; i++){
            arrC[arrA[i]]++;
        }
        int pos = 0;

        for(int i = 0; i <= largest; i++){
            for(int j = 0; j < arrC[i]; j++){
                arrA[pos] = i;
                pos++;
            }
        }
    }

    public static void main(String args[]){
        int[] arr = {3, 6, 4, 1, 3, 4, 1, 4, 7, 9, 3};
        int[] arrB = new int[arr.length];
        
        int max = Arrays.stream(arr).max().getAsInt();

        System.out.println("Before sorting: ");
        for(int num : arr){
            System.out.printf("%d, ", num);
        }
        System.out.println("\n");

        countingSort(arr, arrB, max, arrB.length);
        countingSortB(arr, max, arr.length);

        System.out.println("Counting Sort with arrB:");
        for(int num : arrB){
            System.out.printf("%d, ", num);
        }

        System.out.println("\n\nCounting Sort without arrB:");
        for(int num : arr){
            System.out.printf("%d, ", num);
        }
    }
}
