import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Item {
    Rectangle {
        anchors.fill: parent
        color: "#e7f2db"
        radius: 3

        border.color: "#dde8d4"
        border.width: 2

        FastBlur {
            anchors.fill: parent
            source: parent
            radius: 32
        }
    }
}
