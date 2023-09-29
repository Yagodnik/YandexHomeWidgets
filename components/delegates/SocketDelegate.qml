import QtQuick 2.15
import "../../components/ui" as Components
import Yandex 1.0

Item {
    id: delegate
    width: devicesGrid.width - 4
    height: 32
    clip: true

    Rectangle {
        width: 3
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        color: "#00829e"
        radius: 3
    }

    Text {
        id: title
        color: "#1d1e1d"

        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.top: parent.top
        anchors.topMargin: 5

        verticalAlignment: Text.AlignVCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 19

        text: deviceData["name"]
    }

    Components.Switch {
        id: onOff

        width: 45
        height: 22

        anchors.left: title.right
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 6

        Binding on value {
            value: deviceData["state"]
        }

        onClicked: {
            yandexHome.setWatcherState(false);
            yandexHome.withId(deviceData["id"]).setState(value);
        }
    }
}