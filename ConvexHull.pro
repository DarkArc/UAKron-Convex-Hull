QT += qml quick

CONFIG += qt debug
CONFIG += c++11

HEADERS += Algorithms/GrahamScan.hpp
HEADERS += Algorithms/JarvisMarch.hpp
HEADERS += DataInput/CircularPointInput.hpp
HEADERS += DataInput/RandomPointInput.hpp
HEADERS += Util/Optional.hpp
HEADERS += DataInput.hpp
HEADERS += HullAlgorithm.hpp
HEADERS += HullRenderer.hpp
HEADERS += HullSolver.hpp
HEADERS += HullState.hpp
HEADERS += HullTimeline.hpp

SOURCES += Algorithms/GrahamScan.cpp
SOURCES += Algorithms/JarvisMarch.cpp
SOURCES += DataInput/CircularPointInput.cpp
SOURCES += DataInput/RandomPointInput.cpp
SOURCES += DataInput.cpp
SOURCES += HullAlgorithm.cpp
SOURCES += HullRenderer.cpp
SOURCES += HullSolver.cpp
SOURCES += HullState.cpp
SOURCES += HullTimeline.cpp
SOURCES += main.cpp

RESOURCES += resources.qrc
