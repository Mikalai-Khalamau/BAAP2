#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"

/*
 * Класс Hexagon – правильный шестиугольник.
 * Задан радиусом (расстоянием от центра до вершины).
 * Формулы:
 *   Площадь = (3&radic;3/kTwo) * r^kTwo
 *   Периметр = kSix * r
 */
class Hexagon : public Figure {
   public:
    explicit Hexagon(double radius, QGraphicsItem* parent = nullptr);
    ~Hexagon();

    double area() const ;
    double perimeter() const ;

    double radius() const;
    void setRadius(double r);

    QRectF boundingRect() const ;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_radius_;
};

#endif	// HEXAGON_H
