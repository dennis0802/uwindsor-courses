public class QuickSort {
    /**
     * Perform quicksort
     * @param arr An unsorted array
     * @param first The first index
     * @param last The last index
     */
    static void quickSort(int[] arr, int first, int last){
        if(first < last){
            int pivot = partition(arr, first, last);
            quickSort(arr, first, pivot);
            quickSort(arr, pivot+1, last);
        }
    }

    /**
     * Partition the element in the list
     * @param arr The array
     * @param first The first element index
     * @param last The last element index
     * @return The partition index
     */
    static int partition(int[] arr, int first, int last){
        int firstElem = arr[first];
        int left = first-1;
        int right = last+1;

        while(true){
            // Move indices
            do{
                right--;
            }while(!(arr[right] <= firstElem));

            do{
                left++;
            }while(!(arr[left] >= firstElem));

            if(left < right){
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }
            // The left and right indices have crossed / met
            else{
                return right;
            }
        }
    }

    public static void main(String args[]){
        int arr[] = {5, 3, 2, 6, 4, 1, 3, 7};
        System.out.println("Before sorting: ");
        for(int num : arr){
            System.out.printf("%d, ", num);
        }

        quickSort(arr, 0, arr.length-1);

        System.out.println("\nSorted array: ");
        for(int num : arr){
            System.out.printf("%d, ", num);
        }
    }
}
