#ifndef JARVISMARCH
#define JARVISMARCH

#include <QPoint>

#include <vector>
#include <memory>

#include "../HullState/HullState.hpp"
#include "../HullAlgorithm.hpp"


class JarvisMarch : public HullAlgorithm {
  std::vector<QPoint> pts;
  std::vector<std::shared_ptr<HullState>> stages;
public:
  JarvisMarch();
  virtual ~JarvisMarch();

  virtual QString name() const;
  virtual HullTimeline getTimeline(const std::vector<QPoint>&);

private:
  std::shared_ptr<HullState> captureSnapshot(const std::vector<QPoint>&) const;
  std::shared_ptr<HullState> captureSnapshot(std::shared_ptr<HullState>, std::vector<QPoint>, const QPoint&) const;

  /* Internal functions */
  int ccw(const QPoint&, const QPoint&, const QPoint&) const;
};

#endif // JARVISMARCH
