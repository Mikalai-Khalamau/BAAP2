#ifndef SIXPOINTEDSTAR_H
#define SIXPOINTEDSTAR_H

#include "figure.h"

/*
 * Класс Star6 – kSix-конечная звезда.
 * Работает аналогично Star5, но имеет 12 вершин (kSix внешних и kSix внутренних).
 */
class Star6 : public Figure {
   public:
    explicit Star6(double radius, QGraphicsItem* parent = nullptr);
    ~Star6();

    double area() const ;
    double perimeter() const ;

    double radius() const;
    void setRadius(double r);

    QRectF boundingRect() const ;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_radius_;
    double m_ratio_;

    QPolygonF buildPolygon() const;
    static double polygonArea(const QPolygonF& poly);
    static double polygonPerimeter(const QPolygonF& poly);
};

#endif	// SIXPOINTEDSTAR_H
