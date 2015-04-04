#include "HullTimeline.hpp"

HullTimeline::HullTimeline() { }

HullTimeline::HullTimeline(const std::vector<HullState>& events) : events(events) {
  int maxX = 0;
  int maxY = 0;

  for (auto& point : events[0].getPoints()) {
    if (point.x() > maxX) {
      maxX = point.x();
    }
    if (point.y() > maxY) {
      maxY = point.y();
    }
  }

  max = QPoint(maxX, maxY);
}

QPoint HullTimeline::getMax() const {
  return max;
}

std::vector<HullState> HullTimeline::getEvents() const {
  return events;
}

int HullTimeline::getEventCount() const {
  return events.size();
}
