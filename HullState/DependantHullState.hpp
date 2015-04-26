#ifndef DEPENDANTHULLSTATE_HPP
#define DEPENDANTHULLSTATE_HPP

#include "HullState.hpp"

class DependantHullState : public HullState {
  const HullState* parent;
  std::vector<int> remPoints;
  std::vector<QPoint> addPoints;
  std::vector<int> remLines;
  std::vector<QLine> addLines;
public:
  DependantHullState(
    const HullState*,
    const std::vector<int>&,
    const std::vector<QPoint>&,
    const std::vector<int>&,
    const std::vector<QLine>&
  );
  virtual ~DependantHullState();

  virtual std::vector<QPoint> getPoints() const;
  virtual std::vector<QLine> getLines() const;
};

#endif
