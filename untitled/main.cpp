#include <iostream>

// Базовый абстрактный класс для выражений
class Expression {
public:
    // Виртуальный метод для вычисления значения выражения
    virtual double evaluate() = 0;

    // Виртуальный деструктор для корректного удаления объектов производных классов
    virtual ~Expression() = default;
};

// Класс для представления числа
class Number : public Expression {
private:
    double value;  // Значение числа
public:
    // Конструктор, принимающий значение числа
    explicit Number(double value) {
        this->value = value;
    }

    // Реализация виртуального метода evaluate для числа
    double evaluate() override {
        return value;  // Возвращает значение числа
    }
};

// Класс для представления бинарной операции
class BinaryOperation : public Expression {
private:
    Expression* leftOperand;   // Левый операнд (выражение)
    Expression* rightOperand;  // Правый операнд (выражение)
    char operationType;        // Тип операции (+, -, *, /)
public:
    // Конструктор, принимающий левый операнд, тип операции и правый операнд
    BinaryOperation(Expression* leftOperand, char operationType, Expression* rightOperand) {
        this->leftOperand = leftOperand;
        this->rightOperand = rightOperand;
        this->operationType = operationType;
    }

    // Деструктор для освобождения памяти, выделенной для операндов
    ~BinaryOperation() {
        delete leftOperand;
        delete rightOperand;
    }

    // Реализация виртуального метода evaluate для бинарной операции
    double evaluate() override {
        // Вычисляем значение левого и правого операндов
        double leftValue = leftOperand->evaluate();
        double rightValue = rightOperand->evaluate();

        // Выполняем операцию в зависимости от operationType
        switch (operationType) {
            case '+':
                return leftValue + rightValue;  // Сложение
            case '-':
                return leftValue - rightValue;  // Вычитание
            case '*':
                return leftValue * rightValue;  // Умножение
            case '/':
                if (rightValue != 0) {
                    return leftValue / rightValue;  // Деление, если правый операнд не равен нулю
                } else {
                    std::cout << "Ошибка: Деление на ноль!\n";  // Ошибка деления на ноль
                    return 0;
                }
            default:
                std::cout << "Ошибка: Неизвестный тип операции!\n";  // Неизвестный тип операции
                return 0;
        }
    }
};

// Функция для проверки, указывают ли два указателя на объекты одного и того же класса
bool check_equals(Expression const* left, Expression const* right) {
    // Приводим указатели к типу void** и сравниваем адреса таблиц виртуальных методов (VMT)
    return *(void**)left == *(void**)right;
}

int main() {
    // Создаем объекты чисел
    auto* number1 = new Number(1);  // Число 1
    auto* number2 = new Number(2);  // Число 2

    // Создаем объекты бинарных операций
    auto* subtraction = new BinaryOperation(number1, '-', number2);  // Выражение: 1 - 2
    auto* division = new BinaryOperation(number1, '/', number2);     // Выражение: 1 / 2

    // Выводим адреса таблиц виртуальных методов (VMT) для каждого объекта
    std::cout << "Адреса таблиц виртуальных методов (VMT):\n";
    std::cout << *(void**)number1 << "\t- number1\n";
    std::cout << *(void**)number2 << "\t- number2\n";
    std::cout << *(void**)subtraction << "\t- subtraction\n";
    std::cout << *(void**)division << "\t- division\n\n";

    // Проверяем, являются ли объекты одного и того же класса
    std::cout << "Являются ли subtraction и division объектами одного класса? "
              << (check_equals(subtraction, division) ? "Да\n" : "Нет\n");  // Ожидается Да (оба BinaryOperation)
    std::cout << "Являются ли number1 и division объектами одного класса? "
              << (check_equals(number1, division) ? "Да\n" : "Нет\n");      // Ожидается Нет (Number и BinaryOperation)

    // Освобождаем память, выделенную для объектов
    delete number1;
    delete number2;
    delete subtraction;
    delete division;

    return 0;
}