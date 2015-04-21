#ifndef JARVISMARCH
#define JARVISMARCH

#include <QPoint>

#include <stack>   // Hold the convex hull points
#include <vector>

#include "../HullState.hpp"
#include "../HullAlgorithm.hpp"


class JarvisMarch : public HullAlgorithm {
        std::vector<QPoint> pts;
        std::vector<HullState> stages;
    public:
        JarvisMarch();
        virtual ~JarvisMarch();

        virtual HullTimeline getTimeline(const std::vector<QPoint>&);

    private:

        /* Internal functions */
        int ccw(const QPoint&, const QPoint&, const QPoint&) const;
};

#endif // JARVISMARCH

