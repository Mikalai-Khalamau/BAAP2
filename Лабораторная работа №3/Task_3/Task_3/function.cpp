#include "function.h"

const int k10=10;

Function::Function() {}

int Function::translate(int a, int reversed) {
    if (a == 0)
    {
        return reversed;
    }
    else {
        int lastdigit = a % k10;
        return translate(a / k10, reversed * k10 + lastdigit);
    }
}
