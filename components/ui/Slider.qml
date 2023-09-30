import QtQuick

Item {
    id: root

    property int sliderWidth
    property real value: 0
    signal newValue

    onValueChanged: {
        if (!mouseArea.drag.active && !clickArea.isClicked) {
            progress.width = (sliderWidth - handle.width) * value;
            handle.x = (sliderWidth - handle.width) * value;
        }

        clickArea.isClicked = false;
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

    MouseArea {
        id: clickArea
        width: parent.width
        height: parent.height + 6
        anchors.centerIn: parent

        property bool isClicked: false

        onClicked: {
            isClicked = true;
            handle.x = mouseX - handle.width / 2;

            root.value = (handle.x / mouseArea.drag.maximumX).toFixed(2);
            root.newValue();
        }
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
                    console.log(handle.x)
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
