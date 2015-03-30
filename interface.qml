import QtQuick 2.3

Rectangle {
    id: buttonMouseArea

    gradient: Gradient {
        GradientStop {
            position: 0.0
            SequentialAnimation on color {
                loops: Animation.Infinite
                ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: 5000 }
                ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: 5000 }
            }
        }
        GradientStop {
            position: 1.0
            SequentialAnimation on color {
                loops: Animation.Infinite
                ColorAnimation { from: "#14aaff"; to: "#437284"; duration: 5000 }
                ColorAnimation { from: "#437284"; to: "#14aaff"; duration: 5000 }
            }
        }
    }

}
