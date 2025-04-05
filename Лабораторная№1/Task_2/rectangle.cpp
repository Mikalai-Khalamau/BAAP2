#include "rectangle.h"

const int kTwo = 2;
Rectangle::Rectangle(double width, double height, QGraphicsItem* parent)
    : Figure(parent), m_width_(width), m_height_(height) {}

Rectangle::~Rectangle() = default;

double Rectangle::area() const {
    return m_width_ * m_height_;
}

double Rectangle::perimeter() const {
    return kTwo * (m_width_ + m_height_);
}

double Rectangle::width() const {
    return m_width_;
}

double Rectangle::height() const {
    return m_height_;
}

void Rectangle::setWidth(double w) {
    prepareGeometryChange();
    m_width_ = w;
    update();
}

void Rectangle::setHeight(double h) {
    prepareGeometryChange();
    m_height_ = h;
    update();
}

QRectF Rectangle::boundingRect() const {
    double half_w = m_width_ / kTwo;
    double half_h = m_height_ / kTwo;
    return QRectF(-half_w, -half_h, m_width_, m_height_);
}

void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(m_color_);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
}
