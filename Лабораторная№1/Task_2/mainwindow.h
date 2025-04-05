#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintscene.h"

/*
 * Главное окно приложения.
 *
 * Здесь располагаются:
 *   – QComboBox для выбора типа фигуры.
 *   – QSlider Rotation (0–360), который сразу устанавливает угол поворота выбранной фигуры.
 *   – QSlider ScaleX и QSlider ScaleY (диапазон 1–200, 100 соответствует 1.0),
 *      которые применяются только к выбранной фигуре (последней нарисованной).
 *   – Кнопка Clear – очищает сцену и сбрасывает все значения (слайдеры и поля расчёта).
 *   – Кнопки Calculate Area и Calculate Perimeter с соответствующими QLineEdit для вывода.
 *
 * При смене выбранной фигуры все слайдеры сбрасываются в начальное состояние, а поля расчёта очищаются.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    // Слот реагирует на смену выбранного типа фигуры в ComboBox:
    // сбрасывает слайдеры и очищает поля расчёта.
    void on_combobox_current_index_changed(const QString& text);
    // Слот для слайдера Rotation: сразу устанавливает угол выбранной фигуры.
    void on_rotation_slider_value_changed(int value);
    // Слоты для слайдеров масштабирования – применение происходит по отпусканию слайдера.
    void on_scale_x_slider_released();
    void on_scale_y_slider_released();
    // Кнопка Clear – очищает сцену и сбрасывает значения.
    void on_clear_button_clicked();
    // Кнопки расчёта площади и периметра.
    void on_calc_area_button_clicked();
    void on_calc_perim_button_clicked();

   private:
    // Применяет масштабирование только к выбранной фигуре.
    // Извлекаем коэффициенты масштабирования из значения слайдеров и формируем матрицу.
    void applyScaleToSelectedFigure();

   private:
    PaintScene* m_scene_;	 // Сцена для рисования фигур.
    QGraphicsView* m_view_;	 // Виджет для отображения сцены.

    QComboBox* m_comboBox_;		  // Выбор типа фигуры.
    QSlider* m_rotationSlider_;	  // Слайдер поворота (0–360).
    QPushButton* m_clearButton_;  // Кнопка очистки сцены.

    QSlider* m_scaleXSlider_;  // Слайдер масштабирования по X.
    QSlider* m_scaleYSlider_;  // Слайдер масштабирования по Y.
    double m_scaleFactorX_;	   // Текущий коэффициент масштабирования по X.
    double m_scaleFactorY_;	   // Текущий коэффициент масштабирования по Y.

    QPushButton* m_calcAreaButton_;	  // Кнопка расчёта площади.
    QPushButton* m_calcPerimButton_;  // Кнопка расчёта периметра.
    QLineEdit* m_areaLineEdit_;		  // Поле для вывода площади.
    QLineEdit* m_perimLineEdit_;	  // Поле для вывода периметра.
};

#endif	// MAINWINDOW_H
