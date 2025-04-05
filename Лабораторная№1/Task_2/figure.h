#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QComboBox>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPainter>
#include <QPointF>
#include <QPolygonF>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>
#include <QtMath>
/*
 * Абстрактный базовый класс Figure.
 * Все фигуры нашего приложения наследуются от этого класса.
 *
 * Основные возможности:
 *   – Определение собственной геометрии (boundingRect)
 *   – Самостоятельное рисование (paint)
 *   – Вычисление площади (area) и периметра (perimeter)
 *   – Управление положением и цветом
 */
class Figure : public QGraphicsItem {
   public:
    // Конструктор: родительский QGraphicsItem может быть указан (по умолчанию nullptr)
    explicit Figure(QGraphicsItem* parent = nullptr);
     ~Figure();

    // Чисто виртуальные методы для вычисления площади и периметра,
    // которые должны быть реализованы в каждом классе-наследнике.
    double area() const;
    double perimeter() const;

    // Метод для получения "центра" фигуры (по умолчанию равен pos())
    QPointF center() const;
    // Установка центра фигуры (меняет pos())
    void setCenter(const QPointF& c);

    // Методы для работы с цветом фигуры
    QColor color() const;
    void setColor(const QColor& color);

    // Чисто виртуальные методы QGraphicsItem, которые нужно переопределить:
    // boundingRect() – возвращает прямоугольник, ограничивающий фигуру;
    // paint() – метод рисования фигуры.
    QRectF boundingRect() const  = 0;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr)  = 0;

   protected:
    QColor m_color_;  // Цвет фигуры
};

#endif	// FIGURE_H
