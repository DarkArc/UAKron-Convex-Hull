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

#include "StandaloneHullState.hpp"

/** Construct a new StandaloneHullState object.

    Constructs a new StandaloneHullState object which
    stores the points, and lines of the hull.

    @param points
    The QPoints to store.

    @param lines
    The QLines to store.
 */
StandaloneHullState::StandaloneHullState(const std::vector<QPoint>& points,
                     const std::vector<QLine>& lines)
                     : points(points), lines(lines) { }

/** Destruct the current StandaloneHullState object.

    Destructs the current StandaloneHullState object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
StandaloneHullState::~StandaloneHullState() { }

/** Retrieve the stored points.

    Retrieves the stored points on the hull
    which compose the hull's current state.

    @returns the points which make up the hull's
    state as of this HullState.
 */
std::vector<QPoint> StandaloneHullState::getPoints() const {
  return points;
}

/** Retrieve the stored lines.

    Retrieves the stored lines on the hull
    which compose the hull's current state.

    @returns the lines which make up the hull's
    state as of this HullState.
 */
std::vector<QLine> StandaloneHullState::getLines() const {
  return lines;
}
