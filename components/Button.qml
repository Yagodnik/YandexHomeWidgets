import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Item {
    id: root
    property string text: "Text"

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#e4f2e6"
        radius: 3

        border.color: "#dae8dc"
        border.width: 1

        FastBlur {
            anchors.fill: parent
            source: parent
            radius: 32
        }
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: root.text

        color: "#1d1e1d"

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 12
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onContainsMouseChanged: {
            if (containsMouse) {
                background.border.color = "#747474";
            } else {
                background.border.color = "#dae8dc";
            }
        }
    }
}
