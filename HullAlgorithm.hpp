#ifndef HULLALGORITHM_HPP
#define HULLALGORITHM_HPP

#include <chrono>

#include <QString>

#include "HullTimeline.hpp"

class HullAlgorithm {
  int elapsedTime;
  std::chrono::time_point<std::chrono::system_clock> last;
public:
  virtual ~HullAlgorithm();

  virtual QString name() const = 0;

  int getTime() const;
  void timeTrackInit();
  void timeTrackUpdate();
  void timeTrackRecord();

  virtual HullTimeline getTimeline(const std::vector<QPoint>&) = 0;
};
#endif
