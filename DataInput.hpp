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

#ifndef DATAINPUT_HPP
#define DATAINPUT_HPP

#include <QPoint>
#include <QString>

#include <vector>

class DataInput {
public:
  virtual ~DataInput() = 0;

  virtual QString name() const = 0;

  virtual std::vector<QPoint> getPoints() = 0;
};
#endif
