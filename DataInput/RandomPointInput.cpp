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

/** Construct a new RandomPointInput object.

    Constructs a new RandomPointInput object with an initial
    point generation count, and an initial max value for
    point generations.
 */
RandomPointInput::RandomPointInput(const unsigned int& m_pointCount, const unsigned int& m_maxPoint)
                      : m_pointCount(m_pointCount), m_maxPoint(m_maxPoint) { }

/** Destruct the current RandomPointInput object.

    Destructs the current RandomPointInput object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
 RandomPointInput::~RandomPointInput() { }

/** Retrieve the name of this input provider.

    @returns the QString "Random Point".
 */
QString RandomPointInput::name() const {
  return "Random Point";
}

/** Retrieve the number of points to generate.

    Retrieves the number of points which
    will be generated upon an input request.

    @returns the number of points which will
    be generated.
 */
unsigned int RandomPointInput::pointCount() const {
  return m_pointCount;
}

/** Set the number of points to generate.

    Sets the number of points which
    will be generated upon an input request.

    Upon success a pointCountChanged(); signal
    will be emitted.
 */
void RandomPointInput::setPointCount(const unsigned int& m_pointCount) {
  this->m_pointCount = m_pointCount;
  emit pointCountChanged();
}

/** Retrieve the maximum point coordinate.

    Retrieves the maximum point coordinate which
    may be generated upon an input request. Such
    that any generated point has the bounds
    [0, maximum point) on both x & y.

    @return the maximum point coordinate.
 */
unsigned int RandomPointInput::maxPoint() const {
  return m_maxPoint;
}

/** Set the maximum point coordinate.

    Sets the maximum point coordinate which
    may be generated upon an input rquest.
    Such that any generated point has the bounds
    [0, maximum point) on both x & y.

    @params m_maxPoint
    The maximum point.
 */
void RandomPointInput::setMaxPoint(const unsigned int& m_maxPoint) {
  this->m_maxPoint = m_maxPoint;
  emit maxPointChanged();
}

/** Generate a collection of points.

    Generates a collection of points such that the
    number of points is limited to the object's
    maximum points value, and that all points
    are within the x & y bounds
    [0, maximum point coordinate).

    @returns the generated collection of points.
 */
std::vector<QPoint> RandomPointInput::getPoints() {
  std::vector<QPoint> points;

  // Initalize a random generator
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::minstd_rand0 generator(seed);

  // Create random m_pointCount random points within the bounds
  // of m_maxPoint
  for (unsigned int i = 0; i < m_pointCount; ++i) {
    points.push_back(QPoint(generator() % m_maxPoint, generator() % m_maxPoint));
  }
  return points;
}
