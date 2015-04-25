#include "HullAlgorithm.hpp"

HullAlgorithm::~HullAlgorithm() { }

int HullAlgorithm::getTime() const {
  return elapsedTime;
}

void HullAlgorithm::timeTrackInit() {
  elapsedTime = 0;
  last = std::chrono::system_clock::now();
}

void HullAlgorithm::timeTrackUpdate() {
  last = std::chrono::system_clock::now();
}

void HullAlgorithm::timeTrackRecord() {
  auto timeFragment = std::chrono::system_clock::now() - last;
  elapsedTime += timeFragment.count();
  last = std::chrono::system_clock::now();
}
