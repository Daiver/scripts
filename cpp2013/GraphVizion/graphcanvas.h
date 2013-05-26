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
#include "visualtool.h"

class GraphCanvas : public QLabel
{
public:
    GraphCanvas();
    VisualGraph VG;
    void setVertexAddTool();
    void setVertexMoveTool();
    void setVertexDeleteTool();
    void setEdgeAddTool();
protected:
    VisualTool* tool;
    virtual void paintEvent(QPaintEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
};

#endif // GRAPHCANVAS_H
