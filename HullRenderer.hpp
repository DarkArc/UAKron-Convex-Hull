#ifndef HULLRENDERER_HPP
#define HULLRENDERER_HPP

#include <QtQuick>
#include <QRect>

#include "HullTimeline.hpp"

class HullRenderer : public QQuickPaintedItem {
  Q_OBJECT
  HullTimeline timeline;
  int position;
public:
  HullRenderer(QQuickItem *parent = 0);
  void paint(QPainter *painter);

  bool hasHull() const;

public slots:
  void setTimeline(const HullTimeline&);
  void advance();

private:
  QPointF adjustPoint(const QPoint&) const;
};

#endif
