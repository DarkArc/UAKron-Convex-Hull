#include "HullSolver.hpp"

#include <QVariant>
#include <QDebug>
#include <QMetaProperty>

HullSolver::HullSolver(QObject* algorithmBox, std::unordered_map<std::string, HullAlgorithm*>& algorithms,
                       QObject* inputBox, std::unordered_map<std::string, DataInput*>& inputs
                     ) : algorithmBox(algorithmBox), inputBox(inputBox), algorithms(&algorithms), inputs(&inputs) { }

void HullSolver::calculate() {
  if (!inputPts.empty()) {
    if (!timeline.hasVal() || algorithmDiff) {
      if (algorithmDiff) {
        std::string str = algorithmBox->property("currentText").toString().toStdString();
        auto entry = algorithms->find(str);
        if (entry != algorithms->end()) {
          algorithm = entry->second;
          algorithmDiff = false;
          emit algorithmChanged(QString(entry->first.c_str()));
        } else {
          emit error("Invalid algorithm specified!");
        }
      }
      timeline.setVal(algorithm->getTimeline(inputPts));
    }
    emit solutionFound(timeline.getVal());
  } else {
    emit error("Empty data set!");
  }
}

void HullSolver::repollData() {
  if (inputDiff) {
    auto entry = inputs->find("Random Input");
    if (entry != inputs->end()) {
      input = entry->second;
      inputDiff = false;
      emit inputChanged(QString(entry->first.c_str()));
    } else {
      emit error("Invalid input specified!");
    }
  }
  inputPts = input->getPoints();
  timeline.clearVal();
}

void HullSolver::repollAlgorithm() {
  algorithmDiff = true;
}

void HullSolver::repollInput() {
  inputDiff = true;
}
