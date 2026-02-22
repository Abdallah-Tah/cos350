/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 9
Date: Feb. 21, 2026
*/

#include <stdio.h>
#include <stdlib.h>

#define N 1001

void malloc_array(char *array[], int size, int bytes);
void print_result(char *array[], int size, int bytes);
void cleanup(char *array[], int size);

/* Main function */
int main(void)
{
    // Array of different sizes to allocate
    int sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    // Number of different sizes
    int num_sizes = 9;
    // Loop through each size
    for (int i = 0; i < num_sizes; i++)
    {
        char *array[N];

        malloc_array(array, N, sizes[i]);
        print_result(array, N, sizes[i]);
        cleanup(array, N);
    }

    return 0;
}

/* Allocate memory for an array of strings */
void malloc_array(char *array[], int size, int bytes)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = malloc(bytes);
        if (array[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
}

/* Print the results */
void print_result(char *array[], int size, int bytes)
{
    // Calculate the difference between the first and last allocated blocks
    long diff = (long)array[size - 1] - (long)array[0];

    // Make sure the difference is not negative
    if (diff < 0)
        diff = -diff;

    // Print the results
    printf("\nSize of malloc: %d bytes\n", bytes);
    printf("Address of first block (array[0]): %p\n", (void *)array[0]);
    printf("Address of last block (array[%d]): %p\n", size - 1, (void *)array[size - 1]);
    printf("Difference between array 0 and array %d: %ld\n", size - 1, diff);
    printf("\nArray element addresses:\n");
    printf("&array[0]: %p\n", (void *)&array[0]);
    printf("&array[%d]: %p\n", size - 1, (void *)&array[size - 1]);
    printf("Array element difference: %ld\n",
           (long)&array[size - 1] - (long)&array[0]);
}

/* Cleanup allocated memory */
void cleanup(char *array[], int size)
{
    // Free each allocated block
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
    }
}