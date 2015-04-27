// Copyright (C) 2015 Wyatt Childers & Emil Heineking
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
      auto events = timeline.getVal().getEvents();
      auto points = events[0]->getPoints();
      auto hullPoints = events[events.size() - 1]->getPoints();

      emit solutionFound(timeline.getVal());
      emit solutionFound(
        m_algorithm->name(),
        points.size(),
        hullPoints.size(),
        m_algorithm->getTime()
      );

      for (auto& point :points) {
        emit origPointDiscovered(point.x(), point.y());
      }
      for (auto& point :hullPoints) {
        emit hullPointFound(point.x(), point.y());
      }
    } else {
      emit solutionFound(timeline.getVal());
    }
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
    if (entry.value() != m_algorithm) {
      m_algorithm = entry.value();
      timeline.clearVal();
      emit algorithmChanged(entry.key());
    }
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
    if (entry.value() != m_input) {
      m_input = entry.value();
      inputPts.clear();
      emit inputChanged(entry.key());
    }
  } else {
    emit error("Invalid input specified!");
  }
}
