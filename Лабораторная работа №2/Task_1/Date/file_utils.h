#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>
#include "date.h"

// Функция для чтения дат из файла
std::vector<Date> ReadDatesFromFile(const std::string& filename);

// Новые функции для модификации файла без полной перезаписи
// Добавление даты в конец файла
bool AppendDateToFile(const std::string& filename, const Date& date);

// Изменение даты по индексу (индекс записи в файле)
bool ModifyDateInFile(const std::string& filename, int index,
                      const Date& newDate);

// Удаление даты по индексу из файла
bool DeleteDateFromFile(const std::string& filename, int index);

#endif	// FILE_UTILS_H
