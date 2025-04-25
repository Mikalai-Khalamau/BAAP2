#ifndef SORTS_H
#define SORTS_H
#include <vector>
class Sorts
{
public:
    Sorts();
    void HeapSort(int arr[], int n);
    void Heapify(int arr[], int n, int i);
    void QuickSort(int *arr,int size);
    void MergeSort(int *arr,int l,int r);
    int BinSearch(std::vector<int>&arr,int digit);
};

#endif // SORTS_H
