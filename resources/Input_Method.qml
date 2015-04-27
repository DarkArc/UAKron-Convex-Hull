import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

ColumnLayout {

  RowLayout {
    Label {
      text: "Number of Points:"
    }

    SpinBox {
      id: rand_point_count
      value: random_input.pointCount
      maximumValue: 5000
    }

    Label {
      text: "Max Point:"
    }

    SpinBox {
      id: max_point
      value: random_input.maxPoint
      maximumValue: 100000
    }

    Button {
      text: "Load Random Dataset"

      onClicked: {
        random_input.pointCount = rand_point_count.value;
        random_input.maxPoint = max_point.value;

        hull_solver.input = "Random Point";
        hull_solver.repollData();
      }
    }
  }

  RowLayout {
    Label {
      text: "Number of Segments:"
    }

    SpinBox {
      id: circ_point_count
      value: circular_input.pointCount
      maximumValue: 5000
    }

    Label {
      text: "Radius:"
    }

    SpinBox {
      id: radius
      value: circular_input.radius
      maximumValue: 100000
    }

    Button {
      text: "Generate Circle"

      onClicked: {
        circular_input.pointCount = circ_point_count.value;
        circular_input.radius = radius.value;

        hull_solver.input = "Circular Point";
        hull_solver.repollData();
      }
    }
  }
}
