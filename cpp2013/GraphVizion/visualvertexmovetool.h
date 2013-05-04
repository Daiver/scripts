#ifndef VISUALVERTEXMOVETOOL_H
#define VISUALVERTEXMOVETOOL_H

#include "visualtool.h"

class VisualVertexMoveTool : public VisualTool
{
public:
    VisualVertexMoveTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
protected:
    bool isPressed;
    VisualVertex *vertex;
};

#endif // VISUALVERTEXMOVETOOL_H
