#include "file_utils.h"
#include <QByteArray>
#include <QFile>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

const int k10 = 10;

// Функция для чтения дат из файла (ожидается, что каждая строка содержит дату в формате ДД.ММ.ГГГГ)
std::vector<Date> ReadDatesFromFile(const std::string& filename) {
    std::vector<Date> dates;
    std::ifstream file(filename);


    if (!file) {
        throw std::runtime_error("Не удалось открыть файл!");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int d, m, y;
        char dot1, dot2;


        if (iss >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.') {
            dates.emplace_back(d, m, y);
        } else {
            std::cerr << "Ошибка в строке: " << line << std::endl;
        }
    }
    return dates;
}

// Добавление даты в конец файла


bool AppendDateToFile(const std::string& filename, const Date& date) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        return false;
    }
    // Записываем дату и перевод строки; т.к. формат фиксированный (10 символов) + '\n'
    file << date.toString() << "\n";
    return file.good();
}

// Изменение даты по индексу в файле (без полной перезаписи)
// Предполагается, что файл организован построчно, каждая строка – дата формата ДД.ММ.ГГГГ (10 символов) + перевод строки (итого 11 байт)


bool ModifyDateInFile(const std::string& filename, int index,
                      const Date& newDate) {
    std::fstream file(filename, std::ios::in | std::ios::out);
    if (!file) {
        return false;
    }
    const int record_length =
        11;	 // 10 символов даты + 1 символ перевода строки
    file.seekp(index * record_length, std::ios::beg);
    if (file.fail()) {
        return false;
    }
    // Перезаписываем запись новой датой; если строка не содержит перевода строки, добавляем его
    std::string new_record = newDate.toString();
    if (new_record.size() < k10) {
        return false;
    }
    file << new_record << "\n";
    return file.good();
}

// Удаление даты по индексу из файла без полной перезаписи
// Реализовано через сдвиг содержимого после удаляемой записи и усечение файла


bool DeleteDateFromFile(const std::string& filename, int index) {
    // Используем QFile из Qt для удобного усечения файла
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    }
    const qint64 record_size = 11;	// 10 символов даты + перевод строки
    qint64 pos = index * record_size;
    if (pos > file.size()) {
        file.close();
        return false;
    }
    // Переходим к позиции сразу после удаляемой записи
    file.seek(pos + record_size);
    QByteArray rest = file.readAll();
    // Возвращаемся к позиции удаления
    file.seek(pos);
    // Перезаписываем оставшиеся данные
    file.write(rest);
    // Усечем файл до нового размера
    file.resize(file.size() - record_size);
    file.close();
    return true;
}
