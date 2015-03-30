import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

ColumnLayout {

  Rectangle {
    id: renderer
    color: "red"
    Layout.preferredHeight: 600

    Layout.fillWidth: true
    Layout.fillHeight: true
  }

  RowLayout {
    id: control_box
    Layout.alignment: Qt.AlignHCenter

    ColumnLayout {
      Layout.preferredWidth: 300
      Layout.alignment: Qt.AlignHCenter | Qt.Top

      Text {
        Layout.alignment: Qt.AlignHCenter

        text: "Algorithm"
      }

      ComboBox {
        Layout.preferredWidth: 280
        Layout.alignment: Qt.AlignHCenter
        model: [ "Gram Scan" ]
      }
    }

    ColumnLayout {
      Layout.preferredWidth: 600
      Layout.alignment: Qt.AlignHCenter | Qt.Top

      Text {
        Layout.alignment: Qt.AlignHCenter

        text: "Properties"
      }

      RowLayout {
        Text {
          id: speed_label
          text: "Speed"
        }

        Slider {
          width: parent.parent.width - speed_label.width - (parent.spacing * 4)
          value: 0.5
        }
      }
    }

    ColumnLayout {
      Layout.preferredWidth: 300
      Layout.alignment: Qt.AlignHCenter | Qt.Top

      Text {
        Layout.alignment: Qt.AlignHCenter

        text: "Actions"
      }

      RowLayout {
        Layout.alignment: Qt.AlignHCenter | Qt.Top

        Button {
          Layout.alignment: Qt.AlignHCenter

          text: "Process Hull"
        }

        Button {
          Layout.alignment: Qt.AlignHCenter

          text: "Load Dataset"
        }

        Button {
          Layout.alignment: Qt.AlignHCenter

          text: "Save Result"
        }
      }
    }

    SequentialAnimation {
        running: true
        NumberAnimation {
          target: control_box
          property: "opacity"
          from: 0
          to: 1.0
          duration: 800
        }
    }
  }
}
