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

/** Construct a new DependantHullState object.

    Constructs a new DependantHullState object which
    holds a reference to some parent HullState.

    This reference is then manipulated by the additional points,
    point delete indexs, additional lines, and line delete
    indexs.

    Delete indexs must be defined in a manor in which the
    index n + 1 references the correct point or line
    to remove after n has been deleted.

    @param parent
    The parent HullState.

    @param remPoints
    The indexs of points to remove.

    @param addPoints
    The points to add.

    @param remLines
    The indexs of lines to remove.

    @param addLines
    The lines to add.
 */
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

/** Destruct the current DependantHullState object.

    Destructs the current DependantHullState object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
DependantHullState::~DependantHullState() { }

/** Retrieve the calculated points.

    Retrieves the points as calculated from the
    parent's point set, modified by the current
    object's removal point set, as well
    as the current object's add points set.

    Points are only added after all delete indexs
    have been exaughsted.

    @returns the points which make up the hull's
    state as of this HullState.
 */
std::vector<QPoint> DependantHullState::getPoints() const {
  auto parentPoints = parent->getPoints();
  for (auto& entry : remPoints) {
    parentPoints.erase(parentPoints.begin() + entry);
  }
  parentPoints.insert(parentPoints.end(), addPoints.begin(), addPoints.end());
  return parentPoints;
}

/** Retrieve the calculated lines.

    Retrieves the lines as calculated from the
    parent's line set, modified by the current
    object's removal line set, as well
    as the current object's add lines set.

    Lines are only added after all delete indexs
    have been exaughsted.

    @returns the lines which make up the hull's
    state as of this HullState.
 */
std::vector<QLine> DependantHullState::getLines() const {
  auto parentLines = parent->getLines();
  for (auto& entry : remLines) {
    parentLines.erase(parentLines.begin() + entry);
  }
  parentLines.insert(parentLines.end(), addLines.begin(), addLines.end());
  return parentLines;
}
