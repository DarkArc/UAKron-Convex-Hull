#ifndef DUMMYALGORITHM_HPP
#define DUMMYALGORITHM_HPP

#include <chrono>
#include <random>

#include "HullAlgorithm.hpp"

class DummyAlgorithm : public HullAlgorithm {

  virtual HullTimeline getTimeline() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    std::vector<QPoint> points;

    for (int i = 0; i < 350; ++i) {
      points.push_back(QPoint(generator(), generator()));
    }

    std::vector<HullState> stages;
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
#endif
