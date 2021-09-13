/**
 * Developer: Dennis Dao
 * Date: Mar 12, 2021
 * version 1.0
 */

public class HeapSort {
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
            // Change equality sign to smallest along with comparison to get min heap
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
        // Change equality sign to largest along with smallest node to get min heap
        if(tree[i] < tree[k]){
            int temp = tree[i];
            tree[i] = tree[k];
            tree[k] = temp;
        }
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
     * @param tree
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
        int[] tree = {2, 12, 10, 13, 17, 14, 11};

        System.out.println("Array before sorting");
        for(int num : tree){
            System.out.printf("%d, ", num);
        }
        System.out.println("\n");

        heapSort(tree);

        System.out.println("Array after HeapSort");
        for(int num : tree){
            System.out.printf("%d, ", num);
        }
    }
}
