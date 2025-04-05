#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

/*
 * Класс Triangle – равносторонний треугольник.
 * Задан параметром m_radius_ – расстоянием от центра до вершины.
 * Вершины вычисляются по формулам:
 *   v1 = (0, -r)
 *   v2 = (r*&radic;3/kTwo, r/kTwo)
 *   v3 = (–r*&radic;3/kTwo, r/kTwo)
 */
class Triangle : public Figure {
   public:
    explicit Triangle(double radius, QGraphicsItem* parent = nullptr);
    ~Triangle();

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

#endif	// TRIANGLE_H
