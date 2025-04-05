#include "rhombys.h"

const int kTwo = 2;
const int kFour = 4;
Rhombus::Rhombus(double d1, double d2, QGraphicsItem* parent)
    : Figure(parent), m_d1_(d1), m_d2_(d2) {}

Rhombus::~Rhombus() = default;

double Rhombus::area() const {
    return (m_d1_ * m_d2_) / kTwo;
}

double Rhombus::perimeter() const {
    double side = qSqrt(((m_d1_ / kTwo) * (m_d1_ / kTwo)) +
                        ((m_d2_ / kTwo) * (m_d2_ / kTwo)));
    return kFour * side;
}

double Rhombus::d1() const {
    return m_d1_;
}

double Rhombus::d2() const {
    return m_d2_;
}

void Rhombus::setD1(double d) {
    prepareGeometryChange();
    m_d1_ = d;
    update();
}

void Rhombus::setD2(double d) {
    prepareGeometryChange();
    m_d2_ = d;
    update();
}

QRectF Rhombus::boundingRect() const {
    double half_x = m_d1_ / kTwo;
    double half_y = m_d2_ / kTwo;
    return QRectF(-half_x, -half_y, m_d1_, m_d2_);
}

void Rhombus::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                    QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    // Определяем вершины ромба
    QPointF v1(-m_d1_ / kTwo, 0);
    QPointF v2(0, -m_d2_ / kTwo);
    QPointF v3(m_d1_ / kTwo, 0);
    QPointF v4(0, m_d2_ / kTwo);
    QPolygonF poly;
    poly << v1 << v2 << v3 << v4;
    painter->drawPolygon(poly);
}
