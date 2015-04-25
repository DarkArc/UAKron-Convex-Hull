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

  Q_INVOKABLE int curPosition() const;
  Q_INVOKABLE int maxPosition() const;

public slots:
  void setTimeline(const HullTimeline&);
  void advance();

signals:
  void stageComplete() const;

private:
  QPointF adjustPoint(const QPoint&) const;
};

#endif
