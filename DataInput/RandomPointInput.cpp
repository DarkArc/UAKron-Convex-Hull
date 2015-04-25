#include "RandomPointInput.hpp"

#include <chrono>
#include <random>

RandomPointInput::RandomPointInput(unsigned int pointCount, bool circle)
                      : pointCount(pointCount), circle(circle) { }

RandomPointInput::~RandomPointInput() { }

QString RandomPointInput::name() const {
  return "Random Point";
}

std::vector<QPoint> RandomPointInput::getPoints() {

  std::vector<QPoint> points;

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::minstd_rand0 generator (seed);

  for (unsigned int i = 0; i < pointCount; ++i) {
    points.push_back(QPoint(generator() % 1000, generator() % 1000));
  }

  return points;
}
