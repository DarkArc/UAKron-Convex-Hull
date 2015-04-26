#include "HullRenderer.hpp"

#include <QDebug>

HullRenderer::HullRenderer(QQuickItem *parent) : QQuickPaintedItem(parent) {
  setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void HullRenderer::paint(QPainter *painter) {

  if (!hasHull()) return;

  painter->setRenderHint(QPainter::Antialiasing);

  QPen pointPen(QBrush(Qt::blue), 10, Qt::SolidLine, Qt::RoundCap);
  QPen linePen(QBrush(Qt::black), 4, Qt::SolidLine, Qt::RoundCap);

  HullState state = timeline.getEvents()[position];

  // Draw Points
  painter->setPen(pointPen);
  for (auto& point : state.getPoints()) {
    painter->drawPoint(adjustPoint(point));
  }

  // Draw Lines
  painter->setPen(linePen);
  for (auto& line : state.getLines()) {
    auto&& start = adjustPoint(line.p1());
    auto&& end = adjustPoint(line.p2());
    painter->drawLine(start, end);
  }

  emit stageComplete();
}

bool HullRenderer::hasHull() const {
  return timeline.getEventCount() > 0;
}

int HullRenderer::curPosition() const {
  return position + 1;
}

int HullRenderer::maxPosition() const {
  return timeline.getEventCount();
}

void HullRenderer::setTimeline(const HullTimeline& timeline) {
  this->timeline = timeline;
  this->position = 0;
  update();
}

void HullRenderer::advance() {
  if (curPosition() < maxPosition()) {
    ++position;
    update();
  }
}

QPointF HullRenderer::adjustPoint(const QPoint& point) const {
  QPoint min = timeline.getMin();
  QPoint max = timeline.getMax();
  max.setX(max.x() - min.x());
  max.setY(max.y() - min.y());

  double ratioX = (point.x() - min.x()) / static_cast<double>(max.x());
  double ratioY = (max.y() - (point.y() - min.y())) / static_cast<double>(max.y());

  auto boundingRec = contentsBoundingRect();
  return QPointF(((boundingRec.width() - 20) * ratioX) + 10, ((boundingRec.height() - 20) * ratioY) + 10);
}
