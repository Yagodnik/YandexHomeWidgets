import QtQuick 2.15
import "../ui" as Components

Item {
    id: header

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.topMargin: 5
    anchors.leftMargin: 3
    anchors.rightMargin: 3
    height: 32

    Text {
        color: "#1d1e1d"

        anchors.left: header.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter

        verticalAlignment: Text.AlignVCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 16

        text: "Ваши устройства"
    }

    Components.Button {
        id: updateButton

        text: "Обновить"

        width: 90
        height: 28

        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
//            yandexHome.clearDevices();
            yandexHome.loadDevices();
        }
    }
}
