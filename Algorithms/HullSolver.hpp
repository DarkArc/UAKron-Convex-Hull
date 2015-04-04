#ifndef HULLSOLVER_HPP
#define HULLSOLVER_HPP

#include <QObject>

#include "HullAlgorithm.hpp"
#include "../HullTimeline.hpp"

class HullSolver : public QObject {
  Q_OBJECT

  HullAlgorithm* algorithm;
public:
  HullSolver(HullAlgorithm&);

public slots:
  void calculate();
  void setAlgorithm(const QString&);

signals:
  void solutionFound(const HullTimeline&) const;
  void algorithmChanged(const QString&) const;
};

#endif
