#include "DependantHullState.hpp"

DependantHullState::DependantHullState(
  const HullState* parent,
  const std::vector<int>& remPoints,
  const std::vector<QPoint>& addPoints,
  const std::vector<int>& remLines,
  const std::vector<QLine>& addLines
) : parent(parent),
    remPoints(remPoints),
    addPoints(addPoints),
    remLines(remLines),
    addLines(addLines) { }

DependantHullState::~DependantHullState() { }

std::vector<QPoint> DependantHullState::getPoints() const {
  auto parentPoints = parent->getPoints();
  for (auto& entry : remPoints) {
    parentPoints.erase(parentPoints.begin() + entry);
  }
  parentPoints.insert(parentPoints.end(), addPoints.begin(), addPoints.end());
  return parentPoints;
}

std::vector<QLine> DependantHullState::getLines() const {
  auto parentLines = parent->getLines();
  for (auto& entry : remLines) {
    parentLines.erase(parentLines.begin() + entry);
  }
  parentLines.insert(parentLines.end(), addLines.begin(), addLines.end());
  return parentLines;
}
