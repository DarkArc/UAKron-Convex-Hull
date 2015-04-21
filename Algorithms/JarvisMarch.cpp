#include "JarvisMarch.hpp"
#include <QLine>

#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

HullTimeline JarvisMarch::getTimeline(const std::vector<QPoint>& nPts) {

    // Initialize the vector to hold the points
    std::vector<QPoint> hull;
    stages = std::vector<HullState>();

    // Must be at least 3 points
    if(nPts.size() < 3)
        return HullTimeline(stages);

    // Find left most point
    int left = 0;
    for(unsigned int i = 0; i < nPts.size(); ++i)
    {
        if(nPts[i].x() < nPts[left].x())
            left = i;
    }

    int p = left, q;
    do
    {
        q = (p+1)%nPts.size();
        for(unsigned int i = 0; i < nPts.size(); ++i)
            if(ccw(nPts[p], nPts[i], nPts[q]) == 2)
                q = i;

        hull.push_back(nPts[q]);
        p = q;
    }while(p != left);

    // Add line drawing here...

    // An issue with the drawing is that the left
    // most point is inserted at the end of the hull vector
    // the hull[0] is actually the second point on the convex hull
    // found by the jarvis march. Not sure what to do? Or if it
    // matters?

}

int JarvisMarch::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
    int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
              (p2.x() - p1.x()) * (p3.y() - p2.y());

    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}
