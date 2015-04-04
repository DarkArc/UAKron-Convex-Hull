#include "HullState.hpp"

HullState::HullState(const std::vector<QPoint>& points,
                     const std::vector<QLine>& lines)
                     : points(points), lines(lines) { }

std::vector<QPoint> HullState::getPoints() const {
  return points;
}

std::vector<QLine> HullState::getLines() const {
  return lines;
}
