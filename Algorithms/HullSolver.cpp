#include "HullSolver.hpp"

HullSolver::HullSolver(HullAlgorithm& algorithm) : algorithm(&algorithm) { }

void HullSolver::calculate() {
  emit solutionFound(algorithm->getTimeline());
}

void HullSolver::setAlgorithm(const QString& name) {
  // TODO add algorithm support
  emit algorithmChanged(name);
}
