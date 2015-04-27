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
      minimumValue: 4
      maximumValue: 5000
    }

    Label {
      text: "Max Point:"
    }

    SpinBox {
      id: max_point
      value: random_input.maxPoint
      minimumValue: 5
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
      minimumValue: 4
      maximumValue: 5000
    }

    Label {
      text: "Radius:"
    }

    SpinBox {
      id: radius
      value: circular_input.radius
      minimumValue: 1
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
