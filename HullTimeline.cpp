#include "HullTimeline.hpp"

#include "HullState/DependantHullState.hpp"
#include "HullState/StandaloneHullState.hpp"

HullTimeline::HullTimeline() { }

HullTimeline::HullTimeline(const std::vector<std::shared_ptr<HullState>>& events) : events(events) {
  auto pts = events[0]->getPoints();

  int minX = pts[0].x();
  int minY = pts[0].y();
  int maxX = minX;
  int maxY = minY;

  for (auto& point : pts) {
    if (point.x() > maxX) {
      maxX = point.x();
    } else if (point.x() < minX) {
      minX = point.x();
    }

    if (point.y() > maxY) {
      maxY = point.y();
    } else if (point.y() < minY) {
      minY = point.y();
    }
  }

  min = QPoint(minX, minY);
  max = QPoint(maxX, maxY);
}

QPoint HullTimeline::getMin() const {
  return min;
}

QPoint HullTimeline::getMax() const {
  return max;
}

std::vector<std::shared_ptr<HullState>> HullTimeline::getEvents() const {
  return events;
}

int HullTimeline::getEventCount() const {
  return events.size();
}
