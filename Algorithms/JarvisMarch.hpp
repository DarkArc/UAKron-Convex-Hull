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

#ifndef JARVISMARCH
#define JARVISMARCH

#include <QPoint>

#include <vector>
#include <memory>

#include "../HullState/HullState.hpp"
#include "../HullAlgorithm.hpp"

class JarvisMarch : public HullAlgorithm {
  std::vector<QPoint> pts;
  std::vector<std::shared_ptr<HullState>> stages;
public:
  JarvisMarch();
  virtual ~JarvisMarch();

  virtual QString name() const;
  virtual HullTimeline getTimeline(const std::vector<QPoint>&);
private:
  std::shared_ptr<HullState> captureSnapshot(const std::vector<QPoint>&) const;
  std::shared_ptr<HullState> captureSnapshot(std::shared_ptr<HullState>, std::vector<QPoint>, const QPoint&) const;

  int ccw(const QPoint&, const QPoint&, const QPoint&) const;
};

#endif // JARVISMARCH
