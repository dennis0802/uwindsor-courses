/**
 * Developer: Dennis Dao
 * Date: Mar 14, 2021
 * version 1.0
 */

// Imports
import java.util.Random;

// This program performs heap sort and its various operations
public class HeapSort {
    // Comparison counts
    static int heapifyCount;

    /**
     * Heapify the values
     * @param tree The tree of values
     * @param i Start index
     * @param j Last index
     */
    static void heapify(int[] tree, int i, int j){
        int k;

        // Tree has 2 children
        if(2*i+2<= j){
            // Index of the largest child node
            if(tree[2*i+1] > tree[2*i+2]){
                k = 2*i+1;
            }
            else{
                k = 2*i+2;
            }
        }
        // Tree has 1 child
        else if(2*i+1<= j){
            k = 2*i+1;
        }
        // No children
        else{
            return;
        }

        // Swap
        if(tree[i] < tree[k]){
            int temp = tree[i];
            tree[i] = tree[k];
            tree[k] = temp;
        }
        heapifyCount++;
        heapify(tree, k, j);
    }

    /**
     * Build a heap from the tree
     * @param tree The tree of values
     */
    static void buildHeap(int[] tree){
        for(int i = tree.length / 2 - 1; i >= 0; i--){
            heapify(tree, i, tree.length-1);
        }
    }

    /**
     * Perform heapsort
     * @param tree The tree of values
     */
    static void heapSort(int[] tree){
        buildHeap(tree);

        for(int i = tree.length-1; i >= 1; i--){
            int temp = tree[0];
            tree[0] = tree[i];
            tree[i] = temp;
            heapify(tree, 0, i-1);
        }
    }
    public static void main(String args[]){
        // Variable defintions
        Random gen = new Random();
        int[] heapArray = {4, 2, 1, 8, 6, 5, 10, 9, 11, 16};
        int[] buildHeapArray = {12, 10, 15, 9, 8, 7, 20};
        int[] toSort = new int[100];

        // Fill up array
        for(int i = 0; i < 100; i++){
            int num = gen.nextInt(500) + 1;
            toSort[i] = num;
        }

        // Heapify
        System.out.println("Before heapifying");
        for(int num: heapArray){
            System.out.printf("%d, ", num);
        }
        heapify(heapArray, 0, 9);
        System.out.println("\nAfter heapifying");
        for(int num: heapArray){
            System.out.printf("%d, ", num);
        }
        System.out.println("\nComparions made heapifying: " + heapifyCount + "\n");
        heapifyCount = 0;

        // Build heap
        System.out.println("Before building");
        for(int num: buildHeapArray){
            System.out.printf("%d, ", num);
        }
        buildHeap(buildHeapArray);
        System.out.println("\nAfter building");
        for(int num: buildHeapArray){
            System.out.printf("%d, ", num);
        }
        System.out.println("\nComparions made building: " + heapifyCount + "\n");
        heapifyCount = 0;

        // HeapSort
        System.out.println("Before HeapSort");
        for(int num: toSort){
            System.out.printf("%d, ", num);
        }
        System.out.println("\nAfter HeapSort");
        heapSort(toSort);
        for(int num: toSort){
            System.out.printf("%d, ", num);
        }
        System.out.println("\nComparions made sorting: " + heapifyCount + "\n");
    }
}
