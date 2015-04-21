#include "JarvisMarch.hpp"
#include <QLine>

#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

HullTimeline JarvisMarch::getTimeline(const std::vector<QPoint>& nPts) {
    // Update internal class level variables
    pts = nPts;
    stages = std::vector<HullState>();

    stages.push_back(HullState(nPts, std::vector<QLine>()));

    // Must be at least 3 points
    if(nPts.size() < 3)
        return HullTimeline(stages);

    //Find left most point
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

        pts.push_back(nPts[q]);
        p = q;
    }while(p != left);

}

int JarvisMarch::ccw(const QPoint& p1, const QPoint& p2, const QPoint& p3) const {
    int val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
              (p2.x() - p1.x()) * (p3.y() - p2.y());

    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}
