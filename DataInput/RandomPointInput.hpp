#ifndef RANDOMPOINTINPUT_HPP
#define RANDOMPOINTINPUT_HPP

#include <QObject>

#include "../DataInput.hpp"

class RandomPointInput : public QObject, public DataInput {
  Q_OBJECT

  Q_PROPERTY(unsigned int pointCount READ pointCount WRITE setPointCount NOTIFY pointCountChanged);
  Q_PROPERTY(unsigned int maxPoint READ maxPoint WRITE setMaxPoint NOTIFY maxPointChanged);

  unsigned int m_pointCount;
  unsigned int m_maxPoint;
public:
  RandomPointInput(const unsigned int&, const unsigned int&);
  virtual ~RandomPointInput();

  virtual QString name() const;

  unsigned int pointCount() const;
  void setPointCount(const unsigned int&);

  unsigned int maxPoint() const;
  void setMaxPoint(const unsigned int&);

  virtual std::vector<QPoint> getPoints();

signals:
  void pointCountChanged() const;
  void maxPointChanged() const;
};

#endif
