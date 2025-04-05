#include "ellipse.h"

const int kOne = 1;
const int kTwo = 2;
const int kThree = 3;
const int kFour = 4;
const int kTen = 10;

Ellipse::Ellipse(double a, double b, QGraphicsItem* parent)
    : Figure(parent), m_a_(a), m_b_(b) {}

Ellipse::~Ellipse() = default;

double Ellipse::area() const {
    return M_PI * m_a_ * m_b_;
}

double Ellipse::perimeter() const {
    // Приближённая формула Рамануяма для периметра эллипса:
    double h = qPow((m_a_ - m_b_), kTwo) / qPow((m_a_ + m_b_), kTwo);
    return M_PI * (m_a_ + m_b_) *
           (kOne + ((kThree * h) / (kTen + qSqrt(kFour - (kThree * h)))));
}

double Ellipse::a() const {
    return m_a_;
}

double Ellipse::b() const {
    return m_b_;
}

void Ellipse::setA(double val) {
    prepareGeometryChange();
    m_a_ = val;
    update();
}

void Ellipse::setB(double val) {
    prepareGeometryChange();
    m_b_ = val;
    update();
}

QRectF Ellipse::boundingRect() const {
    // Эллипс центрирован в (0,0)
    return QRectF(-m_a_, -m_b_, kTwo * m_a_, kTwo * m_b_);
}

void Ellipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                    QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
}
