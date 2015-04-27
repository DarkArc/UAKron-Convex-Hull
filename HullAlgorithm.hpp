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

#ifndef HULLALGORITHM_HPP
#define HULLALGORITHM_HPP

#include <chrono>

#include <QString>

#include "HullTimeline.hpp"

class HullAlgorithm {
  double elapsedTime;
  std::chrono::time_point<std::chrono::high_resolution_clock> last;
public:
  virtual ~HullAlgorithm();

  virtual QString name() const = 0;

  double getTime() const;
  void timeTrackInit();
  void timeTrackUpdate();
  void timeTrackRecord();

  virtual HullTimeline getTimeline(const std::vector<QPoint>&) = 0;
};
#endif
