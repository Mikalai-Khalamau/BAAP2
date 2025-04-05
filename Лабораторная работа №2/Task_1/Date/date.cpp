#include "date.h"
#include <cctype>
#include <ctime>
#include <sstream>

// Объявление всех магических констант
const int k1900 = 1900;
const int k2000 = 2000;
const int k1 = 1;
const int k2 = 2;
const int k4 = 4;
const int k5 = 5;
const int k7 = 7;
const int k10 = 10;
const int k12 = 12;
const int k28 = 28;
const int k29 = 29;
const int k30 = 30;
const int k31 = 31;
const int k100 = 100;
const int k400 = 400;
const int k60 = 60;
const int k24 = 24;

// Конструктор по умолчанию (текущая дата)
Date::Date() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    day_ = now->tm_mday;
    month_ = now->tm_mon + k1;
    year_ = now->tm_year + k1900;
}

// Конструктор с параметрами
Date::Date(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day_ = d;
        month_ = m;
        year_ = y;
    } else {
        day_ = k1;
        month_ = k1;
        year_ = k2000;
    }
}

// Проверка корректности даты
bool Date::isValidDate(int d, int m, int y) const {


    if (y < 0) {
        return false;
    }


    if (m < k1 || m > k12) {
        return false;
    }


    if (d < k1) {
        return false;
    }
    int in_month = daysInMonth(m, y);
    return d <= in_month;
}

// Количество дней в месяце
int Date::daysInMonth(int month_, int year_) const {
    static const int kDaysPerMonth[] = {k31, k28, k31, k30, k31, k30,
                                        k31, k31, k30, k31, k30, k31};
    return (month_ == k2 && IsLeap()) ? k29 : kDaysPerMonth[month_ - k1];
}

// Определение високосного года
bool Date::IsLeap() const {
    return (year_ % k4 == 0 && year_ % k100 != 0) || (year_ % k400 == 0);
}

// Проверка формата даты (ДД.ММ.ГГГГ)
bool Date::isValidDateFormat(const std::string& dateStr) {
    if (dateStr.length() != k10 || dateStr[k2] != '.' || dateStr[k5] != '.') {
        return false;
    }
    for (size_t i = 0; i < dateStr.length(); ++i) {


        if (i == k2 || i == k5) {
            continue;
        }
        if (!isdigit(dateStr[i])) {
            return false;
        }
    }
    return true;
}

// Следующий день
Date Date::NextDay() const {
    int d = day_ + k1, m = month_, y = year_;
    if (d > daysInMonth(m, y)) {
        d = k1;


        if (++m > k12) {
            m = k1;
            ++y;
        }
    }
    return Date(d, m, y);
}

// Предыдущий день
Date Date::PreviousDay() const {
    int d = day_ - k1, m = month_, y = year_;


    if (d < k1) {
        if (--m < k1) {
            m = k12;
            --y;
        }
        d = daysInMonth(m, y);
    }
    return Date(d, m, y);
}

// Разница между датами
int Date::Duration(const Date& other) const {
    struct tm a = {0, 0, 0, day_, month_ - k1, year_ - k1900};
    struct tm b = {0, 0, 0, other.day_, other.month_ - k1, other.year_ - k1900};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    return (y - x) / (k60 * k60 * k24);
}

// Разница между текущей датой
int Date::DaysBetweenToday() const {
    Date today;
    return Duration(today);
}

// Дней до дня рождения
int Date::DaysTillBirthday(const Date& birthday) const {
    Date next_birthday(birthday.day_, birthday.month_, year_);


    if (*this < next_birthday) {
        return Duration(next_birthday);
    }
    next_birthday = Date(birthday.day_, birthday.month_, year_ + k1);
    return Duration(next_birthday);
}

// Номер недели в году
int Date::WeekNumber() const {
    struct tm date = {0, 0, 0, day_, month_ - k1, year_ - k1900};
    mktime(&date);
    return date.tm_yday / k7 + k1;
}

// Оператор сравнения
bool Date::operator<(const Date& other) const {


    if (year_ != other.year_) {
        return year_ < other.year_;
    }


    if (month_ != other.month_) {
        return month_ < other.month_;
    }
    return day_ < other.day_;
}

// Преобразование в строку (формат ДД.ММ.ГГГГ)
std::string Date::toString() const {
    std::ostringstream oss;
    oss << (day_ < k10 ? "0" : "") << day_ << "." << (month_ < k10 ? "0" : "")
        << month_ << "." << year_;
    return oss.str();
}
