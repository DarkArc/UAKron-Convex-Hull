#ifndef HULLSOLVER_HPP
#define HULLSOLVER_HPP

#include <QMap>
#include <QObject>
#include <QString>

#include <vector>
#include <unordered_map>

#include "HullAlgorithm.hpp"
#include "DataInput.hpp"
#include "HullTimeline.hpp"
#include "Util/Optional.hpp"

class HullSolver : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged);
  Q_PROPERTY(QString input READ input WRITE setInput NOTIFY inputChanged);

  QMap<QString, HullAlgorithm*>* algorithms;
  QMap<QString, DataInput*>* inputs;

  HullAlgorithm* m_algorithm = nullptr;
  DataInput* m_input = nullptr;

  std::vector<QPoint> inputPts;
  Optional<HullTimeline> timeline;
public:
  HullSolver(QMap<QString, HullAlgorithm*>&, QMap<QString, DataInput*>&);

  QString algorithm() const;
  void setAlgorithm(const QString&);

  QString input() const;
  void setInput(const QString&);

public slots:
  void calculate();
  void repollData();

signals:
  void error(const QString&) const;

  void origPointDiscovered(const int& x, const int& y) const;
  void hullPointFound(const int& x, const int& y) const;

  void solutionFound(const HullTimeline&) const;
  void solutionFound(const QString& a, const int& b, const int& c) const;

  void algorithmChanged(const QString&) const;
  void inputChanged(const QString&) const;
};

#endif
