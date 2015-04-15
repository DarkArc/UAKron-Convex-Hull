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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>   // Hold the convex hull points
#include <algorithm>

#include "HullAlgorithm.hpp"

/* Global Variables */

  QPoint p0; // point with the smallest y-value
  std::vector<QPoint> points;
  std::vector<HullState> stages;
  std::stack<QPoint> s;

/* Functions for calculating Convex Hull by Graham Scan */
  QPoint& findSmallestYPoint(std::vector<QPoint>&);
  void swap(QPoint&,QPoint&);
  QPoint secondToTop(std::stack<QPoint>&);
  int ccw(QPoint, QPoint, QPoint);
  int sqrDist(QPoint const&, QPoint const&);
  int polarCompare(const void*, const void*);
  std::stack<QPoint> grahamScan(std::vector<QPoint>&);

/* NOT USED -- For custom mergeSort implementation */
  bool polarCompare(QPoint, QPoint);
  std::vector<QPoint> merge(std::vector<QPoint>, std::vector<QPoint>); // not used
  std::vector<QPoint> mergeSort(std::vector<QPoint>); // not used


class GrahamScan : public HullAlgorithm {
  public:
    GrahamScan()
    {
      for(int i = 0; i < 20; ++i)
      {
          int x = rand()% 50 + 1;
          int y = rand()% 50 + 1;

          points.push_back(QPoint(x, y));
      }
    }

  virtual HullTimeline getTimeline() {
    // Get the hull
    std::stack<QPoint> hull = grahamScan(points);
    std::vector<QPoint> hullPoints;

    // Convert the points into a vector
    while(!hull.empty())
    {
        hullPoints.push_back(hull.top());
        hull.pop();
    }

    // Generate the line stages
    for (unsigned int i = 0; i < points.size()-1; ++i) {
      std::vector<QLine> lines;
      if (i > 0) {
        lines = stages[i - 1].getLines();
        lines.push_back(QLine(hullPoints[i - 1], hullPoints[i]));
      }
      stages.push_back(HullState(points, lines));
    }

    return HullTimeline(stages);
  }
};

/* Function Definitions */

//===================================================================

/*
    Pre:  Vector of QPoints that contains the set of all the points.
    Post: Returns a reference to the point with the smallest Y-value

    Desc: The complexity of this function is O(N) because it must look
          at each point to check the Y value.
*/

QPoint &findSmallestYPoint(std::vector<QPoint>& points)
{
    //Initialized the values for the for loop
    int minY = points[0].y();
    int minIndex = 0;

    // Iterate over all the point to find the smallest y value
    for(unsigned int i = 1; i < points.size(); ++i)
    {
       int y = points[i].y();
       if((y < minY || (minY == y && points[i].x() < points[minIndex].x())))
       {
         minY = points[i].y();
         minIndex = i;
       }
    }
    
    return points[minIndex];
}

//===================================================================

/*
    Pre:  Two valid QPoints
    Post: Swaps the values

    Desc: Complexity is O(1)
*/
void swap(QPoint& p1, QPoint& p2)
{
    QPoint temp = p1;
    p1 = p2;
    p2 = temp;
}

//===================================================================

/*
    Pre:  A stack that contains at least two QPoints
    Post: Returns a copy of the second to the top QPoint in the stack.
          Does not change the contents of the stack.

    Desc: Complexity is O(1)
*/

QPoint secondToTop(std::stack<QPoint>& s)
{
    QPoint top = s.top();
    s.pop();
    QPoint secondToTop = s.top();
    s.push(top);
    return secondToTop;
}

//======================================================================

/*
    Pre:  
    Post: Returns 1 if points are clockwise, and 2 if counter-clockwise,
          and == 0 if collinear. 

    Desc: Complexity is O(1). Reference http://en.wikipedia.org/wiki/Graham_scan
          for psuedo code implementation.

          This function computes the z-coordinate of the cross product
*/

int ccw(QPoint p1, QPoint p2, QPoint p3)
{
    int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
              (p2.x() - p1.x()) * (p3.y() - p2.y());

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1 : 2; // clock or counterclock wise
}

//======================================================================

/*
    Pre: 
    Post: Returns the square of the distance between two points

    Desc: Complexity is O(1)

*/

int sqrDist(QPoint const& p1, QPoint const& p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y());
}

//======================================================================

/*
    Pre:  Two valid QPoints, and the pivot point (p0) must be defined.
    Post: 
         If colinear it returns true if the first point is closer to the
         pivot point; false otherwise.

         Returns true if polar angle of the first point is less than the
         polar angle of the second point.

     Desc: Complexity is O(1). This is used with the sort algorithm. This
     is being used for custom implementation of mergeSort.

*/

bool polarCompare(QPoint a, QPoint b)
{
    int order = ccw(p0, a, b);
    if(order == 0) // collinear, return true if a is the closer of the two points
        return (sqrDist(p0, a) < sqrDist(p0, b));
    return (order == 2);
}
//======================================================================

/*
    Pre:
    Post: Returns -1 if the first point's polar angle is less than the
          polar angle of the second point. Returns 1 otherwise.
*/
int polarCompare(const void *vp1, const void *vp2)
{
   QPoint *p1 = (QPoint *)vp1;
   QPoint *p2 = (QPoint *)vp2;

   // Find orientation
   int o = ccw(p0, *p1, *p2);
   if (o == 0)
     return (sqrDist(p0, *p2) >= sqrDist(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}
//======================================================================
std::vector<QPoint> merge(std::vector<QPoint> left, std::vector<QPoint> right)
{
    std::vector<QPoint> result;
    while(left.size() > 0 || right.size() > 0)
    {
        if(left.size() > 0 && right.size() > 0)
        {
            if(polarCompare(left.front(), right.front()))
            {
                result.push_back(left.front());
                left.erase(left.begin());
            }
            else
            {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }
        else if (left.size() > 0)
        {
            for(unsigned int i = 0; i < left.size(); ++i)
                result.push_back(left[i]);
            break;
        }
        else if(right.size() > 0)
        {
            for(unsigned int i = 0; i < right.size(); ++i)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
}

std::vector<QPoint> mergeSort(std::vector<QPoint> points)
{
    if(points.size() <= 1)
        return points;

    std::vector<QPoint> left, right, result;
    int middle = (points.size() + 1)/2;

    for(unsigned int i = 0; i < middle; ++i)
    {
        left.push_back(points[i]);
    }

    for(unsigned int i = middle; i < points.size(); ++i)
    {
        right.push_back(points[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left, right);

    return result;
}

std::stack<QPoint> grahamScan(std::vector<QPoint>& points)
{
    // Get the hull
    swap(points[0], findSmallestYPoint(points));
    p0 = points[0];
    qsort(&points[1], points.size()-1, sizeof(QPoint), polarCompare);
    std::stack<QPoint> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for(int i = 3; i < points.size(); ++i)
    {
        while(ccw(secondToTop(hull), hull.top(), points[i]) != 2)
        {
            hull.pop();
        }
        hull.push(points[i]);
    }

    return hull;
}

#endif
