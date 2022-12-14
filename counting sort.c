#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void display(int * sort,int size){
    for(int i = 0; i < size; i++){
        printf(" %d ", sort[i]);
    }
    printf("\n");
}

void set_into_zeros(int * array, int size){
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }
}

void shift_to_left(int * array, int size){
    for(int i = 0; i <= size; i++){
        array[i] = array[i + 1];
    }
    size = size - 1;
    array = realloc(array, size * sizeof(int));
}

void counting_sort(int * arrayA, int * arrayB, int k, int size){
    int * arrayC;
    k = k + 1; //since the larger number is the highest position of array
    arrayC = calloc(k, sizeof(int));

    //set all element of arrayC into zero
    for(int i = -1; i <= k; i++){
        arrayC[i] = 0;
    }
    //count the number of element correspond the position of arrayC
    for(int j = 0; j < size; j++){
        arrayC[arrayA[j]] = arrayC[arrayA[j]] + 1;
    }
    //check if we successfully allocate and count the elements
    printf("arrayC: ");
    display(arrayC, k);

    //add the value of previous element to current element. ex. 2, 4 ,3 should be 2,6,9
    for(int i = 1; i <= k; i++){
        arrayC[i] = arrayC[i] + arrayC[i - 1];
    }
    //sort the array
    for(int j = size - 1; j >= 0; j--){
        arrayB[arrayC[arrayA[j]]] = arrayA[j];
        arrayC[arrayA[j]] = arrayC[arrayA[j]] - 1;
    }
    //since the array stored value until position index 1, we shift the value towards left, to start into 0 index
    shift_to_left(arrayB, size);
}

int largerkey(int * array, int size){
    int larger = 0;
    for(int i = 0; i < size; i++){
        if(larger < array[i]){
            larger = array[i];
        }
    }
    return larger;
}

int main(){
    int size = 5;
    int * arrayA, * arrayB;
    arrayA = calloc(size, sizeof(int));
    arrayB = calloc(size, sizeof(int));

    srand(time(0));
    int low = 1, high = 20;
    for(int i = 0; i < size; i++){
        arrayA[i] = (rand() % high - low + 1) + low;
    }

    //original data
    printf("Original array: ");
    display(arrayA, size);
    //check if we get the exact larger element in array
    int key = largerkey(arrayA, size);
    printf("Larger key: %d\n", key);
    //set all the arrayB into zero
    set_into_zeros(arrayB, size);
    printf("ArrayB: ");
    display(arrayB, size);

    //sorting the arrayA then the output should be sorted which is arrayB
    counting_sort(arrayA,arrayB,key, size);

    //display again for checking the array A
    printf("ArrayA: ");
    display(arrayA, size);
    //Display the sorted array
    printf("ArrayB: ");
    display(arrayB, size);

    return 0;
}
