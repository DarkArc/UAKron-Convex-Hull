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

#include "RandomPointInput.hpp"

#include <chrono>
#include <random>

RandomPointInput::RandomPointInput(const unsigned int& m_pointCount, const unsigned int& m_maxPoint)
                      : m_pointCount(m_pointCount), m_maxPoint(m_maxPoint) { }

RandomPointInput::~RandomPointInput() { }

QString RandomPointInput::name() const {
  return "Random Point";
}

unsigned int RandomPointInput::pointCount() const {
  return m_pointCount;
}

void RandomPointInput::setPointCount(const unsigned int& m_pointCount) {
  this->m_pointCount = m_pointCount;
  emit pointCountChanged();
}

unsigned int RandomPointInput::maxPoint() const {
  return m_maxPoint;
}

void RandomPointInput::setMaxPoint(const unsigned int& m_maxPoint) {
  this->m_maxPoint = m_maxPoint;
  emit maxPointChanged();
}

std::vector<QPoint> RandomPointInput::getPoints() {

  std::vector<QPoint> points;

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::minstd_rand0 generator(seed);

  for (unsigned int i = 0; i < m_pointCount; ++i) {
    points.push_back(QPoint(generator() % m_maxPoint, generator() % m_maxPoint));
  }

  return points;
}
