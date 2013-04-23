#ifndef GRAPHCANVAS_H
#define GRAPHCANVAS_H

#include <QScrollArea>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include <QString>
#include <QImage>
#include <QRgb>

class GraphCanvas : public QLabel
{
public:
    GraphCanvas();
protected:
    virtual void paintEvent(QPaintEvent* e);
};

#endif // GRAPHCANVAS_H
