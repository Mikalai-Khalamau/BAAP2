#include "mainwindow.h"
#include <QMainWindow>
#include "./ui_mainwindow.h"
#include "function.h"

const int k9=9;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this,
            &MainWindow::onTranslateButtonClicked);
    ui->lineEdit->setPlaceholderText("Введите значение числа");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onTranslateButtonClicked() {
    QString text_a = ui->lineEdit->text();
    if (text_a.length() > k9) {
        ui->label->setText("Максимум 9 символов.");
        return;
    } else {
        bool ok_a;
        int a = text_a.toInt(&ok_a);


        if (!ok_a || a < 0) {
            ui->label->setText(
                "Входные параметры должны быть неотрицательными целыми "
                "числами");
        }

        else {
            Function g;
            int result = g.translate(a, 0);
            ui->label->setText(QString::number(result));
        }
    }
}
