import QtQuick 2.15

GridView {
    id: colorsGrid
    interactive: false

    cellWidth: 34
    cellHeight: 34

    delegate: Rectangle {
        id: delegate
        color: colorValue
        width: colorsGrid.cellWidth - 4
        height: colorsGrid.cellHeight - 4

        radius: 3

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onContainsMouseChanged: {
                delegate.state === "hover" ? delegate.state = "noHover" : delegate.state = "hover";
            }
        }

        states: [
            State {
                name: "noHover"

                PropertyChanges {
                    target: delegate
                    radius: 5
                }
            },

            State {
                name: "hover"

                PropertyChanges {
                    target: delegate
                    radius: 8
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

    model: colorModel
}
