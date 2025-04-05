#include "square.h"

const int kTwo = 2;
const int kFour = 4;
Square::Square(double side, QGraphicsItem* parent)
    : Figure(parent), m_side_(side) {}

Square::~Square() = default;

double Square::area() const {
    return m_side_ * m_side_;
}

double Square::perimeter() const {
    return kFour * m_side_;
}

double Square::side() const {
    return m_side_;
}

void Square::setSide(double s) {
    prepareGeometryChange();
    m_side_ = s;
    update();
}

QRectF Square::boundingRect() const {
    // Вычисляем прямоугольник так, чтобы квадрат был центрирован вокруг (0,0)
    double half = m_side_ / kTwo;
    return QRectF(-half, -half, m_side_, m_side_);
}

void Square::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
}
