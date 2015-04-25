#include "HullSolver.hpp"

#include <QVariant>
#include <QDebug>
#include <QMetaProperty>

HullSolver::HullSolver(QMap<QString, HullAlgorithm*>& algorithms,
                       QMap<QString, DataInput*>& inputs
                     ) : algorithms(&algorithms), inputs(&inputs) { }

void HullSolver::calculate() {
  if (!inputPts.empty()) {
    if (!timeline.hasVal()) {
      timeline.setVal(m_algorithm->getTimeline(inputPts));
    }
    emit solutionFound(timeline.getVal());
  } else {
    emit error("Empty data set!");
  }
}

void HullSolver::repollData() {
  if (m_input == nullptr) {
    emit error("No input system!");
    return;
  }

  inputPts = m_input->getPoints();
  timeline.clearVal();
}

QString HullSolver::algorithm() const {
  return m_algorithm == nullptr ? "null" : m_algorithm->name();
}

void HullSolver::setAlgorithm(const QString& str) {
  auto entry = algorithms->find(str);
  if (entry != algorithms->end()) {
    m_algorithm = entry.value();
    timeline.clearVal();
    emit algorithmChanged(entry.key());
  } else {
    emit error("Invalid algorithm specified!");
  }
}

QString HullSolver::input() const {
  return m_input == nullptr ? "null" : m_input->name();
}

void HullSolver::setInput(const QString& str) {
  auto entry = inputs->find(str);
  if (entry != inputs->end()) {
    m_input = entry.value();
    emit inputChanged(entry.key());
  } else {
    emit error("Invalid input specified!");
  }
}
