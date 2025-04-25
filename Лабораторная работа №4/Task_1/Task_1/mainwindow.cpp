#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRegularExpressionValidator>

#include <QDebug>
#include <cstdlib>   // Для rand()
#include <ctime>     // Для time()
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Валидаторы
    // Валидаторы: только целые числа, без пробелов
    QRegularExpression re("^[-]?\\d+$");  // Целое число (возможно отрицательное)
    QValidator *validator = new QRegularExpressionValidator(re, this);

    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit->setPlaceholderText("Введите число для добавления в массив");
    ui->lineEdit_2->setPlaceholderText("Введите число для бинарного поиска");

    // Настройка comboBox
    ui->comboBox->addItem("Heap Sort");
    ui->comboBox->addItem("Merge Sort");
    ui->comboBox->addItem("Quick Sort");
    ui->comboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();
    if (!input.isEmpty()) {
        int number = input.toInt();
        numbers.append(number);
        ui->lineEdit->clear();
    }
}

void MainWindow::updateSortedArrayLabel(const int *arr, int size)
{
    QString result = "Отсортированный массив: ";
    for (int i = 0; i < size; ++i)
        result += QString::number(arr[i]) + " ";
    ui->textEdit->setText(result);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (numbers.isEmpty()) {
        ui->textEdit->setText("Сначала введите хотя бы одно число.");
        return;
    }

    int size = numbers.size();
    std::vector<int> original(numbers.begin(), numbers.end());
    int *arr = new int[size];
    std::copy(original.begin(), original.end(), arr);

    int sortIndex = ui->comboBox->currentIndex();
    QString sortType = ui->comboBox->currentText();

    auto start = std::chrono::high_resolution_clock::now();

    switch (sortIndex) {
    case 0:
        sorter.HeapSort(arr, size);
        break;
    case 1:
        sorter.MergeSort(arr, 0, size - 1);
        break;
    case 2:
        sorter.QuickSort(arr, size);
        break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    updateSortedArrayLabel(arr, size);
    ui->label_2->setText("Время сортировки (" + sortType + "): " + QString::number(elapsed.count()) + " сек");

    // Сохраняем отсортированный массив (если понадобится для поиска)
    numbers.clear();
    for (int i = 0; i < size; ++i)
        numbers.append(arr[i]);

    delete[] arr;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString searchStr = ui->lineEdit_2->text();
    if (numbers.isEmpty()) {
        ui->label_3->setText("Сначала отсортируйте массив.");
        return;
    }
    if (searchStr.isEmpty()) {
        ui->label_3->setText("Введите число для поиска.");
        return;
    }

    int digit = searchStr.toInt();
    std::vector<int> vec(numbers.begin(), numbers.end());

    int index = sorter.BinSearch(vec, digit);
    if (index==-1)
    {
        ui->label_3->setText("Элемент не найден");
    }
    else
    {
    ui->label_3->setText("Индекс элемента: "+QString::number(index));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    for (int i = 0; i < 50; ++i) {
        int value = std::rand() % 201 - 100;  // Случайное число от -100 до 100
        numbers.append(value);
    }

    ui->textEdit->setText("Сгенерировано 50 случайных чисел.");
    ui->label_2->clear();
    ui->label_3->clear();
}



