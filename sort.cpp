#include <iostream>

using namespace std;

template<typename T>
int compare(T first, T second)
{
  if (first > second)
    return 1;
  else
    return 0;
}

template<typename T>
void bubble(T array[], int length, int (*compare)(T, T))
{
  for (int i=0; i < length; ++i) {
    for (int j=0; j < length - 1 - i; ++j) {
      if (compare(array[j], array[j+1]) == 1) {
        T tmp = array[j];
        array[j] = array[j+1];
        array[j+1] = tmp;
      }
    }
  }
}

template<typename T>
void swap(T *first, T *second)
{
  T tmp = *first;
  *first = *second;
  *second = tmp;
}

template<typename T>
int partition(T array[], int left, int right, int(*compare)(T, T))
{
  T prot = array[left];
  int index = left + 1;
  for (int i=index; i <= right; ++i) {
    if (array[i] < prot) {
      swap(&array[i], &array[index]);
      ++index;
    }
  }
  swap(&array[left], &array[index - 1]);
  return index - 1;
}

template<typename T>
void quickSort(T array[], int left, int right, int(*compare)(T, T))
{
  if (left < right) {
    int partitionIndex = partition(array, left, right, compare);
    quickSort(array, left, partitionIndex - 1, compare);
    quickSort(array, partitionIndex + 1, right, compare);
  }
}

template<typename T>
void quick(T array[], int length, int(*compare)(T, T))
{
  quickSort(array, 0, length - 1, compare);
}

template<typename T>
void printArray(T array[], int length)
{
  for (int i=0; i<length; ++i) 
    cout << array[i] << " ";
  cout << endl;
}

int main()
{
  int array[] = { 3, 4, 1, 6, 2, 9, 2};
  //bubble(array, 6, compare);
  quick(array, 7, compare);
  printArray(array, 7);
}
