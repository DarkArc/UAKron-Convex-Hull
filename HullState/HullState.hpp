#ifndef HULLSTATE_HPP
#define HULLSTATE_HPP

#include <QPoint>
#include <QLine>

#include <vector>

class HullState {
public:
  virtual ~HullState();

  virtual std::vector<QPoint> getPoints() const = 0;
  virtual std::vector<QLine> getLines() const = 0;
};

#endif
