#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include "figure.h"

/*
 * Класс PaintScene:
 *
 * Обрабатывает события мыши для:
 *   – Рисования новой фигуры (режим Drawing)
 *   – Перемещения выбранной фигуры (режим Moving)
 *
 * При нажатии мыши, если клик происходит по существующей фигуре, она выбирается (режим Moving).
 * Иначе создаётся новая фигура выбранного типа, положение которой задаётся первым кликом,
 * а её размеры обновляются по мере перемещения мыши до отпускания кнопки.
 *
 * Для поворота и масштабирования точка вращения устанавливается равной центру boundingRect() фигуры.
 */
class PaintScene : public QGraphicsScene {
    Q_OBJECT
   public:
    explicit PaintScene(QObject* parent = nullptr);
    ~PaintScene();

    // Устанавливает тип фигуры для рисования (например, "Circle", "Square", и т.д.)
    void setCurrentShapeType(const QString& shapeType);
    // Возвращает указатель на выбранную фигуру (последняя, по которой кликнули)
    Figure* selectedFigure() const;
    // Сбрасывает выбранную фигуру (например, при очистке сцены)
    void resetSelection();

    // Устанавливает угол поворота выбранной фигуры (без анимации)
    void setTargetRotation(double angle);

   public slots:

   protected:
    // Обработка событий мыши:
    //   – mousePressEvent: выбираем фигуру для перемещения или начинаем рисование новой
    //   – mouseMoveEvent: обновляем размеры новой фигуры или перемещаем выбранную
    //   – mouseReleaseEvent: завершаем режим Drawing или Moving
    void mousePressEvent(QGraphicsSceneMouseEvent* event) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) ;

   private:
    // Режим работы сцены: нет, рисование или перемещение
    enum class ActionMode { kNone, kDrawing, kMoving };

    ActionMode m_mode_;			  // Текущий режим
    QString m_currentShapeType_;  // Тип фигуры для рисования

    // Для режима Drawing
    Figure* m_newFigure_;  // Фигура, которая рисуется
    QPointF m_startPos_;   // Точка начала рисования (центр)

    // Для режима Moving
    Figure* m_selectedFigure_;	// Выбранная фигура
    QPointF m_offset_;			// Смещение между точкой клика и позицией фигуры

    // Таймер обновления (не используется для анимации поворота – поворот производится мгновенно)
    QTimer* m_timer_;
};

#endif	// PAINTSCENE_H
