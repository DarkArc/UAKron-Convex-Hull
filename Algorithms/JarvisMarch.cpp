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

#include "JarvisMarch.hpp"

#include <QLine>

#include "../HullState/DependantHullState.hpp"
#include "../HullState/StandaloneHullState.hpp"


/** Construct a new JarvisMarch object.

    Constructs a new empty JarvisMarch object.
 */
JarvisMarch::JarvisMarch() { }

/** Destruct the current JarvisMarch object.

    Destructs the current JarvisMarch object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
JarvisMarch::~JarvisMarch() { }

/** Retrieve the name of this algorithm.

    @returns the QString "Jarvis March".
 */
QString JarvisMarch::name() const {
  return "Jarvis March";
}

/** Execute the aglorithm.

    Executes the aglorithm on the provided set of points,
    while capturing individual states of the algorithm in
    HullState snapshots.

    Complexity is O(n^2).

    @param nPts
    The points to make convex hull out of.

    @returns the HullTimeline representing all states
    of the algorithm.
 */
HullTimeline JarvisMarch::getTimeline(const std::vector<QPoint>& nPts) {
  // Update internal class level variables
  pts = nPts;
  stages = std::vector<std::shared_ptr<HullState>>();

  // Create an initial point snapshot
  stages.emplace_back(new StandaloneHullState(pts, std::vector<QLine>()));

  // Must be at least 3 points
  if (nPts.size() < 3) {
    return HullTimeline(stages);
  }

  timeTrackInit();

  // Find left most point
  int left = 0;
  for (unsigned int i = 0; i < nPts.size(); ++i) {
    if (nPts[i].x() < nPts[left].x()) {
      left = i;
    }
  }

  // Initialize the vector to hold the points
  std::vector<QPoint> hull;

  // Setup the left value
  int p = left;
  hull.push_back(nPts[p]);

  while (true) {
    int q = (p + 1) % nPts.size();
    // Grab the last "clean" snapshot
    // which doesn't have a test line
    auto lastClean = *stages.rbegin();
    for (unsigned int i = 0; i < nPts.size(); ++i) {
      // Continue adjusting q if there is a counter
      // clockwise turn
      if (ccw(nPts[p], nPts[i], nPts[q]) == 2) {
        q = i;
      }

      // Record the time, ommitting the snapshot capture
      timeTrackRecord();
      stages.push_back(captureSnapshot(lastClean, hull, nPts[i]));
      timeTrackUpdate();
    }

    // Update p so that it is equal to q
    p = q;
    // If p is equal to left, there is no need to add
    // it to the hull, or create a snapshot of it,
    // as this is handled elsewhere
    if (p == left) {
      break;
    }

    // ADd p to the hull
    hull.push_back(nPts[q]);

    // Record the time, ommitting the snapshot capture
    timeTrackRecord();
    stages.push_back(captureSnapshot(lastClean, hull, nPts[q]));
    timeTrackUpdate();
  }

  // Finalize the hull by adding the final line
  // so that the final display is of a complete hull
  std::shared_ptr<HullState> last = *stages.rbegin();
  auto finalLines = last->getLines();

  // Remove the test line
  finalLines.pop_back();

  // Create a line connecting the last point of the final
  // point set to the first point
  finalLines.emplace_back(*hull.begin(), *hull.rbegin());

  stages.emplace_back(new StandaloneHullState(hull, finalLines));

  return HullTimeline(stages);
}

/** Capture an algorithm snapshot.

    Captures a snapshot of the algorithm at the current
    time using a StandaloneHullState using the original
    point set for the points, and the provided points
    for line generation.

    @param hullPts
    The points of the convex hull to construct the line
    set from.

    @return a shared_ptr to a StandaloneHullState
    holding the captured snapshot.
 */
std::shared_ptr<HullState> JarvisMarch::captureSnapshot(const std::vector<QPoint>& hullPts) const {
  std::vector<QLine> lSnap;

  // Reserve memory
  lSnap.reserve(hullPts.size() - 1);

  // Create the lines based on the hullStack
  for (unsigned int k = 0; k < hullPts.size() - 1; ++k) {
    lSnap.emplace_back(hullPts[k], hullPts[k + 1]);
  }

  return std::shared_ptr<HullState>(new StandaloneHullState(pts, lSnap));
}

/** Capture an algorithm snapshot.

    Captures a snapshot of the algorithm at the current
    time using either a StandaloneHullState or
    a DependantHullState.

    If there are no lines in the previous HullState
    then a StandaloneHullState shall be used.

    If there are lines in the previous HullState
    then a DependantHullState shall be used.

    @param last
    A shared_ptr to the last HullState.

    @param curHull
    The current points on the hull which will be used for line
    generation as a fallback.

    @param testPt
    The testPt or nextPt which a line will be drawn to from
    the previous HullState's end line, or in the case of
    falling back to a StandaloneHullState, this point
    will be added onto the list of points in curHull.

    @return a shared_ptr to either a Standalone or Dependant HullState
    holding the captured snapshot.
 */
std::shared_ptr<HullState> JarvisMarch::captureSnapshot(std::shared_ptr<HullState> last, std::vector<QPoint> curHull, const QPoint& testPt) const {
  auto lastLines = last->getLines();

  // If there is no previous line, there is no way to leap from
  // its second point, so instead create a StandaloneHullState
  // with the point added to the point testPt set
  if (lastLines.empty()) {
    curHull.push_back(testPt);
    return captureSnapshot(curHull);
  }

  // Take advantage of the previous HullState
  // and build a line form its last line's end point
  // to testPt
  return std::shared_ptr<HullState>(
    new DependantHullState(
      last,
      std::vector<int>(),
      std::vector<QPoint>(),
      std::vector<int>(),
      std::vector<QLine>({QLine(lastLines.rbegin()->p2(), testPt)})
    )
  );
}

/** Calculate the direction

    Calculates the direction based on the cross product.
    This function computes the z-coordinate of the cross product

    Complexity is O(1). Reference http://en.wikipedia.org/wiki/Graham_scan
    for psuedo code implementation.

    @param p1
    The first point to compare.

    @param p2
    The second point to compare.

    @param p3
    The third point to compare.

    @returns 0 if the points are colinear, 1 if there is a clock
    wise direction, and 2 if there is a conterclockwise direction.
 */
int JarvisMarch::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
  int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
            (p2.x() - p1.x()) * (p3.y() - p2.y());

  if (val == 0) return 0;   // colinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}
