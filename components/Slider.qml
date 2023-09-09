import QtQuick 2.15

Item {
    id: root

    property int sliderWidth
    property real value: 0
    signal newValue

    onValueChanged: {
        if (!mouseArea.drag.active) {
            progress.width = (sliderWidth - handle.width) * value;
            handle.x = (sliderWidth - handle.width) * value;
        }
    }

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

        onXChanged: {
            progress.width = handle.x;
        }

        Rectangle {
            id: center

            anchors.centerIn: parent

            width: parent.width - 8
            height: parent.height - 8
            radius: 45

            color: "#1c7e94"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: handle
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: root.width - handle.width
            drag.onActiveChanged: {
                if (!drag.active) {
                    root.value = (handle.x / drag.maximumX).toFixed(2);
                    root.newValue();
                }
            }

            hoverEnabled: true
            onContainsMouseChanged: {
                if (containsMouse) {
                    handle.border.color = "#747474";
                } else {
                    handle.border.color = "#dae8dc";
                }
            }
        }
    }
}
