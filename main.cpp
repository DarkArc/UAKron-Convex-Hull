#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "Algorithms/HullSolver.hpp"
#include "Algorithms/GrahamScan.hpp"

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
  HullSolver solver(algo);

  QObject::connect(&solver, SIGNAL(solutionFound(const HullTimeline&)),
                   renderer, SLOT(setTimeline(const HullTimeline&)));

  QObject* processButton = view.rootObject()->findChild<QObject*>("process_hull");

  QObject::connect(processButton, SIGNAL(clicked()), &solver, SLOT(calculate()));


  return app.exec();
}
