#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

/*
 * Класс Rhombus – ромб.
 * Задан диагоналями m_d1_ и m_d2_.
 * Формулы:
 *   Площадь = (d1 * d2) / kTwo
 *   Сторона = &radic;((d1/kTwo)^kTwo + (d2/kTwo)^kTwo)
 *   Периметр = 4 * сторона
 */
class Rhombus : public Figure {
   public:
    explicit Rhombus(double d1, double d2, QGraphicsItem* parent = nullptr);
    ~Rhombus();

    double area() const ;
    double perimeter() const ;

    double d1() const;
    double d2() const;
    void setD1(double d);
    void setD2(double d);

    QRectF boundingRect() const ;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_d1_;
    double m_d2_;
};

#endif	// RHOMBUS_H
