#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "figure.h"

/*
 * Класс Ellipse – эллипс.
 * Задан полуосями m_a_ (по X) и m_b_ (по Y).
 * Площадь = π * a * b.
 * Периметр рассчитывается приближённой формулой Рамануяма.
 */
class Ellipse : public Figure {
   public:
    explicit Ellipse(double a, double b, QGraphicsItem* parent = nullptr);
    ~Ellipse();

    double area() const ;
    double perimeter() const ;

    double a() const;
    double b() const;
    void setA(double val);
    void setB(double val);

    // boundingRect возвращает прямоугольник 2a x 2b, центрированный в (0,0)
    QRectF boundingRect() const ;
    // Рисует эллипс
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_a_;  // Полуось по X
    double m_b_;  // Полуось по Y
};

#endif	// ELLIPSE_H
