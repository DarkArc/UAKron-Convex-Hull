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

#include "HullRenderer.hpp"

#include <memory>

/** Construct a new HullRenderer object.

    Constructs a new HullRenderer object, with
    the specified QQuickItem as its parent, and
    the render target set to
    QQuickPaintedItem::FramebufferObject.

    @param parent
    The parent QQuickItem of this HullRenderer.
 */
HullRenderer::HullRenderer(QQuickItem* parent) : QQuickPaintedItem(parent) {
  setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

/** Render the hull.

    Renders the current stage of the hull from the
    HullTimeline. If there is not currently a
    HullTimeline availible, no rendering shall be
    performed.

    @param painter
    The QPainter object to use for the rendering.
 */
void HullRenderer::paint(QPainter* painter) {

  // Ensure we have a hull availible
  if (!hasHull()) return;

  // Request that the drawling be Antialiased for a
  // better image
  painter->setRenderHint(QPainter::Antialiasing);

  // Establish a couple different QPens for drawling
  // the different types of visual elements
  QPen pointPen(QBrush(Qt::blue), 10, Qt::SolidLine, Qt::RoundCap);
  QPen linePen(QBrush(Qt::black), 4, Qt::SolidLine, Qt::RoundCap);

  // Fetch the timeline
  std::shared_ptr<HullState> state = timeline.getEvents()[position];

  // Draw Points
  painter->setPen(pointPen);
  for (auto& point : state->getPoints()) {
    painter->drawPoint(adjustPoint(point));
  }

  // Draw Lines
  painter->setPen(linePen);
  for (auto& line : state->getLines()) {
    auto&& start = adjustPoint(line.p1());
    auto&& end = adjustPoint(line.p2());
    painter->drawLine(start, end);
  }

  // Inform anyone who cares that we're done drawling
  emit stageComplete();
}

/** Check for a HullTimeline.

    Checks to see if there is currently a valid
    HullTimeline which can be rendered.

    @return true if there is a HullTimeline
    with any events.
 */
bool HullRenderer::hasHull() const {
  return timeline.getEventCount() > 0;
}

/** Retrieve the current timeline position.

    Retrieves the current timeline position,
    or in other words, the timeline position
    which should be drawn.

    @returns the current timeline position.
 */
int HullRenderer::curPosition() const {
  return position + 1;
}

/** Retrieve the maximum timeline position.

    Retrieves the maximum timeline position
    which can be drawn for the current
    timeline.

    @returns the maximum timeline position.
 */
int HullRenderer::maxPosition() const {
  return timeline.getEventCount();
}

/** Replace the current timeline.

    Replaces the currently used timeline
    with the one specified resetting the
    current timeline position to it's initial
    value. Then request a redrawl by the renderer
    to show the new initial value.

    @param timeline
    The new HullTimeline to display.
 */
void HullRenderer::setTimeline(const HullTimeline& timeline) {
  this->timeline = timeline;
  this->position = 0;
  update();
}

/** Advance the timeline position.

    Advances the timeline position by
    one increment. If the end of the
    timeline has been reached, no
    position change will occur.

    If a position change occurs,
    a redrawl by the renderer
    will be request to show the new
    value.
 */
void HullRenderer::advance() {
  if (curPosition() < maxPosition()) {
    ++position;
    update();
  }
}

/** Adjust a point for drawling.

    The Qt Point system cannot directly drawl
    negative points, nor will it correctly drawl
    points based simply on their x & y quardenents
    in the state they are in once being retrieved from
    the timeline.

    To account for this, the point is passed to
    this function so that it may be adjusted for
    proper drawling.

    @param point
    The unprocessed point.

    @returns a processed point which may be used
    to properly drawl with.
 */
QPointF HullRenderer::adjustPoint(const QPoint& point) const {
  // Get the minimum and maximum points
  QPoint min = timeline.getMin();
  QPoint max = timeline.getMax();

  // Update the maximum point to be down shifted
  // by the minimum point, as the rest of the points
  // will follow this same transition
  max.setX(max.x() - min.x());
  max.setY(max.y() - min.y());

  // Find the ratio of the point to the maximum point,
  // so as to be able to work with the quardenent in terms of a
  // percentage
  double ratioX = (point.x() - min.x()) / static_cast<double>(max.x());
  double ratioY = (max.y() - (point.y() - min.y())) / static_cast<double>(max.y());

  // Accure the bounding rectangle for the drawling area
  // so we know what space we have to work with
  auto boundingRec = contentsBoundingRect();

  // Create a new point with respect to the drawling area, adding
  // an additional 10 px to avoid drawling too close to an edge
  return QPointF(((boundingRec.width() - 20) * ratioX) + 10, ((boundingRec.height() - 20) * ratioY) + 10);
}
