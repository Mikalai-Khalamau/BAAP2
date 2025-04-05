#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

/*
 * Константы для диапазонов значений.
 * Эти константы используются при валидации ввода и при установке значений по умолчанию.
 */
const int kMinAge = 0;
const int kMaxAge = 200;
const int kMinHeight = 0;
const int kMaxHeight = 300;
const int kMinWeight = 0;
const int kMaxWeight = 300;

/*
 * Класс Candidate хранит данные об одном кандидате службы знакомств.
 * Для каждого кандидата хранятся: порядковый номер, пол, ФИО, возраст, рост, вес,
 * а также требования к партнёру в виде диапазонов (min/max возраст, рост, вес).
 *
 * Все поля объявлены как private. Для доступа используются методы get/set.
 */
class Candidate {
   private:
    int id_;	   // Порядковый номер кандидата
    QString sex_;  // Пол (например, "М" или "Ж")
    QString fio_;  // ФИО кандидата
    int age_;	   // Возраст
    int height_;   // Рост
    int weight_;   // Вес

    // Требования к партнёру (диапазоны)
    int min_age_;	  // Минимальный возраст партнёра
    int max_age_;	  // Максимальный возраст партнёра
    int min_height_;  // Минимальный рост партнёра
    int max_height_;  // Максимальный рост партнёра
    int min_weight_;  // Минимальный вес партнёра
    int max_weight_;  // Максимальный вес партнёра

   public:
    // Конструкторы
    Candidate();
    Candidate(int id, const QString& sex, const QString& fio, int age,
              int height, int weight, int min_age, int max_age, int min_height,
              int max_height, int min_weight, int max_weight);

    // Методы получения (get)
    int getId() const;
    QString getSex() const;
    QString getFio() const;
    int getAge() const;
    int getHeight() const;
    int getWeight() const;
    int getMinAge() const;
    int getMaxAge() const;
    int getMinHeight() const;
    int getMaxHeight() const;
    int getMinWeight() const;
    int getMaxWeight() const;

    // Методы установки (set)
    void setId(int value);
    void setSex(const QString& value);
    void setFio(const QString& value);
    void setAge(int value);
    void setHeight(int value);
    void setWeight(int value);
    void setMinAge(int value);
    void setMaxAge(int value);
    void setMinHeight(int value);
    void setMaxHeight(int value);
    void setMinWeight(int value);
    void setMaxWeight(int value);
};

#endif	// CANDIDATE_H
