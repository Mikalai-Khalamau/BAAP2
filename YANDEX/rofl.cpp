#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void Final(vector<int>& arr, int target, int count) {
    if (arr.empty() || count <= 0) {
        cout << "Некорректные входные данные\n";
        return;
    }

    sort(arr.begin(), arr.end());
//Бинарно находим итератор на минимальный элемент >=target
    auto it= lower_bound(arr.begin(), arr.end(), target);
    int idx;
    if (it == arr.begin()) {
        idx = 0;
    } else if (it == arr.end()) {
        idx = arr.size() - 1;
    } else {
        int left = *(it - 1);
        int right = *it;
        if (abs(left - target) <= abs(right - target)) {
            idx = (it - 1) - arr.begin(); // левый
        } else {
            idx = it - arr.begin(); //правый
        }
    }

    vector<int> removedElements;
    int left = idx - 1;
    int right = idx + 1;

    removedElements.push_back(arr[idx]);
//двигаем 2 указателя пока есть элементы и не набрали нужного количества
    // также записываем новые элементы
    while (removedElements.size() < count && (left >= 0 || right < arr.size())) {
        if (left >= 0 && right < arr.size()) {
            // Выбираем ближайший из left и right
            if (abs(arr[left] - target) <= abs(arr[right] - target)) {
                removedElements.push_back(arr[left]);
                left--;
            } else {
                removedElements.push_back(arr[right]);
                right++;
            }
        } else if (left >= 0) {
            removedElements.push_back(arr[left]);
            left--;
        } else if (right < arr.size()) {
            removedElements.push_back(arr[right]);
            right++;
        }
    }

//создаем новый массив после удаления
    sort(removedElements.begin(), removedElements.end());
    vector<int> newArr;
    int i = 0, j = 0;
    while (i < arr.size() && j < removedElements.size()) {
        if (arr[i] == removedElements[j]) {
            j++;
        } else {
            newArr.push_back(arr[i]);
        }
        i++;
    }
    while (i < arr.size()) {
        newArr.push_back(arr[i++]);
    }


    cout << "Исходный массив после удаления: ";
    for (int num : newArr) {
        cout << num << " ";
    }

    cout << "\nУдалённые элементы: ";
    for (int num : removedElements) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr;
    int target, count, num;

    cout << "Введите число, к которому ищем ближайшие элементы: ";
    cin >> target;
    cout << "Введите количество ближайших элементов для удаления: ";
    cin >> count;

    cout << "Вводите элементы вектора (закончите ввод любым нечисловым символом):\n";
    while (cin >> num) {
        arr.push_back(num);
    }

    Final(arr, target, count);

    return 0;
}