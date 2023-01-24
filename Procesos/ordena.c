#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

void bubble_sort(int *array, int array_size);
void merge_arrays(int *A,int *L,int leftCount,int *R,int rightCount);

/**
 * Function that does a bubble sort.
 * 
 * @param array         List of integers we want to order.
 * @param array_size    Size of list we're ordering.
 *
 * @return Ordered cluster of what we ordered
 */
void bubble_sort(int *array, int array_size) {
    int sortFlag = 0;
    int tempHolder = 0;

    do {
        sortFlag = 1;
        // printf("\nIteration: ");
        for (int i = 1; i < array_size; i++) {
            if (array[i-1] > array[i]) {
                tempHolder = array[i-1];
                array[i-1] = array[i];
                array[i] = tempHolder;
            } else sortFlag++;
            // if (i-1 < array_size) printf("%i, ", array[i-1]);
            // if (i == array_size-1) printf("%i. ", array[i]);
        }
        // printf("Made %i moves.", array_size-sortFlag);
    } while (sortFlag < array_size);
    // printf("\n");
}

/**
 * Function to merge left and right array into the original array. 
 * 
 * @param original_array    Array we started with.
 * @param left              What we consider the left array.
 * @param left_count        Number of elements in the left array.
 * @param right             What we consider the right array.
 * @param right_count       Number of elements in the right array.
 */
void merge_arrays(int *original_array,int *left,int left_count,int *right,int right_count) {
        int i = 0; // i - to mark the index of left subarray (left).
        int j = 0; // j - to mark the index of right subarray (right).
    int k = 0; // k - to mark the index of merged subarray (original_array).
         

        while(i < left_count && j < right_count) {
                if(left[i]  < right[j]) original_array[k++] = left[i++];
                else original_array[k++] = right[j++];
        }
        while(i < left_count) original_array[k++] = left[i++];
        while(j < right_count) original_array[k++] = right[j++];
}
