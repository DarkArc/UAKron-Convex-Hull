#ifndef HULLTIMELINE_HPP
#define HULLTIMELINE_HPP

#include <QPoint>

#include <vector>
#include <memory>

#include "HullState/HullState.hpp"

class HullTimeline {
  QPoint min;
  QPoint max;
  std::vector<std::shared_ptr<HullState>> events;
public:
  HullTimeline();
  HullTimeline(const std::vector<std::shared_ptr<HullState>>&);

  QPoint getMin() const;
  QPoint getMax() const;

  std::vector<std::shared_ptr<HullState>> getEvents() const;

  int getEventCount() const;
private:
  void setMinAndMax();
};
#endif
