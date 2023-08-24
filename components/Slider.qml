import QtQuick 2.15

Item {
    id: root

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#8e978f"
        radius: 3
    }

    Rectangle {
        id: progress
        radius: 3
        color: "#1c7e94"

        height: parent.height
        width: handle.x
        x: 0
    }

    Rectangle {
        id: handle

        anchors.verticalCenter: background.verticalCenter
        x: 0

        width: 20
        height: 20
        radius: 45
        color: "#dbdbdb"

        border.width: 1
        border.color: "#dae8dc"

        Rectangle {
            id: center

            anchors.centerIn: parent

            width: parent.width - 8
            height: parent.height - 8
            radius: 45

            color: "#1c7e94"
        }

        MouseArea {
            anchors.fill: parent
            drag.target: handle
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: root.width - handle.width
        }
    }
}
