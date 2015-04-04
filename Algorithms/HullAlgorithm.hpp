#ifndef HULLALGORITHM_HPP
#define HULLALGORITHM_HPP

#include "../HullTimeline.hpp"

class HullAlgorithm {
public:
  virtual HullTimeline getTimeline() = 0;
};
#endif
