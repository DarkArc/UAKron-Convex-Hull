#ifndef HULLALGORITHM_HPP
#define HULLALGORITHM_HPP

#include "HullTimeline.hpp"

class HullAlgorithm {
public:
  virtual ~HullAlgorithm();

  virtual HullTimeline getTimeline(const std::vector<QPoint>&) = 0;
};
#endif
