import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

ColumnLayout {

  RowLayout {
    Label {
      text: "Max Point:"
    }

    SpinBox {
        id: max_points
    }
  }

  RowLayout {
    Label {
      text: "Number of Points:"
    }

    SpinBox {
        id: point_count
    }
  }

  RowLayout {
    Button {
      text: "Load Random Dataset"

      onClicked: {
        hull_solver.input = "Random Point";
        hull_solver.repollData();
      }
    }
  }
}
