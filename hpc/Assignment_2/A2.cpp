#include <iostream>
#include <omp.h>
using namespace std;

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n) {
    bool swapped = true;

    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = false;

        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
            
            //int numThreads = omp_get_num_threads();
            //cout << "Number of threads in the parallel for loop: " << numThreads << endl;
        }
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
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

// Parallel Merge Sort
void parallelMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                //int numThreads = omp_get_num_threads();
                //cout << "Number of threads in the first section: " << numThreads << endl;

                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                //int numThreads = omp_get_num_threads();
                //cout << "Number of threads in the second section: " << numThreads << endl;

                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Parallel Bubble Sort
    parallelBubbleSort(arr, n);

    cout << "Sorted array using Parallel Bubble Sort: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Parallel Merge Sort
    parallelMergeSort(arr, 0, n - 1);

    cout << "Sorted array using Parallel Merge Sort: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}