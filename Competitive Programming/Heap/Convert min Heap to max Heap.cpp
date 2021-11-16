/*
https://www.geeksforgeeks.org/convert-min-heap-to-max-heap/
Given array representation of min Heap, convert it to max Heap in O(n) time. 
Example : 
 

Input: arr[] = [3 5 9 6 8 20 10 12 18 9]
         3
      /     \
     5       9
   /   \    /  \
  6     8  20   10
 /  \   /
12   18 9 


Output: arr[] = [20 18 10 12 9 9 3 5 6 8] OR 
       [any Max Heap formed from input elements]

         20
       /    \
     18      10
   /    \    /  \
  12     9  9    3
 /  \   /
5    6 8 

The problem might look complex at first look. But our final goal is to only build the max heap. The idea is very simple – we simply build Max Heap without caring about the input. We start from the bottom-most and rightmost internal mode of min Heap and heapify all internal modes in the bottom-up way to build the Max heap.
Below is its implementation
 
*/

// A C++ program to convert min Heap to max Heap
#include <bits/stdc++.h>
using namespace std;

// to heapify a subtree with root at given index
void MaxHeapify(int arr[], int i, int n)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < n && arr[l] > arr[i])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, largest, n);
    }
}

// This function basically builds max heap
void convertMaxHeap(int arr[], int n)
{
    // Start from bottommost and rightmost
    // internal mode and heapify all internal
    // modes in bottom up way
    for (int i = (n - 2) / 2; i >= 0; --i)
        MaxHeapify(arr, i, n);
}

// A utility function to print a given array
// of given size
void printArray(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}

// Driver program to test above functions
int main()
{
    // array representing Min Heap
    int arr[] = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Min Heap array : ");
    printArray(arr, n);

    convertMaxHeap(arr, n);

    printf("\nMax Heap array : ");
    printArray(arr, n);

    return 0;
}