import QtQuick 2.15

Item {
    id: loadingPage

    Text {
        id: loadingText
        height: 32

        color: "#1d1e1d"

        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 14

        text: qsTr("Загрузка...")
    }

    Item {
        id: root

        width: 200
        height: 3

        anchors.top: loadingText.bottom
        anchors.topMargin: 1
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: background
            anchors.fill: parent
            radius: 3
            color: "#8e978f"
            clip: true

            Rectangle {
                id: handle
                width: 30
                height: parent.height
                color: "#1c7e94"
                radius: 3

                PropertyAnimation on x {
                    from: -handle.width
                    to: background.width + handle.width
                    loops: Animation.Infinite
                    easing.type: Easing.OutInCirc
                    duration: 800
                }
            }
        }
    }
}
