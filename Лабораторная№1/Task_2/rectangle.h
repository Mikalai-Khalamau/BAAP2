#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

/*
 * Класс Rectangle – прямоугольник.
 * Хранит ширину и высоту и вычисляет площадь и периметр.
 */
class Rectangle : public Figure {
   public:
    explicit Rectangle(double width, double height,
                       QGraphicsItem* parent = nullptr);
    ~Rectangle();

    // Площадь = width * height
    double area() const ;
    // Периметр = kTwo*(width + height)
    double perimeter() const ;

    double width() const;
    double height() const;
    void setWidth(double w);
    void setHeight(double h);

    // Возвращает boundingRect, центрированный относительно (0,0)
    QRectF boundingRect() const ;
    // Рисует прямоугольник
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_width_;
    double m_height_;
};

#endif	// RECTANGLE_H
