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

#ifndef HULLTIMELINE_HPP
#define HULLTIMELINE_HPP

#include <QPoint>

#include <vector>
#include <memory>

#include "HullState/HullState.hpp"

class HullTimeline {
  QPoint min;
  QPoint max;
  std::vector<std::shared_ptr<HullState>> events;
public:
  HullTimeline();
  HullTimeline(const std::vector<std::shared_ptr<HullState>>&);

  QPoint getMin() const;
  QPoint getMax() const;

  std::vector<std::shared_ptr<HullState>> getEvents() const;

  int getEventCount() const;
private:
  void setMinAndMax();
};
#endif
