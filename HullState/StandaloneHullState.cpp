#include "StandaloneHullState.hpp"

StandaloneHullState::StandaloneHullState(const std::vector<QPoint>& points,
                     const std::vector<QLine>& lines)
                     : points(points), lines(lines) { }

StandaloneHullState::~StandaloneHullState() { }

std::vector<QPoint> StandaloneHullState::getPoints() const {
  return points;
}

std::vector<QLine> StandaloneHullState::getLines() const {
  return lines;
}
