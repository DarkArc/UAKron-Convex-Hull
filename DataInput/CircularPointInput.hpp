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

#ifndef CIRCULARPOINTINPUT_HPP
#define CIRCULARPOINTINPUT_HPP

#include <QObject>

#include "../DataInput.hpp"

class CircularPointInput : public QObject, public DataInput {
  Q_OBJECT

  Q_PROPERTY(int pointCount READ pointCount WRITE setPointCount NOTIFY pointCountChanged);
  Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged);

  unsigned int m_pointCount;
  unsigned int m_radius;
public:
  CircularPointInput(const unsigned int&, const unsigned int&);
  virtual ~CircularPointInput();

  virtual QString name() const;

  unsigned int pointCount() const;
  void setPointCount(const unsigned int&);

  unsigned int radius() const;
  void setRadius(const unsigned int&);

  virtual std::vector<QPoint> getPoints();

signals:
  void pointCountChanged() const;
  void radiusChanged() const;
};

#endif
