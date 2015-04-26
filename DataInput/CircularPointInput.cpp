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
