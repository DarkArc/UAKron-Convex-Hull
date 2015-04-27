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

#ifndef HULLSOLVER_HPP
#define HULLSOLVER_HPP

#include <QMap>
#include <QObject>
#include <QString>

#include <vector>
#include <unordered_map>

#include "HullAlgorithm.hpp"
#include "DataInput.hpp"
#include "HullTimeline.hpp"
#include "Util/Optional.hpp"

class HullSolver : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged);
  Q_PROPERTY(QString input READ input WRITE setInput NOTIFY inputChanged);

  QMap<QString, HullAlgorithm*>* algorithms;
  QMap<QString, DataInput*>* inputs;

  HullAlgorithm* m_algorithm = nullptr;
  DataInput* m_input = nullptr;

  std::vector<QPoint> inputPts;
  Optional<HullTimeline> timeline;
public:
  HullSolver(QMap<QString, HullAlgorithm*>&, QMap<QString, DataInput*>&);

  QString algorithm() const;
  void setAlgorithm(const QString&);

  QString input() const;
  void setInput(const QString&);

public slots:
  void calculate();
  void repollData();

signals:
  void error(const QString&) const;

  void origPointDiscovered(const int& x, const int& y) const;
  void hullPointFound(const int& x, const int& y) const;

  void solutionFound(const HullTimeline&) const;
  void solutionFound(
    const QString& algorithm,
    const int& origPoints,
    const int& hullPoints,
    const double& time
  ) const;

  void algorithmChanged(const QString&) const;
  void inputChanged(const QString&) const;
};

#endif
