#include "circle.h"

const double kTwo = 2.0;

Circle::Circle(double radius, QGraphicsItem* parent)
    : Figure(parent), m_radius_(radius) {}

Circle::~Circle() = default;

double Circle::area() const {
    return M_PI * m_radius_ * m_radius_ * koef;
}

double Circle::perimeter() const {
    return kTwo * M_PI * m_radius_;
}

double Circle::radius() const {
    return m_radius_;
}

void Circle::setRadius(double r) {
    // Подготавливаем обновление геометрии до её изменения
    prepareGeometryChange();
    m_radius_ = r;
    update();  // Перерисовка фигуры
}

QRectF Circle::boundingRect() const {
    // Определяем прямоугольник, охватывающий круг
    return QRectF(-m_radius_, -m_radius_, kTwo * m_radius_, kTwo * m_radius_);
}

void Circle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // Устанавливаем кисть и перо, затем рисуем эллипс, который является кругом
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
}
