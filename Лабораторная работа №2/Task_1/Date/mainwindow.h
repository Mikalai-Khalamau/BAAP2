#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <vector>
#include "date.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void loadDates();
    void calculateNextDay();
    void calculatePreviousDay();
    void calculateDateDifference();
    void calculateDaysTillBirthday();
    void checkLeapYear();
    void calculateWeekNumber();
    void calculateDiffPresentDate();
    void saveDate();

    // Новые слоты для работы с файлами
    void addDateToFile();
    void modifyDateInFile();
    void deleteDateFromFile();

   private:
    void setupTable();
    void updateTable();

    // Элементы управления для работы с датами из файла
    QLineEdit* birthDateEdit_;	// для ввода даты рождения (уже реализовано)
    QLineEdit*
        fileDateEdit_;	// для ввода даты для операций добавления/изменения
    QTableWidget* tableWidget_;
    QPushButton* loadFileButton_;
    QPushButton* nextDayButton_;
    QPushButton* previousDayButton_;
    QPushButton* dateDifferenceButton_;
    QPushButton* daysTillBirthdayButton_;
    QPushButton* leapYearButton_;
    QPushButton* weekNumberButton_;
    QPushButton* diffWithPresentDate_;

    // Новые кнопки для операций с файлом
    QPushButton* addDateButton_;
    QPushButton* modifyDateButton_;
    QPushButton* deleteDateButton_;

    std::vector<Date> dates_;
    Date birthDate_;

    // Сохранённое имя текущего файла для дальнейших операций
    QString currentFileName_;
};

#endif	// MAINWINDOW_H
