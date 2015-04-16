#ifndef RANDOMPOINTINPUT_HPP
#define RANDOMPOINTINPUT_HPP

#include "../DataInput.hpp"

class RandomPointInput : public DataInput {
  unsigned int pointCount;
public:
  RandomPointInput(unsigned int);
  virtual ~RandomPointInput();

  virtual std::vector<QPoint> getPoints();
};

#endif
