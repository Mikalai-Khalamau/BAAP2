#include <iostream>

// Базовый абстрактный класс для представления арифметического выражения
class Expression {
public:
    // Виртуальный метод для вычисления значения выражения
    // Чисто виртуальный метод (= 0) делает класс абстрактным
    virtual double evaluate() = 0;

    // Виртуальный деструктор (необходим для корректного удаления объектов производных классов)
    virtual ~Expression() = default;
};

// Класс для представления числа
class Number : public Expression {
private:
    double number;  // Поле для хранения значения числа

public:
    // Конструктор, принимающий значение числа
    explicit Number(double num) : number(num) {}

    // Реализация виртуального метода evaluate для числа
    // Просто возвращает значение числа
    double evaluate() override {
        return number;
    }
};

// Класс для представления бинарной операции (+, -, *, /)
class BinaryOperation : public Expression {
private:
    Expression* leftOperand;  // Указатель на левый операнд (выражение)
    Expression* rightOperand; // Указатель на правый операнд (выражение)
    char type;                // Тип операции (+, -, *, /)

public:
    // Конструктор, принимающий левый операнд, тип операции и правый операнд
    BinaryOperation(Expression* left, char type, Expression* right)
        : leftOperand(left), rightOperand(right), type(type) {}

    // Деструктор
    // Освобождает память, выделенную для левого и правого операндов
    ~BinaryOperation() {
        delete leftOperand;
        delete rightOperand;
    }

    // Реализация виртуального метода evaluate для бинарной операции
    double evaluate() override {
        // Вычисляем значения левого и правого операндов
        double leftValue = leftOperand->evaluate();
        double rightValue = rightOperand->evaluate();

        // Выполняем операцию в зависимости от типа
        switch (type) {
            case '+':
                return leftValue + rightValue;  // Сложение
            case '-':
                return leftValue - rightValue;  // Вычитание
            case '*':
                return leftValue * rightValue;  // Умножение
            case '/':
                if (rightValue != 0) {
                    return leftValue / rightValue;  // Деление (если правый операнд не равен нулю)
                } else {
                    std::cout << "Ошибка: деление на ноль!\n";
                    return 0;  // Возвращаем 0 в случае деления на ноль
                }
            default:
                std::cout << "Ошибка: неизвестная операция!\n";
                return 0;  // Возвращаем 0 в случае неизвестной операции
        }
    }
};

// Точка входа в программу
int main() {
    // Создаем выражение (4.5 * 5)
    Expression* s = new BinaryOperation(new Number(4.5), '*', new Number(5));

    // Создаем выражение (3 + (4.5 * 5))
    Expression* expr = new BinaryOperation(new Number(3), '+', s);

    // Вычисляем и выводим результат
    std::cout << "Результат выполнения операции: " << expr->evaluate() << "\n";

    // Освобождаем память, выделенную для выражения
    delete expr;

    return 0;
}