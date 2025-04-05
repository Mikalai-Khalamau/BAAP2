#include "mainwindow.h"
#include <QDate>
#include <QFileDialog>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtCore>
#include <fstream>
#include <sstream>
#include "date.h"
#include "file_utils.h"
// Подключаем новые функции работы с файлом

const int k1000 = 1000;
const int k700 = 700;
const int k8 = 8;
const int k5 = 5;
const int k6 = 6;
const int k7 = 7;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), tableWidget_(new QTableWidget(this)) {
    setFixedSize(k1000, k700);
    // Настройка UI
    QVBoxLayout* layout = new QVBoxLayout;

    loadFileButton_ = new QPushButton("Загрузить даты из файла");
    previousDayButton_ = new QPushButton("Предыдущий день");
    nextDayButton_ = new QPushButton("Следующий день");

    dateDifferenceButton_ = new QPushButton("Разница со следующим по списку");
    diffWithPresentDate_ = new QPushButton("Разница с текущей датой");
    daysTillBirthdayButton_ = new QPushButton("Дни до ДР");
    leapYearButton_ = new QPushButton("Високосный год");
    weekNumberButton_ = new QPushButton("Номер недели");

    layout->addWidget(loadFileButton_);
    layout->addWidget(previousDayButton_);
    layout->addWidget(nextDayButton_);
    layout->addWidget(dateDifferenceButton_);
    layout->addWidget(diffWithPresentDate_);
    layout->addWidget(daysTillBirthdayButton_);
    layout->addWidget(leapYearButton_);
    layout->addWidget(weekNumberButton_);
    layout->addWidget(tableWidget_);

    // Элементы для ввода даты рождения (уже реализовано)
    birthDateEdit_ = new QLineEdit(this);
    birthDateEdit_->setPlaceholderText("Введите дату рождения (ДД.ММ.ГГГГ)");
    layout->addWidget(birthDateEdit_);

    QPushButton* save_button = new QPushButton("Сохранить дату", this);
    layout->addWidget(save_button);
    connect(save_button, &QPushButton::clicked, this, &MainWindow::saveDate);

    // элементы для работы с датами в файле (добавление/изменение/удаление)
    fileDateEdit_ = new QLineEdit(this);
    fileDateEdit_->setPlaceholderText("Введите дату для файла (ДД.ММ.ГГГГ)");
    layout->addWidget(fileDateEdit_);

    addDateButton_ = new QPushButton("Добавить дату", this);
    modifyDateButton_ = new QPushButton("Изменить дату", this);
    deleteDateButton_ = new QPushButton("Удалить дату", this);

    layout->addWidget(addDateButton_);
    layout->addWidget(modifyDateButton_);
    layout->addWidget(deleteDateButton_);

    QWidget* central_widget = new QWidget(this);
    central_widget->setLayout(layout);
    setCentralWidget(central_widget);

    setupTable();

    // Соединяем кнопки с функциями
    connect(loadFileButton_, &QPushButton::clicked, this,
            &MainWindow::loadDates);
    connect(previousDayButton_, &QPushButton::clicked, this,
            &MainWindow::calculatePreviousDay);
    connect(nextDayButton_, &QPushButton::clicked, this,
            &MainWindow::calculateNextDay);
    connect(dateDifferenceButton_, &QPushButton::clicked, this,
            &MainWindow::calculateDateDifference);
    connect(diffWithPresentDate_, &QPushButton::clicked, this,
            &MainWindow::calculateDiffPresentDate);
    connect(daysTillBirthdayButton_, &QPushButton::clicked, this,
            &MainWindow::calculateDaysTillBirthday);
    connect(leapYearButton_, &QPushButton::clicked, this,
            &MainWindow::checkLeapYear);
    connect(weekNumberButton_, &QPushButton::clicked, this,
            &MainWindow::calculateWeekNumber);

    // Подключаем новые кнопки к слотам
    connect(addDateButton_, &QPushButton::clicked, this,
            &MainWindow::addDateToFile);
    connect(modifyDateButton_, &QPushButton::clicked, this,
            &MainWindow::modifyDateInFile);
    connect(deleteDateButton_, &QPushButton::clicked, this,
            &MainWindow::deleteDateFromFile);
}

MainWindow::~MainWindow() {}

void MainWindow::saveDate() {
    QString input = birthDateEdit_->text();

    // Проверяем формат строки
    if (!Date::isValidDateFormat(input.toStdString())) {
        QMessageBox::warning(this, "Ошибка",
                             "Неверный формат даты. Используйте ДД.ММ.ГГГГ");
        return;
    }

    // Извлекаем день, месяц и год из строки
    int day = input.mid(0, 2).toInt();
    int month = input.mid(3, 2).toInt();
    int year = input.mid(k6, 4).toInt();

    // Проверяем корректность даты
    if (!birthDate_.isValidDate(day, month, year)) {
        QMessageBox::warning(this, "Ошибка", "Некорректная дата!");
        return;
    }

    // Сохраняем дату в член класса
    birthDate_ = Date(day, month, year);

    QMessageBox::information(
        this, "Успех",
        "Дата сохранена: " + QString::fromStdString(birthDate_.toString()));
}

void MainWindow::setupTable() {
    tableWidget_->setColumnCount(k8);
    tableWidget_->setHorizontalHeaderLabels(
        {"Дата", "Пред. день", "След. день", "Разница с предыдущим по списку",
         "Дней до реальной даты", "Дней до ДР", "Год високосный?",
         "Номер недели в году"});
    tableWidget_->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::loadDates() {
    QString file_name = QFileDialog::getOpenFileName(this, "Выберите файл", "",
                                                     "Text Files (*.txt)");
    if (file_name.isEmpty()) {
        return;
    }

    currentFileName_ =
        file_name;	// Сохраняем имя файла для последующих операций
    dates_.clear();
    std::ifstream file(file_name.toStdString());
    std::string line;

    // Читаем файл построчно (ожидается, что каждая строка содержит дату в формате ДД.ММ.ГГГГ)
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int d, m, y;
        char dot1, dot2;


        if (iss >> d >> dot1 >> m >> dot2 >> y && dot1 == '.' && dot2 == '.') {

            dates_.emplace_back(d, m, y);
        }
    }
    updateTable();
}

void MainWindow::updateTable() {
    tableWidget_->setRowCount(static_cast<int>(dates_.size()));
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(
            static_cast<int>(i), 0,
            new QTableWidgetItem(QString::fromStdString(dates_[i].toString())));
    }
}

void MainWindow::calculateNextDay() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(static_cast<int>(i), 2,
                              new QTableWidgetItem(QString::fromStdString(
                                  dates_[i].NextDay().toString())));
    }
}

void MainWindow::calculatePreviousDay() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(static_cast<int>(i), 1,
                              new QTableWidgetItem(QString::fromStdString(
                                  dates_[i].PreviousDay().toString())));
    }
}

void MainWindow::calculateDateDifference() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(static_cast<int>(i), 3,
                              new QTableWidgetItem(QString::number(
                                  dates_[i].Duration(dates_[i + 1]))));
    }
}

void MainWindow::calculateDaysTillBirthday() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(static_cast<int>(i), k5,
                              new QTableWidgetItem(QString::number(
                                  dates_[i].DaysTillBirthday(birthDate_))));
    }
}

void MainWindow::checkLeapYear() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(
            static_cast<int>(i), k6,
            new QTableWidgetItem(dates_[i].IsLeap() ? "Да" : "Нет"));
    }
}

void MainWindow::calculateWeekNumber() {
    for (size_t i = 0; i < dates_.size(); ++i) {
        tableWidget_->setItem(
            static_cast<int>(i), k7,
            new QTableWidgetItem(QString::number(dates_[i].WeekNumber())));
    }
}

void MainWindow::calculateDiffPresentDate() {
    QDate current_q_date = QDate::currentDate();
    Date current_date(current_q_date.day(), current_q_date.month(),
                      current_q_date.year());
    for (size_t i = 0; i < dates_.size(); ++i) {
        int diff = dates_[i].Duration(current_date);
        tableWidget_->setItem(static_cast<int>(i), 4,
                              new QTableWidgetItem(QString::number(diff)));
    }
}

// Новый слот: добавление даты в файл без полной перезаписи
void MainWindow::addDateToFile() {
    QString input = fileDateEdit_->text();
    // Проверка формата даты
    if (!Date::isValidDateFormat(input.toStdString())) {
        QMessageBox::warning(this, "Ошибка",
                             "Неверный формат даты. Используйте ДД.ММ.ГГГГ");
        return;
    }
    int d = input.mid(0, 2).toInt();
    int m = input.mid(3, 2).toInt();
    int y = input.mid(k6, 4).toInt();
    Date new_date(d, m, y);
    // Дополнительная проверка корректности даты
    if (!new_date.isValidDate(d, m, y)) {
        QMessageBox::warning(this, "Ошибка", "Некорректная дата!");
        return;
    }
    try {
        if (!AppendDateToFile(currentFileName_.toStdString(), new_date)) {
            throw std::runtime_error("Ошибка добавления даты в файл!");
        }
        // Добавляем новую дату в in-memory массив и обновляем таблицу
        dates_.push_back(new_date);
        updateTable();
        QMessageBox::information(this, "Успех",
                                 "Дата успешно добавлена в файл!");
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Ошибка", ex.what());
    }
}

// Новый слот: изменение даты в файле без полной перезаписи
void MainWindow::modifyDateInFile() {
    // Проверяем, выделена ли строка в таблице
    QList<QTableWidgetItem*> selected_items = tableWidget_->selectedItems();
    if (selected_items.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
                             "Выберите дату для изменения в таблице.");
        return;
    }
    int row = selected_items.first()->row();

    QString input = fileDateEdit_->text();
    if (!Date::isValidDateFormat(input.toStdString())) {
        QMessageBox::warning(this, "Ошибка",
                             "Неверный формат даты. Используйте ДД.ММ.ГГГГ");
        return;
    }
    int d = input.mid(0, 2).toInt();
    int m = input.mid(3, 2).toInt();
    int y = input.mid(k6, 4).toInt();
    Date new_date(d, m, y);
    if (!new_date.isValidDate(d, m, y)) {
        QMessageBox::warning(this, "Ошибка", "Некорректная дата!");
        return;
    }
    try {
        if (!ModifyDateInFile(currentFileName_.toStdString(), row, new_date)) {
            throw std::runtime_error("Ошибка изменения даты в файле!");
        }
        // Обновляем дату в in-memory массиве и таблице
        dates_[row] = new_date;
        updateTable();
        QMessageBox::information(this, "Успех", "Дата успешно изменена!");
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Ошибка", ex.what());
    }
}

// Новый слот: удаление даты из файла без полной перезаписи
void MainWindow::deleteDateFromFile() {
    QList<QTableWidgetItem*> selected_items = tableWidget_->selectedItems();
    if (selected_items.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
                             "Выберите дату для удаления в таблице.");
        return;
    }
    int row = selected_items.first()->row();

    // Подтверждение удаления
    if (QMessageBox::question(this, "Подтверждение",
                              "Удалить выбранную дату?") != QMessageBox::Yes) {
        return;
    }
    try {
        if (!DeleteDateFromFile(currentFileName_.toStdString(), row)) {
            throw std::runtime_error("Ошибка удаления даты из файла!");
        }
        // Удаляем дату из in-memory массива и обновляем таблицу
        dates_.erase(dates_.begin() + row);
        updateTable();
        QMessageBox::information(this, "Успех", "Дата успешно удалена!");
    } catch (std::exception& ex) {
        QMessageBox::critical(this, "Ошибка", ex.what());
    }
}
