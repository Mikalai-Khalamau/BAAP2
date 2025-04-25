#include "mainwindow.h"
#include "algo.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>
#include <QIntValidator>
#include <QString>
#include <cstdlib>   // Для rand()
#include <ctime>     // Для time()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setPlaceholderText("Введите одно число для добавления в массив");
    // Валидаторы: только целые числа, без пробелов
    QRegularExpression r("^[-]?\\d+$");  // Целое число (возможно отрицательное)
    QValidator *validator = new QRegularExpressionValidator(r, this);
    ui->lineEdit->setValidator(validator);

     connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (numbers.isEmpty()) {
        ui->textEdit->setText("Сначала введите хотя бы одно число.");
        return;
    }
    QVector<double> med=t.Med(numbers);
    QString result = "Массив медиан:  ";
    for (int i = 0; i < med.size(); ++i)
        result += QString::number(med[i]) + " ";
    ui->textEdit->setText(result);
}

void MainWindow::on_pushButton_clicked()
{
    QString input=ui->lineEdit->text();
    if (!input.isEmpty())
    {
        int number=input.toInt();
        numbers.append(number);
        ui->lineEdit->clear();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    for (int i = 0; i < 50; ++i) {
        int value = std::rand() % 201 - 100;  // Случайное число от -100 до 100
        numbers.append(value);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    QString result = "Массив:  ";
    for (int i = 0; i < numbers.size(); ++i)
        result += QString::number(numbers[i]) + " ";
    ui->textEdit_2->setText(result);
}

