// Copyright (C) 2015 Wyatt Childers & Emil Heineking
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QMap>
#include <QString>
#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "Algorithms/GrahamScan.hpp"
#include "Algorithms/JarvisMarch.hpp"
#include "DataInput/CircularPointInput.hpp"
#include "DataInput/RandomPointInput.hpp"

#include "HullSolver.hpp"
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
  RandomPointInput randomPointInput(50, 1000);
  CircularPointInput circularPointInput(50, 1000);

  QMap<QString, HullAlgorithm*> algorithms({
    {grahamScan.name(), &grahamScan},
    {jarvisMarch.name(), &jarvisMarch}
  });
  QMap<QString, DataInput*> inputs({
    {randomPointInput.name(), &randomPointInput},
    {circularPointInput.name(), &circularPointInput}
  });

  HullSolver solver(algorithms, inputs);

  view.engine()->rootContext()->setContextProperty("random_input", &randomPointInput);
  view.engine()->rootContext()->setContextProperty("circular_input", &circularPointInput);
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
