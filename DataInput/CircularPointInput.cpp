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

/** Construct a new CircularPointInput object.

    Constructs a new CircularPointInput object with an initial
    point generation count, and an initial radius for
    point generations.
 */
CircularPointInput::CircularPointInput(const unsigned int& m_pointCount, const unsigned int& m_radius)
                                     : m_pointCount(m_pointCount), m_radius(m_radius) { }

/** Destruct the current CircularPointInput object.

    Destructs the current CircularPointInput object.
    This destructor is manually defined due to
    the use of polymorphism with this class,
    and the need for a virtual destructor.
 */
CircularPointInput::~CircularPointInput() { }

/** Retrieve the name of this input provider.

    @returns the QString "Circular Point".
 */
QString CircularPointInput::name() const {
  return "Circular Point";
}

/** Retrieve the number of points to generate.

    Retrieves the number of points which
    will be generated upon an input request.

    @returns the number of points which will
    be generated.
 */
unsigned int CircularPointInput::pointCount() const {
  return m_pointCount;
}

/** Set the number of points to generate.

    Sets the number of points which
    will be generated upon an input request.

    Upon success a pointCountChanged(); signal
    will be emitted.
 */
void CircularPointInput::setPointCount(const unsigned int& m_pointCount) {
  this->m_pointCount = m_pointCount;
  emit pointCountChanged();
}

/** Retrieve the radius.

    Retrieves the radius so that all points can lie
    a designated distance from the origin.

    @return the radius.
 */
unsigned int CircularPointInput::radius() const {
  return m_radius;
}

/** Set the radius.

    Sets the radius so that all points will lie
    a designated distance from the origin.

    @param m_radius
    The radius to use.
 */
void CircularPointInput::setRadius(const unsigned int& m_radius) {
  this->m_radius = m_radius;
  emit radiusChanged();
}

/** Generate a collection of points.

    Generates a collection of points such that
    the number of points is limited to the object's
    maximum points value, and that all points lie
    a fixed distance from the origin of the circle.

    @returns the generated collection of points.
 */
std::vector<QPoint> CircularPointInput::getPoints() {
  // Establish a static constant for PI
  static const double PI = 3.14159265358979323846264338327950288;

  std::vector<QPoint> points;

  // Set the interval based on the number of points
  // which must be generated
  double interval = (2 * PI) / m_pointCount;
  double curAngle = 0;

  // Create m_pointCount points which lie fixed
  // intervals apart on the radius of the circle
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
