#ifndef VISUALEDGEADDTOOL_H
#define VISUALEDGEADDTOOL_H

#include <QPainter>

#include "visualtool.h"
#include "visualgraph.h"

class VisualEdgeAddTool : public VisualTool
{
public:
    VisualEdgeAddTool();

    virtual void mouseReleaseEvent(QMouseEvent *e, VisualGraph *g) ;
    virtual void mouseMoveEvent(QMouseEvent* e, VisualGraph *g);
    virtual void mousePressEvent(QMouseEvent* e, VisualGraph *g);
    virtual void paintEvent(QPaintEvent *e, QPainter* painter, VisualGraph *g);
protected:
    int firstEdge;
    graphvizion_td::Position mp;
};

#endif // VISUALEDGEADDTOOL_H
