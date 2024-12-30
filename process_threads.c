#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Structure for passing data to threads
typedef struct {
    int *arr;
    int left;
    int right;
} ThreadData;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void *mergeSort(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int left = data->left;
    int right = data->right;
    int *arr = data->arr;
    
    printf("Thread ID: %ld, Process ID: %d, Range: [%d, %d]\n", pthread_self(), getpid(), left, right);
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        ThreadData leftData = {arr, left, mid};
        ThreadData rightData = {arr, mid + 1, right};
        
        pthread_t leftThread, rightThread;
        printf("Creating thread for left part [%d, %d]\n", left, mid);
        pthread_create(&leftThread, NULL, mergeSort, &leftData);
        
        printf("Creating thread for right part [%d, %d]\n", mid + 1, right);
        pthread_create(&rightThread, NULL, mergeSort, &rightData);
        
        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);
        
        merge(arr, left, mid, right);
    }
    
    return NULL;
}

int main() {
    printf("Threads And Processes : Multithreading\n");
    printf("Process is a running program with its own memory, while a thread is a smaller unit within \n");
    printf("a process that runs concurrently. Multithreading uses multiple threads to execute tasks\n");
    printf("simultaneously, improving efficiency. In merge sort, multithreading allows different threads\n");
    printf("to sort subarrays in parallel and then merge them, speeding up the overall sorting process.\n");
    printf("\n");
    int n;
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Given array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    ThreadData mainData = {arr, 0, n - 1};
    
    pthread_t mainThread;
    pthread_create(&mainThread, NULL, mergeSort, &mainData);
    pthread_join(mainThread, NULL);
    
    printf("Sorted array is \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    free(arr);
    
    return 0;
}
