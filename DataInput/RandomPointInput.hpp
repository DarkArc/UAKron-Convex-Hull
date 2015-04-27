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

#ifndef RANDOMPOINTINPUT_HPP
#define RANDOMPOINTINPUT_HPP

#include <QObject>

#include "../DataInput.hpp"

class RandomPointInput : public QObject, public DataInput {
  Q_OBJECT

  Q_PROPERTY(unsigned int pointCount READ pointCount WRITE setPointCount NOTIFY pointCountChanged);
  Q_PROPERTY(unsigned int maxPoint READ maxPoint WRITE setMaxPoint NOTIFY maxPointChanged);

  unsigned int m_pointCount;
  unsigned int m_maxPoint;
public:
  RandomPointInput(const unsigned int&, const unsigned int&);
  virtual ~RandomPointInput();

  virtual QString name() const;

  unsigned int pointCount() const;
  void setPointCount(const unsigned int&);

  unsigned int maxPoint() const;
  void setMaxPoint(const unsigned int&);

  virtual std::vector<QPoint> getPoints();

signals:
  void pointCountChanged() const;
  void maxPointChanged() const;
};

#endif
