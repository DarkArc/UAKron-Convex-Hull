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

#ifndef DEPENDANTHULLSTATE_HPP
#define DEPENDANTHULLSTATE_HPP

#include <memory>

#include "HullState.hpp"

class DependantHullState : public HullState {
  const std::shared_ptr<HullState> parent;
  std::vector<int> remPoints;
  std::vector<QPoint> addPoints;
  std::vector<int> remLines;
  std::vector<QLine> addLines;
public:
  DependantHullState(
    const std::shared_ptr<HullState>,
    const std::vector<int>&,
    const std::vector<QPoint>&,
    const std::vector<int>&,
    const std::vector<QLine>&
  );
  virtual ~DependantHullState();

  virtual std::vector<QPoint> getPoints() const;
  virtual std::vector<QLine> getLines() const;
};

#endif
