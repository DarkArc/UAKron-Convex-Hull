#ifndef CIRCULARPOINTINPUT_HPP
#define CIRCULARPOINTINPUT_HPP

#include <QObject>

#include "../DataInput.hpp"

class CircularPointInput : public QObject, public DataInput {
  Q_OBJECT

  Q_PROPERTY(int pointCount READ pointCount WRITE setPointCount NOTIFY pointCountChanged);
  Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged);

  unsigned int m_pointCount;
  unsigned int m_radius;
public:
  CircularPointInput(const unsigned int&, const unsigned int&);
  virtual ~CircularPointInput();

  virtual QString name() const;

  unsigned int pointCount() const;
  void setPointCount(const unsigned int&);

  unsigned int radius() const;
  void setRadius(const unsigned int&);

  virtual std::vector<QPoint> getPoints();

signals:
  void pointCountChanged() const;
  void radiusChanged() const;
};

#endif
