#ifndef JARVISMARCH
#define JARVISMARCH

#include <QPoint>

#include <vector>

#include "../HullState/HullState.hpp"
#include "../HullAlgorithm.hpp"


class JarvisMarch : public HullAlgorithm {
  std::vector<QPoint> pts;
  std::vector<HullState*> stages;
public:
  JarvisMarch();
  virtual ~JarvisMarch();

  virtual QString name() const;
  virtual HullTimeline getTimeline(const std::vector<QPoint>&);

private:
  HullState* captureSnapshot(const std::vector<QPoint>&) const;
  HullState* captureSnapshot(std::vector<QPoint>, const QPoint&) const;

  /* Internal functions */
  int ccw(const QPoint&, const QPoint&, const QPoint&) const;
};

#endif // JARVISMARCH
