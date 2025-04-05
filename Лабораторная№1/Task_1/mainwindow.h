#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include "balloon.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget* parent = nullptr);

   private:
    Balloon* balloon_;
    QSlider* slider_;
    QLabel* instructionLabel_;
    QPushButton* popButton_;

    void setupUI();
};

#endif	// MAINWINDOW_H
