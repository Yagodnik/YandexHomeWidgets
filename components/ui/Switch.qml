import QtQuick

Item {
    id: root

    property bool value: false
    signal clicked

    onValueChanged: {
        !value ? root.state = "off" : root.state = "on";
    }

    Rectangle {
        id: background
        anchors.fill: parent

        radius: 45
        color: "#dceadd"

        border.color: "#999b9c"
        border.width: 1
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            root.value = !root.value;
            root.clicked();
        }
    }

    Rectangle {
        id: handle

        width: parent.height - 6
        height: parent.height - 6

        anchors.verticalCenter: parent.verticalCenter
        x: 3
        radius: 45

        color: "#797c7d"
    }

    states: [
        State {
            name: "off"
            PropertyChanges {
                target: handle
                x: 3
            }

            PropertyChanges {
                target: handle
                color: "#797c7d"
            }

            PropertyChanges {
                target: background
                color: "#dceadd"
            }

            PropertyChanges {
                target: background
                border.color: "#999b9c"
            }
        },

        State {
            name: "on"
            PropertyChanges {
                target: handle
                x: root.width - handle.width - 3
            }

            PropertyChanges {
                target: handle
                color: "#fefefe"
            }

            PropertyChanges {
                target: background
                color: "#00829e"
            }

            PropertyChanges {
                target: background
                border.color: "#00829e"
            }
        }
    ]

    transitions: Transition {
        PropertyAnimation {
            target: handle
            properties: "x, color"
            easing.type: Easing.InOutSine
        }

        PropertyAnimation {
            target: background
            properties: "color, border.color"
            easing.type: Easing.InOutSine
        }
    }
}
