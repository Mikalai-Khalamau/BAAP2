#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include "function.h"

class RingItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
   public:
    using QGraphicsRectItem::QGraphicsRectItem;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void initializeTower();
    void startAnimation();
    void performAutoStep();
    void onAnimationFinished();

   private:
    void setupUI();
    void drawTowers();
    void initializeTowers(int rings);
    void animateRing(int ringNumber, int fromTower, int toTower);

    // Виджеты
    QGraphicsScene* scene;
    QGraphicsView* graphicsView;
    QLineEdit* ringsCountEdit;
    QLineEdit* speedEdit;
    QPushButton* initializeButton;
    QPushButton* startButton;
    QLabel* moveCounterLabel;  // << Новый QLabel для отображения ходов

    // Логика
    Function hanoiSolver;
    QVector<QPair<int, int>> moves;
    int currentMove;
    int moveCount;	// << переменная для подсчёта ходов
    QVector<QVector<int>> towers;
    QVector<QRect> rings;
    QVector<RingItem*> ringItems;
    QVector<int> ringWidths;
    QTimer* animationTimer;
    int animationSpeed;
    int ringsCount;
};

#endif	// MAINWINDOW_H
