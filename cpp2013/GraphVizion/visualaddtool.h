#ifndef VISUALADDTOOL_H
#define VISUALADDTOOL_H

#include "visualtool.h"
#include "typedefs.h"

class VisualAddTool : public VisualTool
{
public:
    VisualAddTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
};

#endif // VISUALADDTOOL_H
