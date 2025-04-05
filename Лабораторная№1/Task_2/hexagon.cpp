#include "hexagon.h"

const int kTwo = 2;
const int kThree = 3;
const double kSix = 6.0;
const double k60 = 60.0;
const double k90 = 90.0;

Hexagon::Hexagon(double radius, QGraphicsItem* parent)
    : Figure(parent), m_radius_(radius) {}

Hexagon::~Hexagon() = default;

double Hexagon::area() const {
    return (kThree * qSqrt(kThree) / kTwo) * m_radius_ * m_radius_;
}

double Hexagon::perimeter() const {
    return kSix * m_radius_;
}

double Hexagon::radius() const {
    return m_radius_;
}

void Hexagon::setRadius(double r) {
    prepareGeometryChange();
    m_radius_ = r;
    update();
}

QRectF Hexagon::boundingRect() const {
    // Для правильного шестиугольника можно взять квадрат 2r x 2r
    return QRectF(-m_radius_, -m_radius_, kTwo * m_radius_, kTwo * m_radius_);
}

void Hexagon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                    QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    QPolygonF poly;
    // Рисуем kSix вершин, равномерно распределённых по окружности


    for (int i = 0; i < kSix; i++) {
        double angle_deg =
            (k60 * i) - k90;  // -90 чтобы первая вершина была наверху
        double angle_rad = qDegreesToRadians(angle_deg);
        double x = m_radius_ * qCos(angle_rad);
        double y = m_radius_ * qSin(angle_rad);
        poly << QPointF(x, y);
    }
    painter->drawPolygon(poly);
}
