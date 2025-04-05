#ifndef PARENTELLIPSE_H	 // проверяет не был ли ранее определен макрос
#define PARENTELLIPSE_H	 // определяет макрос

#include <QPainter>
#include <QPainterPath>
#include <QWidget>

const int k100 = 100;

class ParentEllipse
    : public QWidget  // иерархия наследования QObject → QWidget → ParentEllipse → Balloon
{
   Q_OBJECT	 // макрос подключающий поддержку сигналов и слотов
       public
       :  // публичные методы доступны из любого места программы
          explicit ParentEllipse(
              QWidget* parent =
                  nullptr);	 // explicit запрещает неявное преобразование типов при создании объекта.
    // указание что родительского виджета нет и добавление в иерархию . теперь дочерние классы будут автоматически удаляться при закрытии

    // Управление позицией
    void setXPos(double x);


    double getXPos() const { return x_pos_; }
    /*
Геттер — это «дверь» для чтения данных.

Сеттер — это «фильтр» для записи данных.

Зачем:

Защита от некорректных значений.

Возможность добавить логику при чтении/записи.

Сокрытие внутренней реализации класса.
 */
    // Управление состоянием шарика
    void popBalloon();


    bool isPopped() const { return popped_; }
    const double balloonWidth = 60;	  // Ширина шарика
    const double balloonHeight = 80;  // Высота шарика
    const double yPosition = 30;	  // Фиксированная позиция по Y

   protected:  // защищенные методы доступны внутри класса и его наследников
    void paintEvent(QPaintEvent* event)
        override;  // для явного указания, что метод переопределяет (override) виртуальный метод базового класса

   private:	 // приватные методы доступны только внутри своего класса
    double x_pos_ = k100;  // Начальная позиция по X
    bool popped_ = false;  // Состояние шарика
};

#endif	// PARENTELLIPSE_H // завершает блок условной компиляции
