#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "algorithms.h" // Подключаем заголовок с BinPow и InterpolationSearch

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateArray();
    void performSearchStep();

private:
    void resetSearch();
    void updateTextEdit();

    Ui::MainWindow *ui;

    std::vector<int> array;
    int left;
    int right;
    int currentX;
    int searchDigit;
    bool searchInProgress;
};

#endif // MAINWINDOW_H
