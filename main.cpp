#include <QMap>
#include <QString>
#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "Algorithms/GrahamScan.hpp"
#include "Algorithms/JarvisMarch.hpp"
#include "DataInput/RandomPointInput.hpp"

#include "HullSolver.hpp"
#include "HullState.hpp"
#include "HullRenderer.hpp"
#include "HullTimeline.hpp"

int main(int argc, char** argv) {

  QGuiApplication app(argc, argv);

  qmlRegisterType<HullRenderer>("com.nearce.HullRenderer", 1, 0, "HullRenderer");

  QQuickView view;

  // Algorithm setup
  GrahamScan grahamScan;
  JarvisMarch jarvisMarch;

  // Input setup
  RandomPointInput randomPointInput(1000, false);

  QMap<QString, HullAlgorithm*> algorithms({
    {grahamScan.name(), &grahamScan},
    {jarvisMarch.name(), &jarvisMarch}
  });
  QMap<QString, DataInput*> inputs({
    {randomPointInput.name(), &randomPointInput}
  });

  HullSolver solver(algorithms, inputs);

  view.engine()->rootContext()->setContextProperty("hull_solver", &solver);

  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setSource(QUrl("qrc:///resources/main.qml"));
  view.showMaximized();

  HullRenderer* renderer = view.rootObject()->findChild<HullRenderer*>("renderer");

  // C++ Program Logic
  QObject::connect(&solver, SIGNAL(solutionFound(const HullTimeline&)),
                   renderer, SLOT(setTimeline(const HullTimeline&)));

  return app.exec();
}
