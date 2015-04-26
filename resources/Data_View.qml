import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1

SplitView {
  orientation: Qt.Vertical

  Connections {
    target: hull_solver
    onSolutionFound: {
      addTiming(algorithm, origPoints, hullPoints, time)
      purgeOldPoints()
    }

    onOrigPointDiscovered: {
      addOrigPoint(x, y);
    }

    onHullPointFound: {
      addHullPoint(x, y);
    }
  }

  function addTiming(algorithm, points, hullPoints, time) {
    timings.append({"algorithm": algorithm, "points": points, "hullPoints": hullPoints, "time": time})
  }

  function addOrigPoint(x, y) {
    orig_points.append({"x": x, "y": y});
  }

  function addHullPoint(x, y) {
    hull_points.append({"x": x, "y": y});
  }

  function purgeOldPoints() {
    orig_points.clear()
    hull_points.clear()
  }

  ListModel {
      id: timings
  }

  SplitView {
    ListModel {
        id: orig_points
    }

    ListModel {
        id: hull_points
    }

    ColumnLayout {
      Label {
        anchors.horizontalCenter: orig_table.horizontalCenter

        text: "Original Points"
      }

      TableView {
        id: orig_table

        Layout.fillWidth: true
        Layout.fillHeight: true

        TableViewColumn {
          role: "x"
          title: "X"
          width: 100
        }
        TableViewColumn {
          role: "y"
          title: "Y"
          width: 100
        }
        model: orig_points
      }
    }

    ColumnLayout {
      Label {
        anchors.horizontalCenter: hull_table.horizontalCenter

        text: "Convex Hull Points"
      }

      TableView {
        id: hull_table

        Layout.fillWidth: true
        Layout.fillHeight: true

        TableViewColumn {
          role: "x"
          title: "X"
          width: 100
        }
        TableViewColumn {
          role: "y"
          title: "Y"
          width: 100
        }
        model: hull_points
      }
    }
  }

  ColumnLayout {
    Label {
      anchors.horizontalCenter: timings_table.horizontalCenter
      text: "Algorithm Performance"
    }
    TableView {
      id: timings_table

      Layout.fillWidth: true
      Layout.fillHeight: true

      sortIndicatorVisible: true

      TableViewColumn {
        role: "algorithm"
        title: "Algorithm"
        width: 150
      }
      TableViewColumn {
        role: "points"
        title: "Point Count"
        width: 100
      }
      TableViewColumn {
        role: "hullPoints"
        title: "Hull Point Count"
        width: 100
      }
      TableViewColumn {
        role: "time"
        title: "Ellapsed Time"
        width: 1000
      }
      model: timings
    }
  }
}
