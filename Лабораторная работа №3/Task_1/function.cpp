#include "function.h"
#include <QString>
#include <cmath>

const int k20=20;

Function::Function() {}

QString Function::translate(double a) {
    // Обработка нуля


    if (a == 0.0) {
        return "0";
    }

    QString result;

    // Знаковый бит (0 или 1)
    result += (a < 0) ? "-" : "";  // Пробел для разделения
    a = std::abs(a);

    // Целая часть
    int int_part = static_cast<int>(a);
    result += intToBinary(int_part);

    // Дробная часть
    double frac_part = a - int_part;


    if (frac_part != 0.0) {
        result += ".";
        result += fracToBinary(frac_part, 0);
    }

    return result;
}

// Рекурсивный перевод целой части
QString Function::intToBinary(int n) {
    if (n == 0)
    {
        return "0";
    }
    if (n == 1)
    {
        return "1";
    }
    return intToBinary(n / 2) + QString::number(n % 2);
}

// Рекурсивный перевод дробной части (с глубиной)
QString Function::fracToBinary(double frac, int depth) {


    if (frac == 0.0 || depth >= k20) {  // Ограничение глубины
        return "";
    }
    frac *= 2;
    int bit = static_cast<int>(frac);
    return QString::number(bit) + fracToBinary(frac - bit, depth + 1);
}
