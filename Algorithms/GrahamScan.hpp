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

/*
  FileName: GrahamScan.hpp

  References:
    http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
    http://stackoverflow.com/questions/16509100/sorting-points-by-their-polar-angle-java
    http://en.wikipedia.org/wiki/Graham_scan
    http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    http://www.bogotobogo.com/Algorithms/mergesort.php
*/

#ifndef GrahamScan_HPP
#define GrahamScan_HPP

#include <QPoint>

#include <vector>

#include "../HullState/HullState.hpp"
#include "../HullAlgorithm.hpp"

class GrahamScan : public HullAlgorithm {
  std::vector<QPoint> pts;
  std::vector<std::shared_ptr<HullState>> stages;
public:
  GrahamScan();
  virtual ~GrahamScan();

  virtual QString name() const;
  virtual HullTimeline getTimeline(const std::vector<QPoint>&);
private:
  std::shared_ptr<HullState> captureSnapShot(std::vector<QPoint>, const unsigned int&) const;

  QPoint& findSmallestYPoint();

  int ccw(const QPoint&, const QPoint&, const QPoint&) const;
  int sqrDist(const QPoint&, const QPoint&) const;
public:
  bool operator () (const QPoint&, const QPoint&) const;
};

#endif
