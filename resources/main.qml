import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

TabView {
  id: root
  tabPosition: Qt.BottomEdge

  style: TabViewStyle {
    tabsAlignment: Qt.AlignRight
  }

  Tab {
    title: "Renderer"
    active: true
    Renderer { }
  }

  Tab {
    title: "Data"
    active: true
    Data_View { }
  }

  Tab {
    title: "Input Method"
    active: true
    Input_Method { }
  }
}
