#include "algorithms.h"
#include <vector>

Algorithms::Algorithms() {}

int Algorithms::BinPow(int digit, int power, int mod) {
    int result = 1;
    digit %= mod;

    while (power > 0) {
        if (power % 2 == 1)
        {
            result = (1LL * result * digit) % mod;
        }

        digit = (1LL * digit * digit) % mod;
        power /= 2;
    }

    return result;
}


int Algorithms::InterpolationSearch(std::vector<int>&arr, int digit)
{

    int x = 0; //Текущая позиция массива, с которым сравнивается искомое
    int l = 0; //Левая граница области, где ведется поиск
    int r = arr.size()-1; //Правая граница области, где ведется поиск

    // digit //Значение, которое нужно найти
    bool found; //Переменка-флаг, принимающая True если искомое найдено

    /************ Начало интерполяции *******************************/

    //Цикл поиска по массиву, пока искомое не найдено
    //или пределы поиска еще существуют
    for (found = false; (arr[l]<digit) && (arr[r]>digit) && !found; )
    {
        //Вычисление интерполяцией следующего элемента, который будет сравниваться с искомым
        x = l + ((digit - arr[l]) * (r - l)) / (arr[r] - arr[l]);
        //Получение новых границ области, если искомое не найдено
        if (arr[x] < digit)
        {
            l = x + 1;
        }
        else if (arr[x] > digit)
        {
            r= x - 1;
        }
        else
        {
            found = true;
        }
    }

    /************** Конец интерполяции ***************************/

    //Если искомое найдено на границах области поиска, показать на какой границе оно
    if (arr[l]==digit)
    {
        return l;
    }
    else if (arr[r]==digit)
    {
        return r;
    }
    else
    {
        return -1;
    }
}

int Algorithms::BinSearch(std::vector<int>&arr,int digit)
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

