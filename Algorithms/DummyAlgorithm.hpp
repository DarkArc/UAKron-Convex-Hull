/*
     FileName: DummyAlgorithm.hpp

     References:
        http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
        http://stackoverflow.com/questions/16509100/sorting-points-by-their-polar-angle-java
        http://en.wikipedia.org/wiki/Graham_scan
        http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
*/


#ifndef DUMMYALGORITHM_HPP
#define DUMMYALGORITHM_HPP

#include <chrono>  // For testing
#include <random>  // For testing
#include <stack>   // Hold the convex hull points
#include <algorithm>

#include "HullAlgorithm.hpp"

/* Functions for calculating Convex Hull by Graham Scan */
  QPoint& findSmallestYPoint(std::vector<QPoint>&);
  void swap(QPoint&,QPoint&);
  QPoint secondToTop(std::stack<QPoint>&);
  int ccw(QPoint, QPoint, QPoint);
  int distance(QPoint const&, QPoint const&);
  int sqrDist(QPoint const&, QPoint const&);
  bool polarCompare(QPoint, QPoint);

  // Pivot point
  QPoint p0;

class DummyAlgorithm : public HullAlgorithm {
  public:
    /* Data Members */

      // All the points in the hull
      std::vector<QPoint> points;

      // Tells QT in what order to render the points
      std::vector<HullState> stages;

      // Holds all the points on the Convex hull; Subset of points
      std::stack<QPoint> s;

    //=====================================================================
    /* Constructor */
    DummyAlgorithm()
    {
      /* Initialized the points */
      points.push_back(QPoint(3,4));	// We can probably overload an << operator
      points.push_back(QPoint(5,5));	// to stream in from a file to make this
      points.push_back(QPoint(2,2));	// easier. Just a thought though.
      points.push_back(QPoint(4,4));
      points.push_back(QPoint(4,2));
      points.push_back(QPoint(1,2));
      points.push_back(QPoint(3,7));
      points.push_back(QPoint(3,1));
      /* End initialization of points */   
    }

  // virtual function to tell QT how to render the convex hull
  virtual HullTimeline getTimeline() {

    swap(points[0], findSmallestYPoint(points));;

    for (unsigned int i = 0; i < points.size(); ++i) {
      std::vector<QLine> lines;
      if (i > 0) {
        lines = stages[i - 1].getLines();
        lines.push_back(QLine(points[i - 1], points[i]));
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

QPoint& findSmallestYPoint(std::vector<QPoint>& points)
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

     Desc: Complexity is O(1). This is used with the sort algorithm.

*/

bool polarCompare(QPoint a, QPoint b)
{
    int order = ccw(p0, a, b);
    if(order == 0) // collinear, return true if a is the closer of the two points
        return (sqrDist(p0, a) < sqrDist(p0, b));
    return (order == 2);
}

//======================================================================


#endif
