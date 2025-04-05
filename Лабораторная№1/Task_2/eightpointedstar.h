#ifndef EIGHTPOINTEDSTAR_H
#define EIGHTPOINTEDSTAR_H

#include "figure.h"

/*
 * Класс Star8 – 8-конечная звезда.
 * Задан внешним радиусом; внутренний радиус = m_ratio * m_radius_.
 * Всего 16 вершин, построенных по аналогии с предыдущими звёздами.
 */
class Star8 : public Figure {
   public:
    explicit Star8(double radius, QGraphicsItem* parent = nullptr);
    ~Star8();

    double area() const;
    double perimeter() const;

    double radius() const;
    void setRadius(double r);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr);

   private:
    double m_radius_;
    double m_ratio_;

    QPolygonF buildPolygon() const;
    static double polygonArea(const QPolygonF& poly);
    static double polygonPerimeter(const QPolygonF& poly);
};

#endif	// EIGHTPOINTEDSTAR_H
