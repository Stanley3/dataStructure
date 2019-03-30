#include <iostream>

using namespace std;

int leftChildIndex(int index) { return (index << 1) + 1; }
int rightChildIndex(int index) { return (index << 1) + 2; }
void swap(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void maxHeapify(int arr[], int index, int heapSize)
{
  int largest = 0;
  int left = leftChildIndex(index);
  int right = rightChildIndex(index);

  if ((left < heapSize) && (arr[left] > arr[index]))
    largest = left;
  else
    largest = index;

  if ((right < heapSize) && (arr[right] > arr[largest]))
    largest = right;

  if (largest != index) {
    swap(&arr[largest], &arr[index]);
    maxHeapify(arr, largest, heapSize);
  }
}

void buildMaxHeap(int arr[], int len)
{
  for (int i= (len >> 1); i >=0; --i) {
    maxHeapify(arr, i, len);
  }
}

void print(int arr[], int len)
{
  for (int i=0; i<len; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

void maxHeapSort(int arr[], int len)
{
  int heapSize = len;
  buildMaxHeap(arr, len);
  for (int i = len - 1; i >= 0; --i) {
    swap(&arr[0], &arr[i]);
    maxHeapify(arr, 0, i);
  }
}

int main()
{
  int array[] = {3, 5, 8, 9, 1, 4, 2, 0};
  cout << "before sort: ";
  buildMaxHeap(array, 8);
  print(array, 8);
  cout << "after sort: ";
  maxHeapSort(array, 8);
  print(array, 8);

  return 0;
}
