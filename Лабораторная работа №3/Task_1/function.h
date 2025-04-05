#ifndef FUNCTION_H
#define FUNCTION_H
#include <QString>

class Function {
   public:
    Function();
    QString translate(double a);
    QString intToBinary(int n);
    QString fracToBinary(double frac, int depth);
};

#endif	// FUNCTION_H
