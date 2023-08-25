import QtQuick 2.15

GridView {
    id: root
    interactive: false

    cellWidth: 34
    cellHeight: 34

    delegate: Rectangle {
        id: delegate
        color: colorValue
        width: root.cellWidth - 4
        height: root.cellHeight - 4

        radius: 3

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                yandexHome.setColor(deviceId, colorValue);
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
}
