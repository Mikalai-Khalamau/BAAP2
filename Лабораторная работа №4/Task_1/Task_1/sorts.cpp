#include "sorts.h"
#include <algorithm>
#include <vector>

Sorts::Sorts() {}

void Sorts::Heapify(int arr[], int n, int i)
{
    // Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
    // индексом в arr[]. n - размер кучи

    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        Heapify(arr, n, largest);
    }
}

void Sorts::HeapSort(int arr[], int n)
{


    // Основная функция, выполняющая пирамидальную сортировку

        // Построение кучи (перегруппируем массив)
        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(arr, n, i);

        // Один за другим извлекаем элементы из кучи
        for (int i=n-1; i>=0; i--)
        {
            // Перемещаем текущий корень в конец
            std::swap(arr[0], arr[i]);

            // вызываем процедуру heapify на уменьшенной куче
            Heapify(arr, i, 0);
        }

}

void Sorts::QuickSort(int *arr, int size)
{
    int i=0;
    int j=size-1;

    int mid=arr[size/2];
    do
    {
    while (arr[i]<mid)
    {
        i++;
    }
    while (arr[j]>mid)
    {
        j--;
    }
    if (i<=j)
    {
        std::swap(arr[i],arr[j]);
        i++;
        j--;
    }
    }
    while (i<=j);

    if (j>0)
    {
        QuickSort(arr,j+1);
    }
    if (i<size)
    {
        QuickSort(&arr[i], size - i);
    }

}

void Sorts::MergeSort(int *arr, int l,int r)
{
    if (l==r)
    {
        return ;
    }

    int mid=(l+r)/2;
    MergeSort(arr,l,mid);
    MergeSort(arr,mid+1,r);

    std::vector <int> temp;

    for (int i = l, j = mid + 1; i <= mid || j <= r;) {
        // Если одна из частей закончилась, добавляем элемент из другой
        if (i > mid) {
            temp.push_back(arr[j++]);
        } else if (j > r) {
            temp.push_back(arr[i++]);
            // Иначе добавляем меньший из текущих элементов
        } else if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }

    // Копируем отсортированный отрезок из временного массива в arr.
    for (int i = 0; i < temp.size(); i++) {
        arr[l + i] = temp[i];
    }
}

int Sorts::BinSearch(std::vector<int>&arr,int digit)
{
    int left=0;
    int right=0;
    if (arr.size()>0)
    {
    right=arr.size()-1;
    }
    while (left<=right)
    {
        int m=(left+right)/2;
        if (arr[m]>digit)
        {
            right=m-1;
        }
        else if (arr[m]<digit)
        {
            left=m+1;
        }
        else
        {
            return m;
        }
    }
        return -1;

}
