/**
 * Developer: Dennis Dao
 * Date: Feb 22, 2021
 * version 1.0
 */

/**
 * Test MergeSort
 */
public class MergeSort {
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

            System.out.println("Half 1:");
            for(int num : arr1){
                System.out.printf("%d, ", num);
            }
            System.out.println("\nHalf 2:");
            for(int num : arr2){
                System.out.printf("%d, ", num);
            }
            System.out.println();
            
            mergeSort(arr1);
            mergeSort(arr2);
            merge(arr, arr1, arr2);

            System.out.println("\nMerged:");
            for(int num : arr){
                System.out.printf("%d, ", num);
            }
            System.out.println();
        }
        else{
            return;
        }
        
    }

    public static void main(String args[]){
        int[] arr = {2, 7, 3, 4, 9, 8, 5, 6};
        mergeSort(arr);

        System.out.println("\nSorted array: ");
        for(int i = 0; i < arr.length; i++){
            if(i != arr.length-1){
                System.out.printf("%d, ", arr[i]);
            }
            else{
                System.out.printf("%d", arr[i]);
            }
        }
        System.out.println();
    }
}
