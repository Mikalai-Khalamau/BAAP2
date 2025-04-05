#include "mainwindow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include "./ui_mainwindow.h"
#include "ackerman.h"

const int k2=2;
const int k3=3;
const int k4=4;
const int k5=5;
const int k10=10;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this,
            &MainWindow::onCalculateButtonClicked);
    ui->lineEdit->setPlaceholderText("Введите значение переменной m");
    ui->lineEdit_2->setPlaceholderText("Введите значение переменной n");
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::onCalculateButtonClicked() {
    QString text_m = ui->lineEdit->text();
    QString text_n = ui->lineEdit_2->text();
    bool ok_m, ok_n;
    int m = text_m.toInt(&ok_m);
    int n = text_n.toInt(&ok_n);


    if (!ok_m || !ok_n || m < 0 || n < 0) {
        ui->label->setText(
            "Входные параметры должны быть неотрицательными целыми числами");
    } else if (m >= k5 || ((m == k4) && (n >= k2)) || ((m == k3) && (n >= k10))) {
        ui->label->setText(
            "Функция вызовет переполнение стека из-за слишком глубокой "
            "рекурсии");
    }


    else if (m >= 0 && n >= 0 && ok_m && ok_n) {
        Ackerman g;
        int result = g.function(m, n);
        ui->label->setText(QString::number(result));
    }
}
