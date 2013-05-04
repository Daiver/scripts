#ifndef VISUALVERTEXDELETETOOL_H
#define VISUALVERTEXDELETETOOL_H
#include "visualtool.h"

class VisualVertexDeleteTool : public VisualTool
{
public:
    VisualVertexDeleteTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
};

#endif // VISUALVERTEXDELETETOOL_H
