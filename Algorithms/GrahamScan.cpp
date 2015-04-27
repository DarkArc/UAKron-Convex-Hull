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

#include "GrahamScan.hpp"

#include <QLine>

#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

#include "../HullState/StandaloneHullState.hpp"

/** Construct a new GrahamScan object.

    Constructs a new empty GrahamScan object.
 */
GrahamScan::GrahamScan() { }

/** Destruct the current GrahamScan object.

    Destructs the current GrahamScan object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
GrahamScan::~GrahamScan() { }

/** Retrieve the name of this algorithm.

    @returns the QString "Graham Scan".
 */
QString GrahamScan::name() const {
  return "Graham Scan";
}

/** Execute the aglorithm.

    Executes the aglorithm on the provided set of points,
    while capturing individual states of the algorithm in
    HullState snapshots.

    Complexity is:
      Find smallest y value = O(n)
      Sort pts = O(nlog(n))
      Find hull = O(n)

    The full relation is: nlog(n) + 2n. Dropping the linear factor we get
    O(nlog(n)) complexity for the full algorithm.

    @param nPts
    The points to make convex hull out of.

    @returns the HullTimeline representing all states
    of the algorithm.
 */
HullTimeline GrahamScan::getTimeline(const std::vector<QPoint>& nPts) {
  // Update internal class level variables
  pts = nPts;
  stages = std::vector<std::shared_ptr<HullState>>();

  // Create an initial point snapshot
  stages.emplace_back(new StandaloneHullState(nPts, std::vector<QLine>()));
  // Start the time Tracker
  timeTrackInit();

  // Make the initial point the lowest y
  std::swap(pts[0], findSmallestYPoint());

  // Sort the points
  std::stable_sort(pts.begin() + 1, pts.end(), *this);

  // Create the hull's stack
  std::vector<QPoint> hullStack;
  for (unsigned int i = 0; i < 3; ++ i) {
    hullStack.push_back(pts[i]);

    // Record the time, ommitting the snapshot capture
    timeTrackRecord();
    stages.push_back(captureSnapShot(hullStack, i));
    timeTrackUpdate();
  }

  // Process the resulting stack
  for (unsigned int i = 3; i < pts.size(); ++i) {
    // If there are more than two points, compare the cross
    // product to determine the of the "turn"
    // if the turn is not counter clockwise
    // pop off points until there is a counter clockwise turn
    while (hullStack.size() > 1 && ccw(*(hullStack.rbegin() + 1), *hullStack.rbegin(), pts[i]) != 2) {
      hullStack.pop_back();

      // Record the time, ommiting the snapshot capture
      timeTrackRecord();
      stages.push_back(captureSnapShot(hullStack, i));
      timeTrackUpdate();
    }

    // Pushback the point as being the next point in the hull (thus far)
    hullStack.push_back(pts[i]);

    // Record the time ommiting the snapshot capture
    timeTrackRecord();
    stages.push_back(captureSnapShot(hullStack, i));
    timeTrackUpdate();
  }

  // Finalize the hull by adding the final line
  // so that the final display is of a complete hull
  std::shared_ptr<HullState> last = *stages.rbegin();
  auto finalPoints = last->getPoints();
  auto finalLines = last->getLines();

  // Create a line connecting the last point of the final
  // point set to the first point
  finalLines.emplace_back(*finalPoints.begin(), *finalPoints.rbegin());

  stages.emplace_back(new StandaloneHullState(finalPoints, finalLines));

  return HullTimeline(stages);
}

/** Capture an algorithm snapshot.

    Captures a snapshot of the algorithm at the current
    time using a StandaloneHullState using the provided
    hullStack for the point set, and line generation.

    @param hullStack
    The points of the convex hull to construct the line
    set from.

    @return a shared_ptr to a StandaloneHullState
    holding the captured snapshot.
 */
std::shared_ptr<HullState> GrahamScan::captureSnapShot(std::vector<QPoint> hullStack,
    const unsigned int& iteration) const {
  std::vector<QLine> lSnap;

  // Reserve memory
  lSnap.reserve(hullStack.size() - 1);

  // Create the lines based on the hullStack
  for (unsigned int k = 0; k < hullStack.size() - 1; ++k) {
    lSnap.emplace_back(hullStack[k], hullStack[k + 1]);
  }

  // If the iteration is not the last, also add all
  // points not yet checked to be displayed
  if (iteration != pts.size() - 1) {
    for (unsigned int k = iteration; k < pts.size(); ++k) {
      hullStack.push_back(pts[k]);
    }
  }

  return std::shared_ptr<HullState>(new StandaloneHullState(hullStack, lSnap));
}

/** Find the smallest y point.

    Finds the smallest y point in the object's point set
    such that the discovered y point is both the lowest
    in y value, and the greatest in x value of all points.

    The complexity of this function is O(N) because it must look
    at each point to check the y value.

    @returns a reference to the QPoint with the smallest
    y value, and greatest x value.
 */
QPoint& GrahamScan::findSmallestYPoint() {
  //Initialized the values for the for loop
  int minY = pts[0].y();
  int minIndex = 0;

  // Find the smallest y point, with the greatest x value
  for (unsigned int i = 1; i < pts.size(); ++i) {
    int y = pts[i].y();
    if ((y < minY || (minY == y && pts[i].x() >= pts[minIndex].x()))) {
      minY = pts[i].y();
      minIndex = i;
    }
  }

  return pts[minIndex];
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
int GrahamScan::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
  int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
            (p2.x() - p1.x()) * (p3.y() - p2.y());

  if (val == 0) return 0;   // colinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}

/** Calculate the square distance between two points.

    Calculates the square distance between two points.

    Complexity is O(1).

    @param p1
    The first point.

    @param p2
    The second point.

    @returns the calculated square distance.
 */
int GrahamScan::sqrDist(const QPoint& p1, const QPoint& p2) const {
  return (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());
}

/** Compare two QPoints.

    Compares two QPoints using their cross product
    with the lowest y point to determine which
    point has a lower angle from the x-axis.

    If the cross product determines that there is a counterclock
    wise movement, then p1 is considered less than p2.

    @param p1
    The first point to compare.

    @param p2
    The second point to compare.

    @return true if the points are counter clockerwise.
 */
bool GrahamScan::operator () (const QPoint& p1, const QPoint& p2) const {
  int o = ccw(pts[0], p1, p2);
  return o == 0 ? sqrDist(pts[0], p2) >= sqrDist(pts[0], p1) : o == 2;
}
