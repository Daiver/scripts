#ifndef VISUALEDGEADDTOOL_H
#define VISUALEDGEADDTOOL_H

#include "visualtool.h"

class VisualEdgeAddTool : public VisualTool
{
public:
    VisualEdgeAddTool();

    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
protected:
    int firstEdge;
};

#endif // VISUALEDGEADDTOOL_H
