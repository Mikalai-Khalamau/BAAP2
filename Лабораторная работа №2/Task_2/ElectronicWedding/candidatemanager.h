#ifndef CANDIDATEMANAGER_H
#define CANDIDATEMANAGER_H

#include <QList>
#include <QVector>
#include "candidate.h"

/*
 * Класс CandidateManager отвечает за хранение и управление списком (динамическим массивом) объектов Candidate.
 * Выполняет функции:
 *  - инициализация / загрузка данных из файла
 *  - сохранение данных в файл
 *  - добавление кандидата
 *  - удаление кандидата
 *  - корректировка (редактирование) данных кандидата
 *  - сортировка
 *  - просмотр/поиск/формирование пар
 */
const QString kFileError = "Ошибка работы с файлом";

class CandidateManager {
   private:
    QVector<Candidate> candidates_;	 // Наш динамический массив (контейнер)

   public:
    CandidateManager();
    // Работа с файлами
    void loadFromFile(const QString& fileName) /*throw(QString)*/;
    void saveToFile(const QString& fileName) /*throw(QString)*/;

    // Методы управления
    void addCandidate(const Candidate& cand);
    void removeCandidate(int index);
    void editCandidate(int index, const Candidate& newData);

    // Просмотр списка
    const QVector<Candidate>& getCandidates() const;
    int size() const;

    // Сортировка (по убыванию возраста)
    void sortByAgeDescending();

    // Поиск пар
    QList<QPair<int, int>> findAllPairs() const;

    // Поиск всех кандидатов, которые подходят для одного заданного кандидата (по индексу в списке)
    QList<int> findMatchesFor(int index) const;
};

#endif	// CANDIDATEMANAGER_H
