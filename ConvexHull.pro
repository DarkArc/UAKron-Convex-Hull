QT += qml quick

QMAKE_CXXFLAGS += -O2

CONFIG += qt debug
CONFIG += c++11

HEADERS += Algorithms/GrahamScan.hpp
HEADERS += Algorithms/JarvisMarch.hpp
HEADERS += DataInput/CircularPointInput.hpp
HEADERS += DataInput/RandomPointInput.hpp
HEADERS += HullState/DependantHullState.hpp
HEADERS += HullState/HullState.hpp
HEADERS += HullState/StandaloneHullState.hpp
HEADERS += Util/Optional.hpp
HEADERS += DataInput.hpp
HEADERS += HullAlgorithm.hpp
HEADERS += HullRenderer.hpp
HEADERS += HullSolver.hpp
HEADERS += HullTimeline.hpp

SOURCES += Algorithms/GrahamScan.cpp
SOURCES += Algorithms/JarvisMarch.cpp
SOURCES += DataInput/CircularPointInput.cpp
SOURCES += DataInput/RandomPointInput.cpp
SOURCES += HullState/DependantHullState.cpp
SOURCES += HullState/HullState.cpp
SOURCES += HullState/StandaloneHullState.cpp
SOURCES += DataInput.cpp
SOURCES += HullAlgorithm.cpp
SOURCES += HullRenderer.cpp
SOURCES += HullSolver.cpp
SOURCES += HullTimeline.cpp
SOURCES += main.cpp

RESOURCES += resources.qrc
