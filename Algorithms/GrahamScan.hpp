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

#include <stack>   // Hold the convex hull points
#include <vector>

#include "../HullState.hpp"
#include "../HullAlgorithm.hpp"

class GrahamScan : public HullAlgorithm {
  std::vector<QPoint> pts;
  std::vector<HullState> stages;
public:
  GrahamScan();
  virtual ~GrahamScan();

  virtual HullTimeline getTimeline(const std::vector<QPoint>&);
private:
  HullState captureSnapShot(std::stack<QPoint>, const unsigned int&) const;

  /* Internal functions for calculating Convex Hull by Graham Scan */
  QPoint& findSmallestYPoint(std::vector<QPoint>&) const;
  QPoint secondToTop(std::stack<QPoint>) const;

  int ccw(const QPoint&, const QPoint&, const QPoint&) const;
  int sqrDist(const QPoint&, const QPoint&) const;

public:
  /* Operator overloaded for sorting capability */
  bool operator () (const QPoint&, const QPoint&) const;
};

#endif
