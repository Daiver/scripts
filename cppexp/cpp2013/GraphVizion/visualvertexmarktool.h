#ifndef VISUALVERTEXMARKTOOL_H
#define VISUALVERTEXMARKTOOL_H

#include "visualtool.h"

class VisualVertexMarkTool : public VisualTool
{
public:
    VisualVertexMarkTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g);
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
    virtual void paintEvent(QPaintEvent *e, QPainter* painter, VisualGraph *g);
};

#endif // VISUALVERTEXMARKTOOL_H
