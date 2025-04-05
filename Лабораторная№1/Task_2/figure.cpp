#include "figure.h"

Figure::Figure(QGraphicsItem* parent)
    : QGraphicsItem(parent),
      m_color_(Qt::cyan)  // по умолчанию цвет – голубой
{}

Figure::~Figure() {}
double Figure::area() const {
    return 0;
}

double Figure::perimeter() const {
    return 0;
}


QPointF Figure::center() const {

    // Центр фигуры – её позиция в сцене
    return pos();
}

void Figure::setCenter(const QPointF& c) {
    // Устанавливаем позицию фигуры так, чтобы её центр стал равен c
    setPos(c);
}

QColor Figure::color() const {
    return m_color_;
}

void Figure::setColor(const QColor& color) {
    m_color_ = color;
    update();  // Перерисовка фигуры после смены цвета
}
