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

#include "CircularPointInput.hpp"

CircularPointInput::CircularPointInput(const unsigned int& m_pointCount, const unsigned int& m_radius)
                                     : m_pointCount(m_pointCount), m_radius(m_radius) { }

CircularPointInput::~CircularPointInput() { }

QString CircularPointInput::name() const {
  return "Circular Point";
}

unsigned int CircularPointInput::pointCount() const {
  return m_pointCount;
}

void CircularPointInput::setPointCount(const unsigned int& m_pointCount) {
  this->m_pointCount = m_pointCount;
  emit pointCountChanged();
}

unsigned int CircularPointInput::radius() const {
  return m_radius;
}

void CircularPointInput::setRadius(const unsigned int& m_radius) {
  this->m_radius = m_radius;
  emit radiusChanged();
}

std::vector<QPoint> CircularPointInput::getPoints() {

  static const double PI = 3.14159265358979323846264338327950288;

  double interval = (2 * PI) / m_pointCount;
  double curAngle = 0;

  std::vector<QPoint> points;

  for (unsigned int i = 0; i < m_pointCount; ++i) {
    points.push_back(
      QPoint(
        sin(curAngle) * m_radius,
        cos(curAngle) * m_radius
      )
    );
    curAngle += interval;
  }

  return points;
}
