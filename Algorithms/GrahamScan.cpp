#include "GrahamScan.hpp"

#include <QLine>
#include <QDebug>

#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

#include "../HullState/StandaloneHullState.hpp"

GrahamScan::GrahamScan() { }

GrahamScan::~GrahamScan() { }

QString GrahamScan::name() const {
  return "Graham Scan";
}

//======================================================================
/*
    Pre:
    Post: Returns a stack of all the pts on the convex hull

    Desc: Complexity is:
          Find smallest Y value = O(n)
          Sort pts = O(nlog(n))
          Find hull = O(n)

    The full relation is: nlog(n) + 2n. Dropping the linear factor we get
    O(nlog(n)) complexity for the full algorithm.

*/
HullTimeline GrahamScan::getTimeline(const std::vector<QPoint>& nPts) {
  // Update internal class level variables
  pts = nPts;
  stages = std::vector<std::shared_ptr<HullState>>();
  timeTrackInit();

  stages.emplace_back(new StandaloneHullState(nPts, std::vector<QLine>()));

  timeTrackUpdate();

  // Make the initial point the lowest Y
  std::swap(pts[0], findSmallestYPoint(pts));

  // Sort the points
  std::stable_sort(pts.begin() + 1, pts.end(), *this);

  timeTrackRecord();

  // Create the hull's stack
  std::stack<QPoint> hullStack;
  for (unsigned int i = 0; i < 3; ++ i) {
    hullStack.push(pts[i]);
    timeTrackRecord();
    stages.push_back(captureSnapShot(hullStack, i));
    timeTrackUpdate();
  }

  for (unsigned int i = 3; i < pts.size(); ++i) {
    while (hullStack.size() > 1 && ccw(secondToTop(hullStack), hullStack.top(), pts[i]) != 2) {
      hullStack.pop();
      timeTrackRecord();
      stages.push_back(captureSnapShot(hullStack, i));
      timeTrackUpdate();
    }
    hullStack.push(pts[i]);
    timeTrackRecord();
    stages.push_back(captureSnapShot(hullStack, i));
    timeTrackUpdate();
  }

  // Finalize the hull by adding the connecting snapshot
  std::shared_ptr<HullState> last = *stages.rbegin();
  auto finalPoints = last->getPoints();
  auto finalLines = last->getLines();

  finalLines.emplace_back(*finalPoints.begin(), *finalPoints.rbegin());

  stages.emplace_back(new StandaloneHullState(finalPoints, finalLines));

  return HullTimeline(stages);
}

std::shared_ptr<HullState> GrahamScan::captureSnapShot(std::stack<QPoint> hullStack,
    const unsigned int& iteration) const {

  std::vector<QPoint> pSnap;
  std::vector<QLine> lSnap;

  // Reserve memory
  pSnap.reserve(hullStack.size());
  lSnap.reserve(hullStack.size() - 1);

  while (!hullStack.empty()) {
    pSnap.push_back(hullStack.top());
    hullStack.pop();
  }

  for (unsigned int k = 0; k < pSnap.size() - 1; ++k) {
    lSnap.emplace_back(pSnap[k], pSnap[k + 1]);
  }

  if (iteration != pts.size() - 1) {
    for (unsigned int k = iteration; k < pts.size(); ++k) {
      pSnap.push_back(pts[k]);
    }
  }

  return std::shared_ptr<HullState>(new StandaloneHullState(pSnap, lSnap));
}

/* Function Definitions */

//===================================================================

/*
    Pre:  Vector of QPoints that contains the set of all the pts.
    Post: Returns a reference to the point with the smallest Y-value

    Desc: The complexity of this function is O(N) because it must look
          at each point to check the Y value.
*/

QPoint& GrahamScan::findSmallestYPoint(std::vector<QPoint>& pts) const {
    //Initialized the values for the for loop
    int minY = pts[0].y();
    int minIndex = 0;

    // Iterate over all the point to find the smallest y value
    for (unsigned int i = 1; i < pts.size(); ++i) {
       int y = pts[i].y();
       if ((y < minY || (minY == y && pts[i].x() >= pts[minIndex].x()))) {
         minY = pts[i].y();
         minIndex = i;
       }
    }

    return pts[minIndex];
}

//===================================================================

/*
    Pre:  A stack that contains at least two QPoints
    Post: Returns a copy of the second to the top QPoint in the stack.
          Does not change the contents of the stack.

    Desc: Complexity is O(1)
*/

QPoint GrahamScan::secondToTop(std::stack<QPoint> s) const {
    s.pop();
    return s.top();
}

//======================================================================

/*
    Pre:
    Post: Returns 1 if pts are clockwise, and 2 if counter-clockwise,
          and == 0 if collinear.

    Desc: Complexity is O(1). Reference http://en.wikipedia.org/wiki/Graham_scan
          for psuedo code implementation.

          This function computes the z-coordinate of the cross product
*/

int GrahamScan::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
    int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
              (p2.x() - p1.x()) * (p3.y() - p2.y());

    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

//======================================================================

/*
    Pre:
    Post: Returns the square of the distance between two pts

    Desc: Complexity is O(1)

*/
int GrahamScan::sqrDist(const QPoint& p1, const QPoint& p2) const {
    return (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());
}

//======================================================================

/*
    Pre:
    Post: Returns -1 if the first point's polar angle is less than the
          polar angle of the second point. Returns 1 otherwise.
*/
bool GrahamScan::operator () (const QPoint& p1, const QPoint& p2) const {
   // Find orientation
   int o = ccw(pts[0], p1, p2);
   if (o == 0) {
     return sqrDist(pts[0], p2) >= sqrDist(pts[0], p1);
   }

   return o == 2;
}
