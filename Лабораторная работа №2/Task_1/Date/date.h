#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
   public:
    Date();
    Date(int d, int m, int y);

    Date NextDay() const;
    Date PreviousDay() const;
    int Duration(const Date& other) const;
    int DaysTillBirthday(const Date& birthday) const;
    bool IsLeap() const;
    int WeekNumber() const;
    int DaysBetweenToday() const;

    std::string toString() const;
    bool operator<(const Date& other) const;

    int daysInMonth(int month, int year) const;
    bool isValidDate(int d, int m, int y) const;

    // Метод для проверки формата строки (ДД.ММ.ГГГГ)
    static bool isValidDateFormat(const std::string& dateStr);

   private:
    int day_, month_, year_;
};

#endif	// DATE_H
