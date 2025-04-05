#include "mainwindow.h"
#include <QGraphicsTextItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    currentMove = 0;
    towers.resize(3);
    animationSpeed = 1000;
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this,
            &MainWindow::performAutoStep);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* controlLayout = new QHBoxLayout();

    QLabel* label = new QLabel("Количество колец:", this);
    ringsCountEdit = new QLineEdit("3", this);
    ringsCountEdit->setMaximumWidth(50);

    QLabel* speedLabel = new QLabel("Скорость (мс):", this);
    speedEdit = new QLineEdit("1000", this);
    speedEdit->setMaximumWidth(50);

    initializeButton = new QPushButton("Инициализировать", this);
    connect(initializeButton, &QPushButton::clicked, this,
            &MainWindow::initializeTower);

    startButton = new QPushButton("Старт", this);
    startButton->setEnabled(false);
    connect(startButton, &QPushButton::clicked, this,
            &MainWindow::startAnimation);

    controlLayout->addWidget(label);
    controlLayout->addWidget(ringsCountEdit);
    controlLayout->addWidget(speedLabel);
    controlLayout->addWidget(speedEdit);
    controlLayout->addWidget(initializeButton);
    controlLayout->addWidget(startButton);
    moveCounterLabel = new QLabel("Ходов: 0", this);  // Новый QLabel
    controlLayout->addWidget(moveCounterLabel);

    scene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(scene, this);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setSceneRect(0, 0, 600, 400);

    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(graphicsView);

    setCentralWidget(centralWidget);
    resize(800, 600);
    setWindowTitle("Ханойская башня с анимацией");
}

void MainWindow::initializeTower() {
    bool ok;
    int ringsCount = ringsCountEdit->text().toInt(&ok);


    if (!ok || ringsCount < 1 || ringsCount > 8) {
        QMessageBox::warning(this, "Ошибка", "Введите число от 1 до 8");
        return;
    }

    animationSpeed = speedEdit->text().toInt(&ok);


    // Проверка скорости анимации
    bool okSpeed;
    int inputSpeed = speedEdit->text().toInt(&okSpeed);

    // Если ввод не число или вне диапазона


    if (!okSpeed || inputSpeed < 100 || inputSpeed > 10000) {
        QMessageBox::warning(
            this, "Ошибка",
            "Скорость должна быть целым числом от 100 до 10000 мс");
        speedEdit->setText("1000");	 // сброс на стандартное значение
        animationSpeed = 1000;
    } else {
        animationSpeed = inputSpeed;
    }


    initializeTowers(ringsCount);
    moves = hanoiSolver.Hanoi(ringsCount, 1, 3);
    currentMove = 0;
    moveCount = 0;
    moveCounterLabel->setText("Ходов: 0");

    startButton->setEnabled(true);
}

void MainWindow::startAnimation() {
    startButton->setEnabled(false);
    initializeButton->setEnabled(false);
    animationTimer->start(animationSpeed);
}

void MainWindow::performAutoStep() {
    if (currentMove >= moves.size()) {
        animationTimer->stop();
        QMessageBox::information(this, "Готово", "Все кольца перемещены!");
        initializeButton->setEnabled(true);
        return;
    }

    QPair<int, int> move = moves[currentMove];
    int from = move.first - 1;
    int to = move.second - 1;

    if (!towers[from].isEmpty()) {
        int ringValue = towers[from].last();
        int ringIndex = ringsCount - ringValue;	 // Получаем индекс кольца
        animateRing(ringIndex, from, to);
    }

    currentMove++;
    moveCount++;
    moveCounterLabel->setText(QString("Ходов: %1").arg(moveCount));
}

void MainWindow::animateRing(int ringIndex, int fromTower, int toTower) {
    int ringValue = ringsCount - ringIndex;	 // Обратное отображение
    towers[fromTower].removeLast();

    RingItem* ring = ringItems[ringIndex];

    int baseY = 300;
    int liftHeight = 200;

    QPointF startPos = ring->pos();
    QPointF liftPos = QPointF(startPos.x(), startPos.y() - liftHeight);

    int width = ringWidths[ringIndex];
    int targetX = 100 + toTower * 200 - width / 2;

    int stackHeight = towers[toTower].size();
    int targetY = baseY - (stackHeight + 1) * 25;
    QPointF aboveTargetPos = QPointF(targetX, liftPos.y());
    QPointF endPos = QPointF(targetX, targetY);

    towers[toTower].append(ringValue);

    QSequentialAnimationGroup* animationGroup =
        new QSequentialAnimationGroup(this);

    QPropertyAnimation* liftAnimation = new QPropertyAnimation(ring, "pos");
    liftAnimation->setDuration(animationSpeed / 3);
    liftAnimation->setStartValue(startPos);
    liftAnimation->setEndValue(liftPos);

    QPropertyAnimation* moveAnimation = new QPropertyAnimation(ring, "pos");
    moveAnimation->setDuration(animationSpeed / 3);
    moveAnimation->setStartValue(liftPos);
    moveAnimation->setEndValue(aboveTargetPos);

    QPropertyAnimation* dropAnimation = new QPropertyAnimation(ring, "pos");
    dropAnimation->setDuration(animationSpeed / 3);
    dropAnimation->setStartValue(aboveTargetPos);
    dropAnimation->setEndValue(endPos);

    animationGroup->addAnimation(liftAnimation);
    animationGroup->addAnimation(moveAnimation);
    animationGroup->addAnimation(dropAnimation);

    connect(animationGroup, &QAbstractAnimation::finished, this,
            &MainWindow::onAnimationFinished);
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::onAnimationFinished() {}

void MainWindow::initializeTowers(int count) {
    ringsCount = count;
    towers.clear();
    towers.resize(3);
    ringItems.clear();
    ringWidths.clear();
    scene->clear();


    for (int i = 0; i < count; ++i) {
        int ringValue = count - i;
        towers[0].append(ringValue);
    }

    int baseY = 300;


    for (int i = 0; i < 3; ++i) {
        scene->addRect(100 + i * 200 - 5, baseY, 10, 10, QPen(),
                       QBrush(Qt::black));
        scene->addRect(100 + i * 200 - 2, baseY - 200, 4, 200, QPen(),
                       QBrush(Qt::black));
    }


    for (int i = 0; i < count; ++i) {
        int ringValue = i + 1;
        int ringIndex = count - ringValue;

        int width = 30 + (count - ringValue + 1) * 20;

        int x = 100 - width / 2;
        int y = baseY - (ringValue) * 25;

        RingItem* ring = new RingItem();
        ring->setRect(0, 0, width, 20);
        ring->setPos(x, y);
        ring->setBrush(QColor::fromHsv(ringIndex * 30, 255, 200));
        ring->setPen(QPen(Qt::black));


        scene->addItem(ring);
        ringItems.append(ring);
        ringWidths.append(width);
    }

    scene->addText("A")->setPos(90, 310);
    scene->addText("B")->setPos(290, 310);
    scene->addText("C")->setPos(490, 310);
}
