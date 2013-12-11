#include "polygonview.h"

PolygonView::PolygonView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void PolygonView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        this->scale(SCALE, SCALE);
    }
    else
    {
        this->scale(1.0 / SCALE, 1.0 / SCALE);
    }
}
