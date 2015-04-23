#ifndef HULLSOLVER_HPP
#define HULLSOLVER_HPP

#include <QObject>
#include <QString>

#include <string>
#include <vector>
#include <unordered_map>

#include "HullAlgorithm.hpp"
#include "DataInput.hpp"
#include "HullTimeline.hpp"
#include "Util/Optional.hpp"

class HullSolver : public QObject {
  Q_OBJECT

  QObject* algorithmBox;
  QObject* inputBox;

  std::unordered_map<std::string, HullAlgorithm*>* algorithms;
  std::unordered_map<std::string, DataInput*>* inputs;

  HullAlgorithm* algorithm = nullptr;
  DataInput* input = nullptr;

  bool algorithmDiff = true;
  bool inputDiff = true;

  std::vector<QPoint> inputPts;
  Optional<HullTimeline> timeline;
public:
  HullSolver(QObject*, std::unordered_map<std::string, HullAlgorithm*>&, QObject*, std::unordered_map<std::string, DataInput*>&);

public slots:
  void calculate();
  void repollData();
  void repollAlgorithm();
  void repollInput();

signals:
  void error(const QString&) const;
  void solutionFound(const HullTimeline&) const;
  void algorithmChanged(const QString&) const;
  void inputChanged(const QString&) const;
};

#endif
