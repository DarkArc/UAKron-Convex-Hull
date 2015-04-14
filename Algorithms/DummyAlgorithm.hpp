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
      points.push_back(QPoint(0,3));	// We can probably overload an << operator
      points.push_back(QPoint(1,1));	// to stream in from a file to make this
      points.push_back(QPoint(2,2));	// easier. Just a thought though.
      points.push_back(QPoint(4,4));
      points.push_back(QPoint(0,0));
      points.push_back(QPoint(1,2));
      points.push_back(QPoint(3,1));
      points.push_back(QPoint(3,3));
      /* End initialization of points */   
    }


    /* Member Functions */
      QPoint& findSmallestYPoint(std::vector<QPoint>&);
      

  // virtual function to tell QT how to render the convex hull
  virtual HullTimeline getTimeline() {

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


QPoint& findSmallesYPoint(std::vector<QPoint>& points)
{
    //Find the bottom most point
    

}
#endif
