#include "HullSolver.hpp"

HullSolver::HullSolver(HullAlgorithm& algorithm, DataInput& input)
  : algorithm(&algorithm), input(&input) { }

void HullSolver::calculate() {
  if (timeline.hasVal()) {
    emit solutionFound(timeline.getVal());
  } else {
    emit error("Empty data set!");
  }
}

void HullSolver::repollData() {
  timeline.setVal(algorithm->getTimeline(input->getPoints()));
}

void HullSolver::setAlgorithm(const QString& name) {
  // TODO add algorithm support
  repollData();
  emit algorithmChanged(name);
}
