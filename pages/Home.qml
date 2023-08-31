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
                interactive: true
                clip: true

                anchors.fill: parent

                cellWidth: parent.width
                cellHeight: 204

                model: devicesModel
                delegate: Item {
                    id: delegate
                    width: devicesGrid.cellWidth - 4
                    height: devicesGrid.cellHeight - 4
                    clip: true

                    state: "maximized"

                    states: [
                        State {
                            name: "maximized"

                            PropertyChanges {
                                target: delegate
                                height: devicesGrid.cellHeight - 4
                            }

                            PropertyChanges {
                                target: minimizeIcon
                                rotation: -90
                            }
                        },

                        State {
                            name: "minimized"

                            PropertyChanges {
                                target: delegate
                                height: 32
                            }

                            PropertyChanges {
                                target: minimizeIcon
                                rotation: 90
                            }
                        }
                    ]

                    transitions: Transition {
                        PropertyAnimation {
                            target: delegate
                            properties: "height"
                            easing.type: Easing.InOutSine
                        }

                        PropertyAnimation {
                            target: minimizeIcon
                            properties: "rotation"
                            easing.type: Easing.InOutSine
                        }
                    }

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

                        value: deviceState

                        onClicked: {
                            yandexHome.setState(deviceId, value);
                        }
                    }

                    Item {
                        id: minimizeButton
                        width: 16
                        height: 16

                        anchors.right: parent.right
                        anchors.rightMargin: 8
                        anchors.top: parent.top
                        anchors.topMargin: 6

                        Image {
                            id: minimizeIcon
                            anchors.fill: parent
                            source: "qrc:/assets/icons8-arrow-24.png"

                            rotation: -90
                        }

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                delegate.state === "maximized" ? delegate.state = "minimized" :
                                                                 delegate.state = "maximized";
                            }
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

                        sliderWidth: parent.width - 17

                        height: 5

                        value: deviceBrightness / 100.0

                        onNewValue: {
                            yandexHome.setBrightness(deviceId, value * 100);
                        }
                    }

                    Components.ColorPicker {
                        id: temperaturePicker

                        model: temperaturesModel
                        valueRole: "temperatureValue"
                        displayRole: "displayColor"

                        height: 30

                        anchors.top: slider.bottom
                        anchors.topMargin: 12
                        anchors.left: parent.left
                        anchors.leftMargin: 12
                        anchors.right: parent.right
                        anchors.rightMargin: 12

                        onClicked: {
                            yandexHome.setTemperature(deviceId, currentColor);
                        }
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

                        onClicked: {
                            yandexHome.setColor(deviceId, currentColor);
                        }
                    }
                }
            }
        }
    }
}

