/*
 * Developer: Dennis Dao
 * June 28, 2022
 * v1.0
 */

// Program to sort an array of numbers with threads

#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 3

// Function prototypes
void *sorter(void *params); 
void *merger(void *params);
void printArray(int from, int to, int *arr); // Helper function to output array contents
void swap(int *num1, int *num2); // Helper function to swap when sorting

// Struct for the parameters that will be used.
typedef struct{
    int fromIndex;
    int toIndex;
} parameters;

// The global array to sort
int numbers[] = {7,12,19,3,18,4,2,6,15,8};
// Where the sorted numbers will be stored, cannot use the size constant for array so redoing 
// calculation, this is if the above list changes.
int sorted[sizeof(numbers)/sizeof(numbers[0])];
// Get size of the array, will determine the amount each thread must sort
const int size = sizeof(numbers)/sizeof(numbers[0]);

int main(void){
    // Variables
    parameters par1, par2;
    pthread_t tid[NUM_THREADS];

    // Assign indices
    par1.fromIndex = 0;
    par1.toIndex = size/2-1;
    par2.fromIndex = size/2;
    par2.toIndex = size-1;

    printf("Before sorting with threads: [");
    printArray(0, size, numbers);

    // Create threads to sort
    pthread_create(&tid[0], NULL, sorter, &par1);
    pthread_create(&tid[1], NULL, sorter, &par2);

    // Join the sorting threads BEFORE merging the halves
    for(int i = 0; i < NUM_THREADS-1; i++){
        pthread_join(tid[i], NULL);
    }

    // Output progress - sublists/halves sorted
    printf("After initially sorting each half with threads: [");
    printArray(0, size, numbers);

    // Create a thread to merge and allow it to finish
    pthread_create(&tid[2], NULL, merger, NULL);
    pthread_join(tid[2], NULL);

    // Output final result
    printf("After merging the sublists with threads: [");
    printArray(0, size, sorted);
    puts("Terminating program...");
    return 0;
}

// Function defintiions
// Helper function to print array contents
void printArray(int from, int to, int arr[]){
    for(int i = from; i < to; i++){
        if(i == to-1){
            printf("%d]\n\n", arr[i]);
        }
        else{
            printf("%d, ", arr[i]);
        }
    }
}

// Sorter function
void *sorter(void *params){
    parameters par = *(parameters*)params;

    printf("A thread will be sorting: [");
    // 1 added to lastIndex accomodate the function's for loop having '<' in the condition
    printArray(par.fromIndex, par.toIndex+1, numbers);

    // Sort using bubble sort; typically starts at index 0 / the starting index
    for(int i = par.fromIndex; i < par.toIndex; i++){

        // Indexing will work as usual with index 0 involved and less than the whole list's size
        if(par.fromIndex < size/2){
            for(int j = par.fromIndex; j < par.toIndex - i; j++){
                if(numbers[j] > numbers[j+1]){
                    swap(&numbers[j], &numbers[j+1]);
                }
            }
        }

        // To start at a higher index (halfway), the first half of the indices need to be accounted for.
        // Half of the list's length will be added to the inner for loop to do this.
        else{
            for(int j = par.fromIndex; j < par.toIndex - i + size/2; j++){
                if(numbers[j] > numbers[j+1]){
                    swap(&numbers[j], &numbers[j+1]);
                }
            }            
        }
    }
}

// Merger function, similar to MergeSort's merge function
void *merger(void *params){
    // maxIndex1 will handle indices up to 1st half, maxIndex2 will handle last half
    // i starts at index 0, j starts at halfway through, k is the index of the sorted array
    int maxIndex1 = size/2, maxIndex2 = size, i = 0, j = size/2, k = 0;
    
    // Compare values from both halves, similar to MergeSort's merging portion
    while(i < maxIndex1 && j < maxIndex2){
        if(numbers[i] < numbers[j]){
            sorted[k] = numbers[i];
            i++;
        }
        else{
            sorted[k] = numbers[j];
            j++;
        }
        k++;
    }

    /* Once a sublist has been exhausted, the rest of the elements in the remaining sublist follow in order
         ex. Total of 10 elements and the array is 0-indexed (half 1 has indices 0-4, half 2 has indices 5-9)
         When list1 has been exhausted, i will be equal to 5, 5 is not less than 5 so the 1st for loop fails to execute.
         Here, the remaining elements of sublist 2 would fall in the proper place
    */
    for(int m = i; m < maxIndex1; m++){
        sorted[k] = numbers[m];
        k++;
    }
    for(int m = j; m < maxIndex2; m++){
        sorted[k] = numbers[m];
        k++;
    }
}

// Helper function to swap when sorting
void swap(int *num1, int *num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
