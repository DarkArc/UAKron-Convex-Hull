#ifndef DATAINPUT_HPP
#define DATAINPUT_HPP

#include <QPoint>
#include <QString>

#include <vector>

class DataInput {
public:
  virtual ~DataInput() = 0;

  virtual QString name() const = 0;

  virtual std::vector<QPoint> getPoints() = 0;
};
#endif
