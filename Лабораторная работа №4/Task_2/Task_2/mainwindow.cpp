#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRandomGenerator>
#include <QString>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , left(0)
    , right(0)
    , currentX(0)
    , searchInProgress(false)
{
    ui->setupUi(this);

    // Валидатор: только цифры, без пробелов
    QValidator *validator = new QIntValidator(0, 1000000, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setPlaceholderText("Введите число для поиска");

    // Кнопки
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::generateArray);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::performSearchStep);

    ui->textEdit->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateArray()
{
    array.clear();
    for (int i = 0; i < 30; ++i) {
        array.push_back(QRandomGenerator::global()->bounded(0, 100));
    }

    std::sort(array.begin(), array.end());

    ui->textEdit->clear();
    ui->label->clear();

    QString text = "Сгенерирован массив:\n";
    for (int num : array) {
        text += QString::number(num) + " ";
    }
    ui->textEdit->setText(text);

    // Сбросить поиск
    resetSearch();
}

void MainWindow::resetSearch()
{
    left = 0;
    right = array.size() - 1;
    currentX = 0;
    searchInProgress = false;
}

void MainWindow::updateTextEdit()
{
    QString subArrayText = "Текущий диапазон: [l = " + QString::number(left) +
                           ", r = " + QString::number(right) + "]\n";

    for (int i = left; i <= right && i < array.size(); ++i) {
        subArrayText += QString::number(array[i]) + " ";
    }

    ui->textEdit->append(subArrayText);
}

void MainWindow::performSearchStep()
{
    if (!searchInProgress) {
        // Начинаем новый поиск
        if (ui->lineEdit->text().isEmpty()) {
            ui->textEdit->append("Введите число для поиска.");
            return;
        }

        searchDigit = ui->lineEdit->text().toInt();
        ui->lineEdit->clear(); // ОЧИСТКА ПОЛЯ ВВОДА
        ui->textEdit->clear();
        resetSearch();
        searchInProgress = true;
    }

    Algorithms algo;

    // Если уже вышли за границы или массив пустой
    if (left > right || array.empty()) {
        ui->textEdit->append("Элемент не найден.");
        ui->label->setText("—");
        searchInProgress = false;
        return;
    }

    // Если не попадает в интерполяцию
    if (array[left] == array[right]) {
        if (array[left] == searchDigit) {
            int index = left;
            ui->textEdit->append("Найден элемент на позиции: " + QString::number(index));
            int result = algo.BinPow(index, array.size(), 1000000007);
            ui->label->setText(QString::number(result));
        } else {
            ui->textEdit->append("Элемент не найден.");
            ui->label->setText("—");
        }
        searchInProgress = false;
        return;
    }

    currentX = left + ((searchDigit - array[left]) * (right - left)) / (array[right] - array[left]);

    updateTextEdit(); // Показать текущую границу поиска

    if (currentX < left || currentX > right) {
        ui->textEdit->append("Элемент не найден.");
        ui->label->setText("—");
        searchInProgress = false;
        return;
    }

    if (array[currentX] == searchDigit) {
        ui->textEdit->append("Найден элемент на позиции: " + QString::number(currentX));
        int result = algo.BinPow(currentX, array.size(), 1000000007);
        ui->label->setText("Индекс найденного элемента в степени длины массива по модулю числа: "+QString::number(result));
        searchInProgress = false;
    } else if (array[currentX] < searchDigit) {
        left = currentX + 1;
    } else {
        right = currentX - 1;
    }

    if (left > right && searchInProgress) {
        ui->textEdit->append("Элемент не найден.");
        ui->label->setText("Элемент не найден");
        searchInProgress = false;
    }
}
