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

  srand(time(NULL));

  QGuiApplication app(argc, argv);

  qmlRegisterType<HullRenderer>("com.nearce.HullRenderer", 1, 0, "HullRenderer");

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setSource(QUrl("qrc:///resources/main.qml"));
  view.showMaximized();

  HullRenderer* renderer = view.rootObject()->findChild<HullRenderer*>("renderer");

  GrahamScan algo;
  JarvisMarch algo2;
  RandomPointInput input(50);
  HullSolver solver(algo2, input);

  QObject::connect(&solver, SIGNAL(solutionFound(const HullTimeline&)),
                   renderer, SLOT(setTimeline(const HullTimeline&)));

  QObject* processButton = view.rootObject()->findChild<QObject*>("process_hull");

  QObject::connect(processButton, SIGNAL(clicked()), &solver, SLOT(calculate()));

  QObject* loadButton = view.rootObject()->findChild<QObject*>("load_data");
  QObject::connect(loadButton, SIGNAL(clicked()), &solver, SLOT(repollData()));


  return app.exec();
}
