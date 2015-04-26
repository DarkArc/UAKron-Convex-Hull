#include "HullTimeline.hpp"

#include "HullState/DependantHullState.hpp"
#include "HullState/StandaloneHullState.hpp"

HullTimeline::HullTimeline() { }

HullTimeline::HullTimeline(const std::vector<HullState*>& events) : events(events) {
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

HullTimeline::HullTimeline(const HullTimeline& orig) : min(orig.min), max(orig.max) {
  for (auto& entry : orig.events) {
    HullState* cpyState;
    DependantHullState* dependant;
    StandaloneHullState* standalone;
    if ((dependant = dynamic_cast<DependantHullState*>(entry))) {
      cpyState = new DependantHullState(*dependant);
    } else if ((standalone = dynamic_cast<StandaloneHullState*>(entry))) {
      cpyState = new StandaloneHullState(*standalone);
    }
    events.push_back(cpyState);
  }
}

HullTimeline::HullTimeline(
  HullTimeline&& orig
) : min(std::move(orig.min)),
    max(std::move(orig.max)),
    events(std::move(orig.events)) { }

HullTimeline::~HullTimeline() {
  for (auto entry : events) {
    delete entry;
  }
}

HullTimeline& HullTimeline::operator = (const HullTimeline& orig) {
  min = orig.min;
  max = orig.max;
  events = std::vector<HullState*>();

  for (auto& entry : orig.events) {
    HullState* cpyState;
    DependantHullState* dependant;
    StandaloneHullState* standalone;
    if ((dependant = dynamic_cast<DependantHullState*>(entry))) {
      cpyState = new DependantHullState(*dependant);
    } else if ((standalone = dynamic_cast<StandaloneHullState*>(entry))) {
      cpyState = new StandaloneHullState(*standalone);
    }
    events.push_back(cpyState);
  }
  return *this;
}

HullTimeline& HullTimeline::operator = (HullTimeline&& orig) {
  min = std::move(orig.min);
  max = std::move(orig.max);
  events = std::move(orig.events);
  return *this;
}

QPoint HullTimeline::getMin() const {
  return min;
}

QPoint HullTimeline::getMax() const {
  return max;
}

std::vector<HullState*> HullTimeline::getEvents() const {
  return events;
}

int HullTimeline::getEventCount() const {
  return events.size();
}
