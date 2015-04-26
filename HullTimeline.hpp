#ifndef HULLTIMELINE_HPP
#define HULLTIMELINE_HPP

#include <QPoint>

#include <vector>

#include "HullState/HullState.hpp"

class HullTimeline {
  QPoint min;
  QPoint max;
  std::vector<HullState*> events;
public:
  HullTimeline();
  HullTimeline(const std::vector<HullState*>&);

  HullTimeline(const HullTimeline&);
  HullTimeline(HullTimeline&&);

  ~HullTimeline();

  HullTimeline& operator = (const HullTimeline&);
  HullTimeline& operator = (HullTimeline&&);

  QPoint getMin() const;
  QPoint getMax() const;

  std::vector<HullState*> getEvents() const;

  int getEventCount() const;
private:
  void setMinAndMax();
};
#endif
