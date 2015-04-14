/*
     FileName: DummyAlgorithm.hpp

     Reference:
	http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/	
     
*/


#ifndef DUMMYALGORITHM_HPP
#define DUMMYALGORITHM_HPP

#include <chrono>
#include <random>

/* Included by Emil */
#include <stack>

#include "HullAlgorithm.hpp"

class DummyAlgorithm : public HullAlgorithm {
  public:
    /* Data Members */

      // All the points in the hull
      std::vector<QPoint> points;

      // Tells QT in what order to render the points
      std::vector<HullState> stages;

      // Holds all the points on the Convex hull; Subset of points
      std::stack<QPoint> Stack;

      // The point with the smallest y-value; will be used for sorting
      QPoint p0;

    //=====================================================================
    /* Constructor */
    DummyAlgorithm()
    {
      /* Initialized the points */
      points.push_back(QPoint(5,5));	// We can probably overload an << operator
      points.push_back(QPoint(3,4));	// to stream in from a file to make this
      points.push_back(QPoint(2,2));	// easier. Just a thought though.
      points.push_back(QPoint(4,4));
      points.push_back(QPoint(4,2));
      points.push_back(QPoint(1,2));
      points.push_back(QPoint(3,7));
      points.push_back(QPoint(3,1));
      /* End initialization of points */   
    }


    /* Member Functions */
      QPoint& findSmallestYPoint(std::vector<QPoint>&);
      void swap(QPoint&,QPoint&);
      

  // virtual function to tell QT how to render the convex hull
  virtual HullTimeline getTimeline() {

    swap(points[0], findSmallestYPoint(points));
    
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
QPoint& DummyAlgorithm::findSmallestYPoint(std::vector<QPoint>& points)
{
    //Initialized the values for the for loop
    int minY = points[0].y();
    int minIndex = 0;

    // Find the point with the smallest y value
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
void DummyAlgorithm::swap(QPoint& p1, QPoint& p2)
{
    QPoint temp = p1;
    p1 = p2;
    p2 = temp;
}

#endif
