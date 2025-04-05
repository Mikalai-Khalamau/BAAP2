#include "triangle.h"

const double kTwo = 2.0;
const double kThree = 3.0;
const double kFour = 4.0;

Triangle::Triangle(double radius, QGraphicsItem* parent)
    : Figure(parent), m_radius_(radius) {}

Triangle::~Triangle() = default;

double Triangle::area() const {
    // Вычисляем сторону: side = r * &radic;3
    double side = m_radius_ * qSqrt(kThree);
    // Площадь равностороннего треугольника = (&radic;3/4) * side^kTwo
    return (qSqrt(kThree) / kFour) * side * side;
}

double Triangle::perimeter() const {
    double side = m_radius_ * qSqrt(kThree);
    return kThree * side;
}

double Triangle::radius() const {
    return m_radius_;
}

void Triangle::setRadius(double r) {
    prepareGeometryChange();
    m_radius_ = r;
    update();
}

QRectF Triangle::boundingRect() const {
    // Вычисляем boundingRect на основе вершин треугольника
    double half_x = m_radius_ * qSqrt(kThree) / kTwo;
    double min_x = -half_x;
    double max_x = half_x;
    double min_y = -m_radius_;
    double max_y = m_radius_ / kTwo;
    return QRectF(min_x, min_y, max_x - min_x, max_y - min_y);
}

void Triangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                     QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    // Определяем вершины треугольника
    QPointF v1(0, -m_radius_);
    QPointF v2(m_radius_ * qSqrt(kThree) / kTwo, m_radius_ / kTwo);
    QPointF v3(-m_radius_ * qSqrt(kThree) / kTwo, m_radius_ / kTwo);
    QPolygonF poly;
    poly << v1 << v2 << v3;
    painter->drawPolygon(poly);
}
