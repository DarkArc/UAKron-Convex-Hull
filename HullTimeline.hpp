#ifndef HULLTIMELINE_HPP
#define HULLTIMELINE_HPP

#include <QPoint>

#include <vector>

#include "HullState.hpp"

class HullTimeline {
  std::vector<HullState> events;
  QPoint max;
public:
  HullTimeline();
  HullTimeline(const std::vector<HullState>&);

  QPoint getMax() const;

  std::vector<HullState> getEvents() const;

  int getEventCount() const;
};
#endif
