#include <string>
#include <unordered_map>

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

  QObject* algorithmBox = view.rootObject()->findChild<QObject*>("algorithm_box");
  QObject* inputBox = view.rootObject()->findChild<QObject*>("input_box");

  GrahamScan grahamScan;
  JarvisMarch jarvisMarch;

  RandomPointInput randomPointInput(50);

  std::unordered_map<std::string, HullAlgorithm*> algorithms({
    {"Graham Scan", &grahamScan},
    {"Jarvis March", &jarvisMarch}
  });
  std::unordered_map<std::string, DataInput*> inputs({
    {"Random Input", &randomPointInput}
  });

  HullSolver solver(algorithmBox, algorithms, inputBox, inputs);

  QObject::connect(algorithmBox, SIGNAL(activated(int)),
                   &solver, SLOT(repollAlgorithm()));

  QObject::connect(&solver, SIGNAL(solutionFound(const HullTimeline&)),
                   renderer, SLOT(setTimeline(const HullTimeline&)));

  QObject* processButton = view.rootObject()->findChild<QObject*>("process_hull");

  QObject::connect(processButton, SIGNAL(clicked()), &solver, SLOT(calculate()));

  QObject* loadButton = view.rootObject()->findChild<QObject*>("load_data");
  QObject::connect(loadButton, SIGNAL(clicked()), &solver, SLOT(repollData()));


  return app.exec();
}
