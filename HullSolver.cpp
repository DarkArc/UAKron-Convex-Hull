#include "HullSolver.hpp"

#include <QVariant>
#include <QDebug>
#include <QMetaProperty>

HullSolver::HullSolver(QObject* algorithmBox, std::unordered_map<std::string, HullAlgorithm*>& algorithms,
                       QObject* inputBox, std::unordered_map<std::string, DataInput*>& inputs
                     ) : algorithmBox(algorithmBox), inputBox(inputBox), algorithms(&algorithms), inputs(&inputs) { }

void HullSolver::calculate() {
  if (!inputPts.empty()) {
    if (!timeline.hasVal()) {
      timeline.setVal(algorithm->getTimeline(inputPts));
    }
    emit solutionFound(timeline.getVal());
  } else {
    emit error("Empty data set!");
  }
}

void HullSolver::repollData() {
  if (algorithm == nullptr) {
    repollAlgorithm();
  }

  if (input == nullptr) {
    repollInput();
  }

  inputPts = input->getPoints();
}

void HullSolver::repollAlgorithm() {
  qDebug() << "Polling";
  std::string str = algorithmBox->property("currentText").toString().toStdString();
  auto entry = algorithms->find(str);
  qDebug() << str.c_str();
  if (entry != algorithms->end()) {
    algorithm = entry->second;
    timeline.clearVal();
    emit algorithmChanged(QString(entry->first.c_str()));
  } else {
    emit error("Invalid algorithm specified!");
  }
}

void HullSolver::repollInput() {
  auto entry = inputs->find("Random Input");
  if (entry != inputs->end()) {
    input = entry->second;
    emit inputChanged(QString(entry->first.c_str()));
  } else {
    emit error("Invalid input specified!");
  }
}
