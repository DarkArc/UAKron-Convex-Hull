#include "HullAlgorithm.hpp"

HullAlgorithm::~HullAlgorithm() { }

double HullAlgorithm::getTime() const {
  return elapsedTime;
}

void HullAlgorithm::timeTrackInit() {
  elapsedTime = 0;
  last = std::chrono::high_resolution_clock::now();
}

void HullAlgorithm::timeTrackUpdate() {
  last = std::chrono::high_resolution_clock::now();
}

void HullAlgorithm::timeTrackRecord() {
  std::chrono::duration<double> timeFragment = std::chrono::high_resolution_clock::now() - last;
  elapsedTime += timeFragment.count();
  last = std::chrono::high_resolution_clock::now();
}
