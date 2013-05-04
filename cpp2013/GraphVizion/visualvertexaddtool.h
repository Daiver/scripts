#ifndef VISUALADDTOOL_H
#define VISUALADDTOOL_H

#include "visualtool.h"
#include "typedefs.h"

class VisualVertexAddTool : public VisualTool
{
public:
    VisualVertexAddTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
};

#endif // VISUALADDTOOL_H
