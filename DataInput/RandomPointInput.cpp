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
