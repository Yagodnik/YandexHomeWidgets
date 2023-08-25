import QtQuick 2.15
import "../components" as Components

Item {
    id: appPage

    function setAccountData(name, avatar) {
        accountName.text = name;
        accountPic.source = avatar;
    }

    Components.Panel {
        id: appbar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 60

        Components.Avatar {
            id: accountPic

            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: accountName
            height: 32

            color: "#1d1e1d"

            anchors.left: accountPic.right
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter

            verticalAlignment: Text.AlignVCenter

            font.family: textFont.font.family
            font.weight: textFont.font.weight
            font.pixelSize: 16
        }

        Components.Button {
            id: logoutButton

            text: "Выйти"

            width: 64
            height: 28

            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Components.Panel {
        anchors.top: appbar.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

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

                text: "Ваши девайсы"
            }

            Components.Button {
                id: updateButton

                text: "Обновить"

                width: 90
                height: 28

                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Components.Splitter {
            id: splitter
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 3
            anchors.leftMargin: 12
            anchors.rightMargin: 12
        }

        Item {
            anchors.top: splitter.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 5
            anchors.leftMargin: 12
            anchors.rightMargin: 3
            anchors.bottom: parent.bottom

            GridView {
                id: devicesGrid
                interactive: false

                anchors.fill: parent

                cellWidth: parent.width
                cellHeight: 170

                model: devicesModel
                delegate: Item {
                    width: devicesGrid.cellWidth - 4
                    height: devicesGrid.cellHeight - 4

                    Rectangle {
                        width: 3
                        height: parent.height - 16
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

                        text: deviceName
                    }

                    Components.Switch {
                        id: onOff

                        width: 45
                        height: 22

                        anchors.left: title.right
                        anchors.leftMargin: 8
                        anchors.top: parent.top
                        anchors.topMargin: 6

                        onClicked: {
                            yandexHome.setState(deviceId, value);
                        }
                    }

                    Components.Slider {
                        id: slider

                        anchors.top: title.bottom
                        anchors.topMargin: 8
                        anchors.left: parent.left
                        anchors.leftMargin: 12

                        anchors.right: parent.right
                        anchors.rightMargin: 5

                        height: 5

                        onNewValue: {
                            yandexHome.setBrightness(deviceId, value * 100);
                        }
                    }

                    Components.ColorPicker {
                        id: temperaturePicker

                        model: temperaturesModel

                        height: 30

                        anchors.top: slider.bottom
                        anchors.topMargin: 12
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        anchors.right: parent.right
                        anchors.rightMargin: 12
                    }

                    Components.ColorPicker {
                        id: colorPicker

                        model: colorModel

                        anchors.top: temperaturePicker.bottom
                        anchors.topMargin: 5
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        anchors.right: parent.right
                        anchors.rightMargin: 12
                    }
                }
            }
        }
    }
}

