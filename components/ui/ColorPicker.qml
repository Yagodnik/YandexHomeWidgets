import QtQuick

GridView {
    id: root
    interactive: false

    property string valueRole: "colorValue"
    property string displayRole: "colorValue"

    property var currentColor
    signal clicked

    cellWidth: 34
    cellHeight: 34

    delegate: Rectangle {
        id: delegate
        color: model[root.displayRole]
        width: root.cellWidth - 4
        height: root.cellHeight - 4

        state: "noHover"
        border.width: 1
        border.color: "#8e978f"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                currentColor = model[root.valueRole];
                root.clicked();
            }

            onContainsMouseChanged: {
                delegate.state === "hover" ? delegate.state = "noHover" : delegate.state = "hover";
            }
        }

        states: [
            State {
                name: "noHover"

                PropertyChanges {
                    target: delegate
                    radius: 8
                }
            },

            State {
                name: "hover"

                PropertyChanges {
                    target: delegate
                    radius: 5
                }
            }
        ]

        transitions: Transition {
            PropertyAnimation {
                target: delegate
                properties: "radius"
                easing.type: Easing.InOutSine
            }
        }
    }
}
