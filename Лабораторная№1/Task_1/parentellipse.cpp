#include "parentellipse.h"

const int k200 = 200;
const int k400 = 400;
const int k18 = 18;
const int k30 = 30;
const int k230 = 230;
ParentEllipse::ParentEllipse(QWidget* parent)  //констуктор класса
    : QWidget(parent)  // обязательно для корректной инициализации виджета
/*
Конструктор QWidget настраивает:

Систему событий

Свойства виджета

Родительско-дочерние связи
 */
{
    setFixedSize(k400, k200);  // Фиксированный размер виджета
}

void ParentEllipse::setXPos(
    double x)  // метод для установки позиции шарика по оси x
{
    x_pos_ = qBound(0.0, x, width() - balloonWidth);
    /*
     qBound(min, value, max) — функция Qt, которая:

Возвращает value, если оно в диапазоне [min, max]

Возвращает min, если value < min

Возвращает max, если value > max
*/
    update();  // Вызывает перерисовку виджета через событие paintEvent
}

void ParentEllipse::
    popBalloon()  //Состояние изменяется в popBalloon() Визуализация — в paintEvent()
{
    popped_ = true;
    update();  // Перерисовка виджета
}

/*
update() — метод Qt, который планирует перерисовку виджета.

Что происходит:

Qt добавляет событие перерисовки в очередь

Когда цикл событий доходит до него, вызывается paintEvent()

В paintEvent() проверяется popped, чтобы отрисовать нужное состояние
 */

void ParentEllipse::paintEvent(
    QPaintEvent* event)	 //метод для отрисовки шарика в зависимости от состояний
{
    QPainter painter(this);	 // создает обьект для рисования на текущем виджете
    painter.setRenderHint(
        QPainter::
            Antialiasing);	//Включает сглаживание краёв, чтобы фигуры выглядели менее "пикселизированными".


    if (popped_) {
        // Отображение текста при лопании ровно по центру нашего виджета
        painter.setPen(Qt::darkRed);
        painter.setFont(QFont("Arial", k18, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "Вы лопнули шарик!");
    } else {
        // Рисование реалистичного шарика
        QPainterPath path;	//контейнер для рисования векторных фигур

        // Основная часть (вертикальный эллипс)
        path.addEllipse(QPointF(x_pos_ + (balloonWidth / 2),
                                yPosition + (balloonHeight / 2)),
                        balloonWidth / 2, balloonHeight / 2);

        painter.setBrush(QColor(
            k230, k30, k30));  // Алый цвет Заливка: RGB(230, 30, 30) (алый)
        painter.setPen(Qt::NoPen);	// Без контура (Qt::NoPen)
        painter.drawPath(path);
    }
    /*
Метод вызывается Qt при:

Первом отображении виджета

Вызове update()

Изменении размера окна
 */
}
