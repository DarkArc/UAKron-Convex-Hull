# Copyright (C) 2015 Wyatt Childers & Emil Heineking
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
