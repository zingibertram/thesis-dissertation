#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>

class PolygonView : public QGraphicsView // элемент интерфейса, отображает графическую сцену
                                         // здесь переопределён метод wheelEvent, чтобы менять размер изображения
{
    Q_OBJECT
public:
    explicit PolygonView(QWidget *parent = 0);
    
protected:
    void wheelEvent(QWheelEvent *event);
    double scaleFactor;
    static double const SCALE = 1.2;
    
};

#endif // POLYGONVIEW_H
