#include "IntVector.h"
#include <stdio.h>

void printArray(int *array, size_t len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void initArray(IntVector *array)
{
    for (int i = 0; i < array->capacity; i++)
        int_vector_set_item(array, i, i + 1);
}

int main()
{
    size_t capacity = 10;
    IntVector *array1 = int_vector_new(capacity);
    printf("New Array1:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    initArray(array1);
    printf("Initialized Array1:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    IntVector *array2 = int_vector_copy(array1);
    printf("Copied Array2:\n");
    printArray(array2->data, int_vector_get_capacity(array2));
    printf("Array1[5] = %d\n", int_vector_get_item(array1, 5));
    int_vector_push_back(array1, 11);
    printf("Array1 with an element appended to the end:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    printf("Capacity: %ld, Size: %ld\n", int_vector_get_capacity(array1), int_vector_get_size(array1));
    int_vector_pop_back(array1);
    printf("Array1 with last element removed:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    int_vector_shrink_to_fit(array1);
    printf("Array1 after equating the size and capacity:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    int_vector_resize(array1, 5);
    printf("Array1 after resizing to 5:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    int_vector_reserve(array1, 20);
    printf("Array1 after changing the capacity to 20:\n");
    printArray(array1->data, int_vector_get_capacity(array1));
    int_vector_free(array1);
    int_vector_free(array2);
    return 0;
}
