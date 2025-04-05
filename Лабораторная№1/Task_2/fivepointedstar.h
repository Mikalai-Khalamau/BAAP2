#ifndef FIVEPOINTEDSTAR_H
#define FIVEPOINTEDSTAR_H

#include "figure.h"

/*
 * Класс Star5 – 5-конечная звезда.
 * Задан внешним радиусом, внутренний радиус = m_ratio * m_radius_.
 * Для вычисления площади и периметра звезды строим полигон (10 точек).
 */
class Star5 : public Figure {
   public:
    explicit Star5(double radius, QGraphicsItem* parent = nullptr);
    ~Star5();

    double area() const ;
    double perimeter() const ;

    double radius() const;
    void setRadius(double r);

    QRectF boundingRect() const ;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) ;

   private:
    double m_radius_;  // Внешний радиус звезды
    double m_ratio_;   // Отношение внутреннего радиуса к внешнему

    // Метод, строящий полигон звезды (10 точек)
    QPolygonF buildPolygon() const;
    // Статические функции для вычисления площади и периметра полигона
    static double polygonArea(const QPolygonF& poly);
    static double polygonPerimeter(const QPolygonF& poly);
};

#endif	// FIVEPOINTEDSTAR_H
