#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "sorts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();    // Добавить число
    void on_pushButton_2_clicked();  // Сортировка
    void on_pushButton_3_clicked();  // Бинарный поиск
     void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> numbers;
    Sorts sorter;

    void updateSortedArrayLabel(const int *arr, int size);
};

#endif // MAINWINDOW_H
