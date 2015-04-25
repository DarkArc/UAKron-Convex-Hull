#ifndef HULLALGORITHM_HPP
#define HULLALGORITHM_HPP

#include <QString>

#include "HullTimeline.hpp"

class HullAlgorithm {
public:
  virtual ~HullAlgorithm();

  virtual QString name() const = 0;

  virtual HullTimeline getTimeline(const std::vector<QPoint>&) = 0;
};
#endif
