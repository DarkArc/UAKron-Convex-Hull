#ifndef HULLSTATE_HPP
#define HULLSTATE_HPP

#include <QPoint>
#include <QLine>

#include <vector>

class HullState {
  std::vector<QPoint> points;
  std::vector<QLine> lines;
public:
  HullState(const std::vector<QPoint>&, const std::vector<QLine>&);

  std::vector<QPoint> getPoints() const;
  std::vector<QLine> getLines() const;
};

#endif
