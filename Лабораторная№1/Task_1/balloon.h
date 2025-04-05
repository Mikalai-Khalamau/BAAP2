#ifndef BALLOON_H
#define BALLOON_H

#include "parentellipse.h"
#include <QMouseEvent>

class Balloon : public ParentEllipse
{
    Q_OBJECT
public:
    explicit Balloon(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // BALLOON_H
