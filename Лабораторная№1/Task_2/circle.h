#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"
/*
 * Класс Circle – круг.
 * Хранит радиус (m_radius_) и реализует вычисление площади и периметра.
 */
class Circle : public Figure {
   public:
    explicit Circle(double radius, QGraphicsItem* parent = nullptr);
    ~Circle();

    // Площадь круга = π * r^kTwo
    double area() const;
    // Периметр круга = 2πr
    double perimeter() const;

    double radius() const;
    void setRadius(double r);

    // Возвращает прямоугольник, охватывающий круг (центрирован относительно (0,0))
    QRectF boundingRect() const;
    // Рисует круг с помощью QPainter
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr);

   private:
    double m_radius_;  // Радиус круга
};

#endif	// CIRCLE_H
