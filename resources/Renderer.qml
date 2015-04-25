import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1

import com.nearce.HullRenderer 1.0

ColumnLayout {
  HullRenderer {
    id: renderer
    objectName: "renderer"
    Layout.preferredHeight: 600

    Layout.fillWidth: true
    Layout.fillHeight: true

    onStageComplete: {
      renderer_progress.value = renderer.curPosition() / renderer.maxPosition()
    }

    Timer {
      interval: speed_slider.value * 2000; running: renderer_playback.checked; repeat: true
      onTriggered: renderer.advance()
    }
  }

  RowLayout {
    Layout.alignment: Qt.AlignLeft

    anchors.top: renderer.bottom
    anchors.left: renderer.left
    anchors.leftMargin: 10

    ProgressBar {
      id: renderer_progress
    }
  }

  RowLayout {
    id: control_box

    anchors.top: renderer.bottom
    anchors.right: renderer.right
    anchors.rightMargin: 10

    Layout.alignment: Qt.AlignRight

    Label {
      text: "Algorithm: "
    }

    ComboBox {
      id: algorithm_box
      objectName: "algorithm_box"
      implicitWidth: 150

      model: ListModel {
          ListElement { text: "Graham Scan" }
          ListElement { text: "Jarvis March" }
      }
    }

    Label {
      text: "Playback: "
    }

    Switch {
      id: renderer_playback
      checked: true
    }

    Label {
      text: "Playback Speed: "
    }

    Slider {
      id: speed_slider
      activeFocusOnPress: true
      updateValueWhileDragging: true
      minimumValue: .01
      maximumValue: 1
      value: .5

      style: SliderStyle {
        groove: Rectangle {
          implicitWidth: renderer.width / 4
          implicitHeight: 8
          color: "grey"
          radius: 8
        }
      }
    }

    Button {
      objectName: "process_hull"
      Layout.alignment: Qt.AlignHCenter

      text: "Process Hull"

      onClicked: {
        hull_solver.algorithm = algorithm_box.currentText;
        hull_solver.calculate();
      }
    }
  }
}
