#include "ackerman.h"

Ackerman::Ackerman() {}

int Ackerman::function(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if ((m > 0) && (n == 0)) {
        return function(m - 1, 1);
    } else if ((m > 0) && (n > 0)) {
        return function(m - 1, function(m, n - 1));
    }
    return 0;
}
