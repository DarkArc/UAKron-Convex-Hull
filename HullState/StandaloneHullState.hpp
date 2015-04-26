#ifndef STANDALONEHULLSTATE_HPP
#define STANDALONEHULLSTATE_HPP

#include "HullState.hpp"

class StandaloneHullState : public HullState {
  std::vector<QPoint> points;
  std::vector<QLine> lines;
public:
  StandaloneHullState(const std::vector<QPoint>&, const std::vector<QLine>&);
  virtual ~StandaloneHullState();

  virtual std::vector<QPoint> getPoints() const;
  virtual std::vector<QLine> getLines() const;
};

#endif
