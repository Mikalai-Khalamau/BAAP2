#include "mainwindow.h"

const int k400 = 400;
const int k600 = 600;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setFixedSize(k600, k400);  // Фиксированный размер окна
    setupUI();				   //настройка базового интерфейса
}

void MainWindow::setupUI() {
    // создание главного центрального виджета
    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Основной вертикальный лэйаут с центрированием
    auto* main_lay_out = new QVBoxLayout(central_widget);
    main_lay_out->setAlignment(Qt::AlignCenter);

    // Надпись с инструкцией с центрированием
    instructionLabel_ = new QLabel(
        "Двигайте ползунок чтобы перемещать шарик\n"
        "Нажмите на поверхность шарика или на кнопку чтобы лопнуть его");
    instructionLabel_->setAlignment(Qt::AlignCenter);

    // Создаем шарик
    balloon_ = new Balloon();

    // Ползунок
    slider_ = new QSlider(Qt::Horizontal);
    slider_->setRange(
        0, balloon_->width() - balloon_->balloonWidth);	 //диапазон значений

    // Кнопка
    popButton_ = new QPushButton("Лопнуть шарик");

    // Компоновка элементов
    main_lay_out->addWidget(instructionLabel_);
    main_lay_out->addWidget(balloon_, 0, Qt::AlignCenter);
    main_lay_out->addWidget(slider_);
    main_lay_out->addWidget(popButton_, 0, Qt::AlignCenter);

    // Соединения сигналов
    connect(slider_, &QSlider::valueChanged, balloon_, &Balloon::setXPos);
    connect(popButton_, &QPushButton::clicked, balloon_, &Balloon::popBalloon);
}
