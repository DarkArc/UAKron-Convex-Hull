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

#ifndef HULLRENDERER_HPP
#define HULLRENDERER_HPP

#include <QtQuick>
#include <QRect>

#include "HullTimeline.hpp"

class HullRenderer : public QQuickPaintedItem {
  Q_OBJECT
  HullTimeline timeline;
  int position;
public:
  HullRenderer(QQuickItem *parent = 0);
  void paint(QPainter *painter);

  bool hasHull() const;

  Q_INVOKABLE int curPosition() const;
  Q_INVOKABLE int maxPosition() const;

public slots:
  void setTimeline(const HullTimeline&);
  void advance();

signals:
  void stageComplete() const;

private:
  QPointF adjustPoint(const QPoint&) const;
};

#endif
