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

/** Construct a new HullSolver object.

    Constructs a new HullSolver object which
    will have the provided algorithms
    and input providers availible.

    @param algorithms
    The algorithms which will be availible.

    @param inputs
    The inputs providers which will be availible.
 */
HullSolver::HullSolver(QMap<QString, HullAlgorithm*>& algorithms,
                       QMap<QString, DataInput*>& inputs
                     ) : algorithms(&algorithms), inputs(&inputs) { }

/** Calculates the hull.

    Given the current input collection, and the current
    algorithm, the HullSolver will first check to see
    if the HullTimeline has already been calculated
    for the current input collection, and algorithm.

    If either the current input collection, or the
    algorithm have changed since the previous calculation,
    or in the case that there is no previous calculation,
    the Hulltimeline will be calculated based on the
    input collection, and current algroithm.

    Once the HullTimeline has been obtained
    either by the cache of the previous value, or
    by a recalculation, the HullSolver will emit
    the signals:
    - solutionFound(const HullTimeline&);
    - solutionFound(
        const QString&,
        const int&,
        const int&,
        const double&
      );
    - origPointDiscovered(const int& x, const int& y);
    - hullPointFound(const int& x, const int& y);

    In the case of an error, an error(const QString&)
    signal shall be emitted.
 */
void HullSolver::calculate() {
  // Check to see if we have input points
  if (!inputPts.empty()) {
    // Check to see if there is a cached value
    if (!timeline.hasVal()) {
      // No cached value, request the algorithm calculate
      // the hull
      timeline.setVal(m_algorithm->getTimeline(inputPts));

      // Collect information for stats
      auto events = timeline.getVal().getEvents();
      auto points = events[0]->getPoints();
      auto hullPoints = events[events.size() - 1]->getPoints();

      // Release the new HullTimeline to all interested
      emit solutionFound(timeline.getVal());

      // Release the algorithm stats
      emit solutionFound(
        m_algorithm->name(),
        points.size(),
        hullPoints.size(),
        m_algorithm->getTime()
      );

      // Release a list of the original points
      // one-by-one
      for (auto& point :points) {
        emit origPointDiscovered(point.x(), point.y());
      }

      // Release a list of the points on the hull
      // one-by-one
      for (auto& point :hullPoints) {
        emit hullPointFound(point.x(), point.y());
      }
    } else {
      // Release the cached HullTimeline to all interested
      emit solutionFound(timeline.getVal());
    }
  } else {
    emit error("Empty data set!");
  }
}

/** Repoll the input provider for new data.

    Repolls the input provider replacing the
    previously held input collection with the
    new input collection as provided by the
    input provider. If there is no valid
    input provider, an error(const QString&)
    signal shall be emitted.
 */
void HullSolver::repollData() {
  if (m_input == nullptr) {
    emit error("No input system!");
    return;
  }

  // Overwrite the existing points
  inputPts = m_input->getPoints();
  // Remove the invalidated cached hull solution
  timeline.clearVal();
}

/** Get the algrithm's name.

    @returns the current algorithm's name, or
    the string "null" if no algorithm is present.
 */
QString HullSolver::algorithm() const {
  return m_algorithm == nullptr ? "null" : m_algorithm->name();
}

/** Request a new algorithm.

    Request the algorithm with the specified name
    be used. This algorithm must be provided
    in the QMap which the HullSolver was
    originally constructd with.

    If the algorithm specified is different from the
    one currently in use, an algorithmChanged(const QString&);
    signal will be emitted.

    If the algroithm was not found, an error(const QString&);
    signal will be emitted.

    @param str
    The name of the algorithm to use.
 */
void HullSolver::setAlgorithm(const QString& str) {
  // Search for the algorithm by name
  auto entry = algorithms->find(str);
  if (entry != algorithms->end()) {
    // Check to see if the found agorithm differs
    // from the one currently in use
    if (entry.value() != m_algorithm) {
      // Update the current algorithm
      m_algorithm = entry.value();
      // Remove the invalidated cached hull solution
      timeline.clearVal();
      emit algorithmChanged(entry.key());
    }
  } else {
    emit error("Invalid algorithm specified!");
  }
}

/** Get the input provider's name.

    @returns the current input provider's name, or
    the string "null" if no input provider is present.
 */
QString HullSolver::input() const {
  return m_input == nullptr ? "null" : m_input->name();
}

/** Request a new input provider.

    Request the input provider with the specified name
    be used. This input provider must be provided in
    the QMap which the HullSolver was originally
    constructd with.

    If the input provider specified is different from the
    one currently in use, an inputChanged(const QString&);
    signal will be emitted.

    If the input provider was not found, an
    error(const QString&); signal will be emitted.

    @param str
    The name of the input provider to use.
 */
void HullSolver::setInput(const QString& str) {
  // Search for the input provider by name
  auto entry = inputs->find(str);
  if (entry != inputs->end()) {
    // Check to see if the found input provider
    // differs from the one currently in use
    if (entry.value() != m_input) {
      // Update the current input provider
      m_input = entry.value();
      // Remove invalidated previous points
      inputPts.clear();
      emit inputChanged(entry.key());
    }
  } else {
    emit error("Invalid input proivder specified!");
  }
}
