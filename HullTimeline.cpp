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

#include "HullTimeline.hpp"

#include "HullState/DependantHullState.hpp"
#include "HullState/StandaloneHullState.hpp"

/** Construct a new HullTimeline object.

    Constructs a new empty HullTimeline object.
 */
HullTimeline::HullTimeline() { }

/** Construct a new HullTimeline object.

    Constructs a new HullTimeline object with
    the defined event vector.

    Then performns an anayalsis on the points
    of the first event, finding the minimum, and
    maximum point for later user by the HullRenderer.

    @param events
    The event vector which this object shall provide.
 */
HullTimeline::HullTimeline(const std::vector<std::shared_ptr<HullState>>& events) : events(events) {
  // Fetch the points of the first event
  auto pts = events[0]->getPoints();

  // Establish a starting point
  int minX = pts[0].x();
  int minY = pts[0].y();
  int maxX = minX;
  int maxY = minY;

  // Go through all points, expanding or constricting
  // the min & max as necissary
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

  // Convert the integers into a proper QPoint
  // for storage
  min = QPoint(minX, minY);
  max = QPoint(maxX, maxY);
}

/** Retrieves the minimum point.

    Retrieves the minimum point of the first
    event as defined by the event series this
    object was constructed. If this object
    has an empty event vector, this point will
    be the default constructed value of a
    QPoint.

    @returns the QPoint which holds the lowest
    x & y position of all points in the event vector.
 */
QPoint HullTimeline::getMin() const {
  return min;
}

/** Retrieves the maximum point.

    Retrieves the maximum point of the first
    event as defined by the event series this
    object was constructed. If this object
    has an empty event vector, this point will
    be the default constructed value of a
    QPoint.

    @returns the QPoint which holds the greatest
    x & y position of all points in the event vector.
 */
QPoint HullTimeline::getMax() const {
  return max;
}

/** Retrieves the event vector.

    Retrieves the event vector held
    by this object.

    @returns the event vector held by this
    object.
 */
std::vector<std::shared_ptr<HullState>> HullTimeline::getEvents() const {
  return events;
}

/** Retrieves the number of events.

    Retrieves the number of events in
    the event vector, without requiring
    a clone of the event vector object.

    @returns the number of elements in the
    event vector.
 */
int HullTimeline::getEventCount() const {
  return events.size();
}
