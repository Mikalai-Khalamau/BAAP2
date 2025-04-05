#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

/*
 * Класс Square – квадрат.
 * Хранит длину стороны (m_side_) и вычисляет площадь и периметр.
 */
class Square : public Figure {
   public:
    explicit Square(double side, QGraphicsItem* parent = nullptr);
    ~Square();

    // Площадь квадрата = side^kTwo
    double area() const ;
    // Периметр квадрата = 4 * side
    double perimeter() const ;

    double side() const;
    void setSide(double s);

    // Возвращает boundingRect, центрированный так, чтобы (0,0) был в центре квадрата
    QRectF boundingRect() const ;
    // Рисует квадрат
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_side_;	 // Длина стороны
};

#endif	// SQUARE_H
