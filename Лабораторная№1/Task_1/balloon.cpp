#include "balloon.h"
#include <QMouseEvent>

const double k20 = 2.0;
Balloon::Balloon(QWidget* parent) : ParentEllipse(parent) {
    // Начальная позиция по центру горизонтали
    setXPos((width() / k20) - (balloonWidth / k20));
}

void Balloon::mousePressEvent(QMouseEvent* event) {
    if (!isPopped()) {	//если шарик уже лопнут, клики игнорируются.
        QPoint click_pos =
            event->pos();  //возвращает позицию клика относительно виджета
        QPointF center((getXPos() + (balloonWidth / 2)),
                       yPosition + (balloonHeight / 2));

        // Проверка попадания в эллипс (математическая формула)
        qreal dx = (click_pos.x() - center.x()) / (balloonWidth / 2);
        qreal dy = (click_pos.y() - center.y()) / (balloonHeight / 2);


        if (dx * dx + dy * dy <= 1.0) {
            popBalloon();
        }
        /*
Центр эллипса:

getXPos() — текущая позиция левого края шарика по X.

balloonWidth/2 — смещение до центра по горизонтали.

yPosition — фиксированная позиция верхнего края шарика по Y (из ParentEllipse).

balloonHeight/2 — смещение до центра по вертикали.

Нормализация координат:

dx и dy приводятся к диапазону [-1, 1], где:

dx = 1 — клик на правой границе эллипса.

dx = -1 — клик на левой границе.

Уравнение эллипса:
Формула dx² + dy² <= 1 проверяет, находится ли точка внутри эллипса.
Для круга это уравнение превращается в x² + y² <= 1, для эллипса — масштабируется радиусами.

          */
    }
}
