#include "mainwindow.h"

const double kTwo = 2.0;
const int kOne = 1;
const double k1 = 1.0;
const int k100 = 100;
const double k1000 = 100.0;
const int k1200 = 1200;
const int k200 = 200;
const int k360 = 360;
const int k600 = 600;
/*
 * Конструктор главного окна.
 * Здесь создаётся интерфейс приложения (без использования .ui-файла).
 * В верхней панели размещаются:
 *  – QComboBox для выбора типа фигуры
 *  – QSlider для поворота (Rotation)
 *  – Кнопка Clear
 *  – Слайдеры масштабирования по X и Y (ScaleX, ScaleY)
 *  – Панель для расчёта площади и периметра (с кнопками и полями вывода)
 * При смене выбранной фигуры все слайдеры сбрасываются до начальных значений,
 * а поля расчёта очищаются.
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_scene_(nullptr),
      m_view_(nullptr),
      m_comboBox_(nullptr),
      m_rotationSlider_(nullptr),
      m_clearButton_(nullptr),
      m_scaleXSlider_(nullptr),
      m_scaleYSlider_(nullptr),
      m_scaleFactorX_(1.0),
      m_scaleFactorY_(1.0),
      m_calcAreaButton_(nullptr),
      m_calcPerimButton_(nullptr),
      m_areaLineEdit_(nullptr),


      m_perimLineEdit_(nullptr) {
    // Создаём центральный виджет и основной вертикальный layout
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* main_lay_out = new QVBoxLayout(central);

    // Верхняя панель управления
    auto* top_layout = new QHBoxLayout();
    main_lay_out->addLayout(top_layout);

    // Создаём ComboBox для выбора типа фигуры
    m_comboBox_ = new QComboBox(this);
    m_comboBox_->addItem("Круг");
    m_comboBox_->addItem("Квадрат");
    m_comboBox_->addItem("Прямоугольник");
    m_comboBox_->addItem("Треугольник");
    m_comboBox_->addItem("Ромб");
    m_comboBox_->addItem("Правильный шестиугольник");
    m_comboBox_->addItem("Пятиконечная звезда");
    m_comboBox_->addItem("Шестиконечная звезда");
    m_comboBox_->addItem("Восьмиконечная звезда");
    m_comboBox_->addItem("Эллипс");
    top_layout->addWidget(m_comboBox_);
    // При смене выбранной фигуры сбрасываем слайдеры и поля
    connect(m_comboBox_, &QComboBox::currentTextChanged, this,
            &MainWindow::on_combobox_current_index_changed);

    // Слайдер для поворота (Rotation)
    auto* rot_label = new QLabel("Поворот:", this);
    top_layout->addWidget(rot_label);
    m_rotationSlider_ = new QSlider(Qt::Horizontal, this);
    m_rotationSlider_->setRange(0, k360);
    m_rotationSlider_->setValue(0);	 // 0 градусов по умолчанию
    top_layout->addWidget(m_rotationSlider_);
    // При изменении слайдера сразу обновляем трансформацию выбранной фигуры
    connect(m_rotationSlider_, &QSlider::valueChanged, this,
            &MainWindow::on_rotation_slider_value_changed);

    // Кнопка Clear – очищает сцену и сбрасывает все значения
    m_clearButton_ = new QPushButton("Очистить сцену", this);
    top_layout->addWidget(m_clearButton_);
    connect(m_clearButton_, &QPushButton::clicked, this,
            &MainWindow::on_clear_button_clicked);

    // Слайдер для масштабирования по X
    auto* scale_x_label = new QLabel("Масштабирование по X:", this);
    top_layout->addWidget(scale_x_label);
    m_scaleXSlider_ = new QSlider(Qt::Horizontal, this);
    m_scaleXSlider_->setRange(kOne, k200);	// Значение 100 соответствует 1.0
    m_scaleXSlider_->setValue(k100);
    top_layout->addWidget(m_scaleXSlider_);
    // Применение масштабирования происходит по отпусканию слайдера
    connect(m_scaleXSlider_, &QSlider::sliderReleased, this,
            &MainWindow::on_scale_x_slider_released);

    // Слайдер для масштабирования по Y
    auto* scale_y_label = new QLabel("Масштабирование по Y:", this);
    top_layout->addWidget(scale_y_label);
    m_scaleYSlider_ = new QSlider(Qt::Horizontal, this);
    m_scaleYSlider_->setRange(kOne, k200);
    m_scaleYSlider_->setValue(k100);
    top_layout->addWidget(m_scaleYSlider_);
    connect(m_scaleYSlider_, &QSlider::sliderReleased, this,
            &MainWindow::on_scale_y_slider_released);

    // Панель для расчёта площади и периметра
    auto* calc_layout = new QHBoxLayout();
    main_lay_out->addLayout(calc_layout);
    m_calcAreaButton_ = new QPushButton("Вычислить площадь", this);
    calc_layout->addWidget(m_calcAreaButton_);
    connect(m_calcAreaButton_, &QPushButton::clicked, this,
            &MainWindow::on_calc_area_button_clicked);
    m_areaLineEdit_ = new QLineEdit(this);
    m_areaLineEdit_->setReadOnly(true);
    calc_layout->addWidget(m_areaLineEdit_);
    m_calcPerimButton_ = new QPushButton("Вычислить периметр", this);
    calc_layout->addWidget(m_calcPerimButton_);
    connect(m_calcPerimButton_, &QPushButton::clicked, this,
            &MainWindow::on_calc_perim_button_clicked);
    m_perimLineEdit_ = new QLineEdit(this);
    m_perimLineEdit_->setReadOnly(true);
    calc_layout->addWidget(m_perimLineEdit_);

    // Создаём сцену и QGraphicsView
    m_scene_ = new PaintScene(this);
    m_view_ = new QGraphicsView(m_scene_, this);
    main_lay_out->addWidget(m_view_);

    // Задаём размеры окна и заголовок
    resize(k1200, k600);
    setWindowTitle("Выберите фигуру и творите ");
}

MainWindow::~MainWindow() = default;

/*
 * Слот on_comboBox_currentIndexChanged:
 * Вызывается при смене выбранной фигуры в ComboBox.
 * Передаёт новый тип фигуры в PaintScene и сбрасывает все слайдеры и поля расчёта.
 */
void MainWindow::on_combobox_current_index_changed(const QString& text) {
    m_scene_->setCurrentShapeType(text);
    // Сброс слайдера поворота – 0 градусов
    m_rotationSlider_->setValue(0);
    // Сброс слайдеров масштабирования – 100 означает 1.0 (без изменений)
    m_scaleXSlider_->setValue(k100);
    m_scaleYSlider_->setValue(k100);
    m_scaleFactorX_ = k1;
    m_scaleFactorY_ = k1;
    // Очищаем поля вывода площади и периметра
    m_areaLineEdit_->clear();
    m_perimLineEdit_->clear();
}

/*
 * Слот on_rotation_slider_value_changed:
 * При изменении слайдера Rotation сразу обновляем трансформацию выбранной фигуры.
 */
void MainWindow::on_rotation_slider_value_changed(int value) {
    applyScaleToSelectedFigure();
}

/*
 * Слот on_scale_x_slider_released:
 * При отпускании слайдера ScaleX вычисляем коэффициент и обновляем трансформацию.
 */
void MainWindow::on_scale_x_slider_released() {
    auto val = static_cast<double>(m_scaleXSlider_->value());
    m_scaleFactorX_ = val / k1000;
    applyScaleToSelectedFigure();
}

/*
 * Слот on_scale_y_slider_released:
 * Аналогично для ScaleY.
 */
void MainWindow::on_scale_y_slider_released() {
    auto val = static_cast<double>(m_scaleYSlider_->value());
    m_scaleFactorY_ = val / k1000;
    applyScaleToSelectedFigure();
}

/*
 * Слот on_clear_Button_clicked:
 * Очищает сцену, сбрасывает выбранную фигуру, очищает поля расчёта и возвращает слайдеры в начальное положение.
 */
void MainWindow::on_clear_button_clicked() {
    m_scene_->clear();
    m_scene_->resetSelection();
    m_areaLineEdit_->clear();
    m_perimLineEdit_->clear();
    m_rotationSlider_->setValue(0);
    m_scaleXSlider_->setValue(k100);
    m_scaleYSlider_->setValue(k100);
    m_scaleFactorX_ = k1;
    m_scaleFactorY_ = k1;
}

/*
 * Слот on_calcAreaButton_clicked:
 * Вычисляет площадь выбранной фигуры с учётом текущего масштабирования.
 * Площадь умножается на произведение коэффициентов масштабирования (определённое нами).
 */
void MainWindow::on_calc_area_button_clicked() {
    Figure* f = m_scene_->selectedFigure();


    if (f != nullptr) {
        // Эффективная площадь = базовая площадь * (scaleX * scaleY)
        double effective_area = f->area() * (m_scaleFactorX_ * m_scaleFactorY_);
        m_areaLineEdit_->setText(QString::number(effective_area, 'f', kTwo));
    }
}

/*
 * Слот on_calcPerimButton_clicked:
 * Вычисляет периметр выбранной фигуры с учётом масштабирования.
 * Используем среднее значение масштабирования для периметра.
 */
void MainWindow::on_calc_perim_button_clicked() {
    Figure* f = m_scene_->selectedFigure();


    if (f) {
        double effective_perimeter =
            f->perimeter() * ((m_scaleFactorX_ + m_scaleFactorY_) / kTwo);
        m_perimLineEdit_->setText(
            QString::number(effective_perimeter, 'f', kTwo));
    }
}

/*
 * Функция applyScaleToSelectedFigure:
 * Вычисляет и устанавливает комбинированную трансформацию для выбранной фигуры.
 * Трансформация включает:
 *   – Поворот на угол, заданный слайдером Rotation.
 *   – Невыровненное масштабирование по осям X и Y, заданное слайдерами ScaleX и ScaleY.
 * Трансформация выполняется относительно центра boundingRect(), чтобы фигура не смещалась.
 * При этом, если слайдеры находятся в положении по умолчанию (Rotation=0, Scale=1.0),
 * матрица превращается в единичную, и фигура возвращается к исходному виду.
 */
void MainWindow::applyScaleToSelectedFigure() {
    // Получаем выбранную фигуру из сцены
    Figure* f = m_scene_->selectedFigure();


    if (f == nullptr) {
        return;
    }

    // Устанавливаем точку вращения в центр boundingRect() для корректного преобразования
    QPointF center = f->boundingRect().center();
    f->setTransformOriginPoint(center);

    // Получаем текущий угол поворота из слайдера
    int rot = m_rotationSlider_->value();

    // Формируем абсолютную матрицу преобразования:
    // 1. Переносим систему координат в центр фигуры.
    // kTwo. Поворачиваем на угол rot.
    // 3. Масштабируем по осям X и Y.
    // 4. Переносим систему координат обратно.
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(rot);
    t.scale(m_scaleFactorX_, m_scaleFactorY_);
    t.translate(-center.x(), -center.y());

    // Устанавливаем полученную трансформацию как абсолютную (без накопления предыдущих)
    f->setTransform(t);
}
