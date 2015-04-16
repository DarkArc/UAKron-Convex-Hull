#ifndef HULLSOLVER_HPP
#define HULLSOLVER_HPP

#include <QObject>

#include "HullAlgorithm.hpp"
#include "DataInput.hpp"
#include "HullTimeline.hpp"
#include "Util/Optional.hpp"

class HullSolver : public QObject {
  Q_OBJECT

  HullAlgorithm* algorithm;
  DataInput* input;

  Optional<HullTimeline> timeline;
public:
  HullSolver(HullAlgorithm&, DataInput&);

public slots:
  void calculate();
  void repollData();
  void setAlgorithm(const QString&);

signals:
  void error(const QString&) const;
  void solutionFound(const HullTimeline&) const;
  void algorithmChanged(const QString&) const;
};

#endif
