#include "sixpointedstar.h"

const int kTwo = 2;
const int kSix = 6;
const int k90 = 90;
const double k360 = 360.0;
const double k05 = 0.5;
Star6::Star6(double radius, QGraphicsItem* parent)
    : Figure(parent), m_radius_(radius), m_ratio_(k05) {}

Star6::~Star6() = default;

double Star6::area() const {
    QPolygonF poly = buildPolygon();
    return polygonArea(poly);
}

double Star6::perimeter() const {
    QPolygonF poly = buildPolygon();
    return polygonPerimeter(poly);
}

double Star6::radius() const {
    return m_radius_;
}

void Star6::setRadius(double r) {
    prepareGeometryChange();
    m_radius_ = r;
    update();
}

QRectF Star6::boundingRect() const {
    return QRectF(-m_radius_, -m_radius_, kTwo * m_radius_, kTwo * m_radius_);
}

void Star6::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                  QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    QPolygonF poly = buildPolygon();
    painter->drawPolygon(poly);
}

QPolygonF Star6::buildPolygon() const {
    QPolygonF poly;
    const int n = kSix;	 // kSix лучей &rarr; 12 вершин
    double outer_r = m_radius_;
    double inner_r = m_ratio_ * m_radius_;


    for (int i = 0; i < kTwo * n; i++) {
        double angle_deg = ((k360 / (kTwo * n)) * i) - k90;
        double angle_rad = qDegreesToRadians(angle_deg);
        double r = (i % kTwo == 0) ? outer_r : inner_r;
        poly << QPointF(r * qCos(angle_rad), r * qSin(angle_rad));
    }
    return poly;
}

double Star6::polygonArea(const QPolygonF& poly) {
    double a = 0.0;
    int n = poly.size();


    for (int i = 0; i < n; i++) {
        QPointF p1 = poly[i];
        QPointF p2 = poly[(i + 1) % n];
        a += p1.x() * p2.y() - p2.x() * p1.y();
    }
    return qFabs(a) / kTwo;
}

double Star6::polygonPerimeter(const QPolygonF& poly) {
    double p = 0.0;
    int n = poly.size();


    for (int i = 0; i < n; i++) {
        QPointF p1 = poly[i];
        QPointF p2 = poly[(i + 1) % n];
        double dx = p2.x() - p1.x();
        double dy = p2.y() - p1.y();
        p += qSqrt((dx * dx) + (dy * dy));
    }
    return p;
}
