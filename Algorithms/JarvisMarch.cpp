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
#include <QDebug>

#include "../HullState/DependantHullState.hpp"
#include "../HullState/StandaloneHullState.hpp"

JarvisMarch::JarvisMarch() { }

JarvisMarch::~JarvisMarch() { }

QString JarvisMarch::name() const {
  return "Jarvis March";
}

HullTimeline JarvisMarch::getTimeline(const std::vector<QPoint>& nPts) {
  // Update internal class level variables
  pts = nPts;
  stages = std::vector<std::shared_ptr<HullState>>();
  timeTrackInit();

  stages.emplace_back(new StandaloneHullState(pts, std::vector<QLine>()));

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
    auto lastClean = *stages.rbegin();
    for (unsigned int i = 0; i < nPts.size(); ++i) {
      if (ccw(nPts[p], nPts[i], nPts[q]) == 2) {
        q = i;
      }
      timeTrackRecord();
      stages.push_back(captureSnapshot(lastClean, hull, nPts[i]));
      timeTrackUpdate();
    }

    p = q;
    if (p == left) {
      break;
    }

    hull.push_back(nPts[q]);
    timeTrackRecord();
    stages.push_back(captureSnapshot(lastClean, hull, nPts[q]));
    timeTrackUpdate();
  }

  // Finalize the hull by adding the connecting snapshot
  std::shared_ptr<HullState> last = *stages.rbegin();
  auto finalLines = last->getLines();
  finalLines.pop_back();
  finalLines.emplace_back(*hull.begin(), *hull.rbegin());

  stages.emplace_back(new StandaloneHullState(hull, finalLines));

  return HullTimeline(stages);
}

std::shared_ptr<HullState> JarvisMarch::captureSnapshot(const std::vector<QPoint>& hullPts) const {

  std::vector<QLine> lSnap;

  // Reserve memory
  lSnap.reserve(hullPts.size() - 1);

  for (unsigned int k = 0; k < hullPts.size() - 1; ++k) {
    lSnap.emplace_back(hullPts[k], hullPts[k + 1]);
  }

  return std::shared_ptr<HullState>(new StandaloneHullState(pts, lSnap));
}

std::shared_ptr<HullState> JarvisMarch::captureSnapshot(std::shared_ptr<HullState> last, std::vector<QPoint> curHull, const QPoint& testPt) const {

  auto lastLines = last->getLines();

  if (lastLines.empty()) {
    curHull.push_back(testPt);
    return captureSnapshot(curHull);
  }

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

int JarvisMarch::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
  int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
            (p2.x() - p1.x()) * (p3.y() - p2.y());

  if (val == 0) return 0;  // colinear
  return (val > 0) ? 1 : 2; // clock or counterclock wise
}
