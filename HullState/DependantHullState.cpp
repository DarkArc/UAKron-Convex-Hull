// Copyright (C) 2015 Wyatt Childers & Emil Heineking
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "DependantHullState.hpp"

DependantHullState::DependantHullState(
  const std::shared_ptr<HullState> parent,
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
