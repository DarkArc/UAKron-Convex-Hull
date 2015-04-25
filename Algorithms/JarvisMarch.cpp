#include "JarvisMarch.hpp"

#include <QLine>

JarvisMarch::JarvisMarch() { }

JarvisMarch::~JarvisMarch() { }

QString JarvisMarch::name() const {
  return "Jarvis March";
}

HullTimeline JarvisMarch::getTimeline(const std::vector<QPoint>& nPts) {
  // Update internal class level variables
  pts = nPts;
  stages = std::vector<HullState>();
  timeTrackInit();

  stages.push_back(HullState(pts, std::vector<QLine>()));

  timeTrackUpdate();
  // Must be at least 3 points
  if (nPts.size() < 3) {
    return HullTimeline(stages);
  }

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
    for (unsigned int i = 0; i < nPts.size(); ++i) {
      if (ccw(nPts[p], nPts[i], nPts[q]) == 1) {
        q = i;
      }
      timeTrackRecord();
      stages.push_back(captureSnapshot(hull, nPts[i]));
      timeTrackUpdate();
    }

    p = q;
    if (p == left) {
      break;
    }

    hull.push_back(nPts[q]);
    timeTrackRecord();
    stages.push_back(captureSnapshot(hull));
    timeTrackUpdate();
  }

  // Finalize the hull by adding the connecting snapshot
  HullState last = *stages.rbegin();
  auto finalLines = last.getLines();
  finalLines.erase(finalLines.end() - 1);

  finalLines.push_back(QLine(*hull.begin(), *hull.rbegin()));

  stages.push_back(HullState(hull, finalLines));

  return HullTimeline(stages);
}

HullState JarvisMarch::captureSnapshot(const std::vector<QPoint>& hullPts) const {

  std::vector<QLine> lSnap;

  for (unsigned int k = 0; k < hullPts.size() - 1; ++k) {
    lSnap.push_back(QLine(hullPts[k], hullPts[k + 1]));
  }

  return HullState(pts, lSnap);
}

HullState JarvisMarch::captureSnapshot(std::vector<QPoint> hullPts, const QPoint& testPt) const {
  hullPts.push_back(testPt);
  return captureSnapshot(hullPts);
}

int JarvisMarch::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
  int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
            (p2.x() - p1.x()) * (p3.y() - p2.y());

  if (val == 0) return 0;  // colinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}
