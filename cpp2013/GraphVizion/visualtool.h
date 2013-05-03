#ifndef VISUALTOOL_H
#define VISUALTOOL_H
#include <QMouseEvent>
#include "visualgraph.h"

class VisualTool
{
public:
    VisualTool();
    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) = 0;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g) = 0;
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g) = 0;
};

#endif // VISUALTOOL_H
