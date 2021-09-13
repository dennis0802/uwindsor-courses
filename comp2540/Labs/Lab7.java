/**
 * Developer: Dennis Dao
 * Date: Feb 22, 2021
 * version 1.0
 */

// Imports
import java.util.Random;

/**
 * A class to test MergeSort and InsertionSort
 * Placed in both in the same file to use same random numbers
 */
public class Lab7 {
    // Comparison counts
    static int mergeCount = 0;
    static long insertCount;

    /**
     * Merge sorted arrays
     * @param arr The main array
     * @param arrHalf1 The first half of the main array
     * @param arrHalf2 The last half of the main array
     */
    static void merge(int[] arr, int[] arrHalf1, int[] arrHalf2){
        int size1 = arrHalf1.length;
        int size2 = arrHalf2.length;
        int i = 0, j = 0, k = 0;

        // Compare values in both halves
        while(i < size1 && j < size2){
            if(arrHalf1[i] < arrHalf2[j]){
                arr[k] = arrHalf1[i];
                i++;
            }
            else{
                arr[k] = arrHalf2[j];
                j++;
            }
            mergeCount++;
            k++;
        }
        
        for(int m = i; m < size1; m++){
            arr[k] = arrHalf1[m];
            k++;
        }
        for(int m = j; m < size2; m++){
            arr[k] = arrHalf2[m];
            k++;
        }
    }

    /**
     * Perform merge sort
     * @param arr An unsorted array
     */
    static void mergeSort(int[] arr){
        int n = arr.length;

        if(n > 1){
            // Assign half of the lements
            int[] arr1 = new int[n/2];
            int[] arr2;

            // Even numbered lengths
            if(n % 2 == 0){
                arr2 = new int[n/2];
                for(int i = 0; i < n/2; i++){
                    arr1[i] = arr[i];
                    arr2[i] = arr[n/2 + i];
                }
            }
            // Odd numbered lengths
            else{
                arr2 = new int[n/2 + 1];
                for(int i = 0; i < n/2; i++){
                    arr1[i] = arr[i];
                }
                for(int i = 0; i < n/2 + 1; i++){
                    arr2[i] = arr[n/2 + i];
                }
            }
            mergeSort(arr1);
            mergeSort(arr2);
            merge(arr, arr1, arr2);
        }
        else{
            return;
        }
        
    }

    /**
     * Perform insertion sort
     * @param arr An unsorted array
     */
    static void insertionSort(int[] arr){
        int i = 1;

        while(i < arr.length){
            int j = i;

            // If the newly introduced element is already in sorted position
            if(arr[j-1] <= arr[j]){
                insertCount++;
            }

            while(j > 0 && arr[j-1] > arr[j]){
                insertCount++;
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
                j--;

                // Count the final "comparison"
                if(j > 0 && arr[j-1] <= arr[j]){
                    insertCount++;
                }
            }
            i++;
        }
    }

    public static void main(String args[]){
        int size = 5000;
        int[] arrMerge = new int[size], arrIns = new int[size];
        Random gen = new Random();

        // Fill up array
        for(int i = 0; i < size; i++){
            int num = gen.nextInt(100) + 1;
            arrMerge[i] = num;
            arrIns[i] = num;
        }

        // Merge Sort
        System.out.println("Merge sort with " + size + " elements");
        mergeSort(arrMerge);
        System.out.println(mergeCount + " comparisons made\n");

        // Insertion Sort
        System.out.println("Insertion sort with " + size + " elements");
        insertionSort(arrIns);
        System.out.println(insertCount + " comparisons made\n");
    }
}
