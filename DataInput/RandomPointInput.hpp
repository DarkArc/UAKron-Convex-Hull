#ifndef RANDOMPOINTINPUT_HPP
#define RANDOMPOINTINPUT_HPP

#include "../DataInput.hpp"

class RandomPointInput : public DataInput {
  unsigned int pointCount;
  bool circle;
public:
  RandomPointInput(unsigned int, bool);
  virtual ~RandomPointInput();

  virtual QString name() const;

  virtual std::vector<QPoint> getPoints();
};

#endif
