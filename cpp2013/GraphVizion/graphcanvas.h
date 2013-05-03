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
#include <vector>

#include "typedefs.h"
#include "visualvertex.h"
#include "visualgraph.h"

class GraphCanvas : public QLabel
{
public:
    GraphCanvas();
    VisualGraph VG;
protected:    
    virtual void paintEvent(QPaintEvent* e);
};

#endif // GRAPHCANVAS_H
