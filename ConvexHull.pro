QT += qml quick

CONFIG += qt debug
CONFIG += c++11

HEADERS += Algorithms/HullAlgorithm.hpp \
    Algorithms/GrahamScan.hpp
HEADERS += Algorithms/HullSolver.hpp
HEADERS += HullRenderer.hpp
HEADERS += HullState.hpp
HEADERS += HullTimeline.hpp

SOURCES += Algorithms/HullSolver.cpp
SOURCES += HullRenderer.cpp
SOURCES += HullState.cpp
SOURCES += HullTimeline.cpp
SOURCES += main.cpp

RESOURCES += resources.qrc
