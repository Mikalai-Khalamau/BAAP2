#include "paintscene.h"

const int kTwo = 2;
const int k50 = 50;

// Подключаем все новые фигуры
#include "circle.h"
#include "eightpointedstar.h"
#include "ellipse.h"
#include "fivepointedstar.h"
#include "hexagon.h"
#include "rectangle.h"
#include "rhombys.h"
#include "sixpointedstar.h"
#include "square.h"
#include "triangle.h"

PaintScene::PaintScene(QObject* parent)
    : QGraphicsScene(parent),
      m_mode_(ActionMode::kNone),
      m_currentShapeType_("Круг"),
      m_newFigure_(nullptr),
      m_selectedFigure_(nullptr),
      m_offset_(0, 0),
      m_timer_(new QTimer(this)) {
    // Запускаем таймер обновления (можно использовать для анимаций, здесь оставляем на всякий случай)
    m_timer_->start(k50);
}

PaintScene::~PaintScene() = default;

void PaintScene::setCurrentShapeType(const QString& shapeType) {
    m_currentShapeType_ = shapeType;
}

Figure* PaintScene::selectedFigure() const {
    return m_selectedFigure_;
}

void PaintScene::resetSelection() {
    m_selectedFigure_ = nullptr;
}

void PaintScene::setTargetRotation(double angle) {
    // Если выбрана фигура, устанавливаем ей мгновенно угол поворота, равный значению слайдера.


    if (m_selectedFigure_ != nullptr) {
        m_selectedFigure_->setRotation(angle);
    }
}


void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Если кликнули по уже существующей фигуре – переходим в режим перемещения (Moving)
    QList<QGraphicsItem*> items_under_cursor = items(event->scenePos());
    if (!items_under_cursor.isEmpty()) {
        QGraphicsItem* top_item = items_under_cursor.first();
        auto* fig = dynamic_cast<Figure*>(top_item);


        if (fig != nullptr) {
            m_selectedFigure_ = fig;
            m_mode_ = ActionMode::kMoving;
            // Устанавливаем точку вращения в центр boundingRect() для корректного поворота и масштабирования
            m_selectedFigure_->setTransformOriginPoint(
                m_selectedFigure_->boundingRect().center());
            QPointF figure_pos = fig->pos();
            QPointF click_pos = event->scenePos();
            m_offset_ = figure_pos - click_pos;
            return;
        }
    }
    // Иначе – начинаем рисование новой фигуры (режим Drawing)
    m_mode_ = ActionMode::kDrawing;
    m_startPos_ = event->scenePos();

    // В зависимости от выбранного типа фигуры создаём соответствующий объект


    if (m_currentShapeType_ == "Круг") {
        m_newFigure_ = new Circle(0.0);
        m_newFigure_->setColor(Qt::yellow);
    } else if (m_currentShapeType_ == "Квадрат") {
        m_newFigure_ = new Square(0.0);
        m_newFigure_->setColor(Qt::green);
    } else if (m_currentShapeType_ == "Прямоугольник") {
        m_newFigure_ = new Rectangle(0.0, 0.0);
        m_newFigure_->setColor(Qt::magenta);
    } else if (m_currentShapeType_ == "Треугольник") {
        m_newFigure_ = new Triangle(0.0);
        m_newFigure_->setColor(Qt::cyan);
    } else if (m_currentShapeType_ == "Ромб") {
        m_newFigure_ = new Rhombus(0.0, 0.0);
        m_newFigure_->setColor(Qt::red);
    } else if (m_currentShapeType_ == "Правильный шестиугольник") {
        m_newFigure_ = new Hexagon(0.0);
        m_newFigure_->setColor(Qt::darkCyan);
    } else if (m_currentShapeType_ == "Пятиконечная звезда") {
        m_newFigure_ = new Star5(0.0);
        m_newFigure_->setColor(Qt::blue);
    } else if (m_currentShapeType_ == "Шестиконечная звезда") {
        m_newFigure_ = new Star6(0.0);
        m_newFigure_->setColor(Qt::white);
    } else if (m_currentShapeType_ == "Восьмиконечная звезда") {
        m_newFigure_ = new Star8(0.0);
        m_newFigure_->setColor(Qt::darkRed);
    } else if (m_currentShapeType_ == "Эллипс") {
        m_newFigure_ = new Ellipse(0.0, 0.0);
        m_newFigure_->setColor(Qt::gray);
    } else {
        qDebug() << "Unknown shape type:" << m_currentShapeType_;
        m_mode_ = ActionMode::kNone;
        m_newFigure_ = nullptr;
        return;
    }
    // Устанавливаем фигуру в точку клика (центр)
    m_newFigure_->setPos(m_startPos_);
    // Устанавливаем точку вращения в центр boundingRect() для корректного масштабирования и поворота
    m_newFigure_->setTransformOriginPoint(
        m_newFigure_->boundingRect().center());
    addItem(m_newFigure_);
    // Новая фигура становится выбранной
    m_selectedFigure_ = m_newFigure_;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {


    if (m_mode_ == ActionMode::kDrawing && m_newFigure_ != nullptr) {
        // При рисовании новой фигуры обновляем её размеры в зависимости от положения мыши
        QPointF curr_pos = event->scenePos();
        double dx = curr_pos.x() - m_startPos_.x();
        double dy = curr_pos.y() - m_startPos_.y();
        // Для каждого типа фигуры вызываем соответствующий метод изменения размеров
        if (auto* c = dynamic_cast<Circle*>(m_newFigure_)) {
            double r = qSqrt((dx * dx) + (dy * dy));
            c->setRadius(r);
        } else if (auto* s = dynamic_cast<Square*>(m_newFigure_)) {
            double half_side = qMax(qAbs(dx), qAbs(dy));
            s->setSide(kTwo * half_side);
        } else if (auto* r = dynamic_cast<Rectangle*>(m_newFigure_)) {
            double w = kTwo * qAbs(dx);
            double h = kTwo * qAbs(dy);
            r->setWidth(w);
            r->setHeight(h);
        } else if (auto* t = dynamic_cast<Triangle*>(m_newFigure_)) {
            double dist = qSqrt((dx * dx) + (dy * dy));
            t->setRadius(dist);
        } else if (auto* rh = dynamic_cast<Rhombus*>(m_newFigure_)) {
            double d1 = kTwo * qAbs(dx);
            double d2 = kTwo * qAbs(dy);
            rh->setD1(d1);
            rh->setD2(d2);
        } else if (auto* hx = dynamic_cast<Hexagon*>(m_newFigure_)) {
            double dist = qSqrt((dx * dx) + (dy * dy));
            hx->setRadius(dist);
        } else if (auto* st5 = dynamic_cast<Star5*>(m_newFigure_)) {
            double dist = qSqrt((dx * dx) + (dy * dy));
            st5->setRadius(dist);
        } else if (auto* st6 = dynamic_cast<Star6*>(m_newFigure_)) {
            double dist = qSqrt((dx * dx) + (dy * dy));
            st6->setRadius(dist);
        } else if (auto* st8 = dynamic_cast<Star8*>(m_newFigure_)) {
            double dist = qSqrt((dx * dx) + (dy * dy));
            st8->setRadius(dist);
        } else if (auto* el = dynamic_cast<Ellipse*>(m_newFigure_)) {
            double a = qAbs(dx);
            double b = qAbs(dy);
            el->setA(a);
            el->setB(b);
        }
    } else if (m_mode_ == ActionMode::kMoving && m_selectedFigure_ != nullptr) {
        // Перемещение выбранной фигуры: новая позиция = текущее положение мыши + смещение
        QPointF mouse_pos = event->scenePos();
        QPointF new_pos = mouse_pos + m_offset_;
        m_selectedFigure_->setPos(new_pos);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {


    if (m_mode_ == ActionMode::kDrawing) {
        // Завершаем режим рисования
        m_mode_ = ActionMode::kNone;
        m_newFigure_ = nullptr;
    } else if (m_mode_ == ActionMode::kMoving) {
        m_mode_ = ActionMode::kNone;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
