import QtQuick 2.15
import QtQuick.Controls 2.4
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

            property string toolTipText: text
            ToolTip.delay: 700
            ToolTip.text: toolTipText
            ToolTip.visible: toolTipText ? tooltipMouseArea.containsMouse : false

            MouseArea {
                id: tooltipMouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
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

            ListView {
                id: devicesGrid
                interactive: true
                clip: true
                spacing: 5

                anchors.fill: parent

//                cellWidth: parent.width
//                cellHeight: 204

//                ScrollBar.vertical: ScrollBar {
//                    id: control
//                    visible: true
//                    active: true
//                    size: 0.1
//                    height: devicesGrid.availableHeight

//                    contentItem: Rectangle {
//                       implicitWidth: 6
//                       implicitHeight: 20
//                       radius: width / 2
//                       color: control.pressed ? "#81e889" : "#c2f4c6"
//                       // Hide the ScrollBar when it's not needed.
//                       opacity: control.policy === ScrollBar.AlwaysOn || (control.active && control.size < 1.0) ? 0.75 : 0

//                       // Animate the changes in opacity (default duration is 250 ms).
//                       Behavior on opacity {
//                           NumberAnimation {}
//                       }
//                   }
//                }

                model: devicesModel
                delegate: Item {
                    id: delegate
                    width: devicesGrid.width - 4
                    height: 204
                    clip: true

                    state: "maximized"

                    states: [
                        State {
                            name: "maximized"

                            PropertyChanges {
                                target: delegate
                                height: 204
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
                        id: offlineMark
                        width: 60
                        height: 22

                        anchors.top: parent.top
                        anchors.topMargin: 6
                        anchors.left: onOff.right
                        anchors.leftMargin: 15

                        Rectangle {
                            anchors.fill: parent
                            color: "#e77fa2"
                            radius: 45
                        }

                        Text {
                            anchors.fill: parent
                            text: "Не в сети"

                            color: "#ecf9e6"

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter

                            font.family: textFont.font.family
                            font.weight: textFont.font.weight
                            font.pixelSize: 9
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
                        anchors.topMargin: 10

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

