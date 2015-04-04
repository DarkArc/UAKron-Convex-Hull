#ifndef DUMMYALGORITHM_HPP
#define DUMMYALGORITHM_HPP

#include "HullAlgorithm.hpp"

class DummyAlgorithm : public HullAlgorithm {

  virtual HullTimeline getTimeline() {
    QPoint p1(10, 20);
    QPoint p2(10, 20);
    QPoint p3(30, 40);
    QPoint p4(12, 344);

    std::vector<QPoint> points({p1, p2, p3, p4});

    QLine l1(p1, p2);
    QLine l2(p2, p3);
    QLine l3(p3, p4);

    std::vector<QLine> pSet1{l1};
    std::vector<QLine> pSet2{l1, l2};
    std::vector<QLine> pSet3{l2, l3};

    HullState s1(points, pSet1);
    HullState s2(points, pSet2);
    HullState s3(points, pSet3);

    std::vector<HullState> stages{s1, s2, s3};
    return HullTimeline(stages);
  }
};
#endif
