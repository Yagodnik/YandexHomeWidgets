import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Layouts 1.12
import Qt.labs.platform
import Qt.labs.settings
import QtQuick.Shapes 1.5
import "./components/" as Components
import Yandex 1.0
import QtQml
import Qt5Compat.GraphicalEffects

Window {
    id: window
    title: "YandexTrayApp"
    width: 300
    height: 365
    visible: false
    flags: Qt.FramelessWindowHint
    color: "transparent"

    DevicesModel {
        id: devicesModel
    }

    YandexHome {
        id: yandexHome

        Component.onCompleted: {
            loadDevices();
        }
    }

    FontLoader {
        id: textFont
        source: "qrc:/assets/Montserrat-SemiBold.ttf"
    }

    Rectangle {
        anchors.fill: parent
        color: "#ecf9e6"
        radius: 3
    }

    onActiveChanged: {
        yandexHome.updateDevices();

        if (!active) {
            window.hide();
        }
    }

//    Connections {
//        target: yandexOAuth

//        function onGranted() {
//            console.log("Authorized with: " + yandexOAuth.getToken())

//            yandexOAuth.saveToken(yandexOAuth.getToken());
//            startupCheck();
//            trayIcon.showMessage("Вы авторизовались в аккаунт!", "Успех крч");
//        }
//    }

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/assets/icon.png"

        onActivated: {
            yandexHome.updateDevices();

            window.x = Screen.desktopAvailableWidth - 20 - width + Screen.virtualX
            window.y = Screen.desktopAvailableHeight - 5 - height + Screen.virtualY

            if (!window.visible) {
                window.show();
                window.raise();
                window.requestActivate();
            } else {
                window.hide();
            }
        }
    }

    Item {
        id: app
        anchors.fill: parent
        anchors.margins: 3

        Components.Panel {
            id: appbar

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            height: 60

            Components.Avatar {
                id: icon

                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter

//                source: "https://avatars.mds.yandex.net/get-yapic/0/0-0/islands-retina-small"
                source: "qrc:/assets/icon.png"
            }

            Text {
                height: 32

                color: "#1d1e1d"

                anchors.left: icon.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter

                verticalAlignment: Text.AlignVCenter

                font.family: textFont.font.family
                font.weight: textFont.font.weight
                font.pixelSize: 16

                text: "Yandex Account"
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

                    anchors.fill: parent

                    cellWidth: parent.width
                    cellHeight: 140

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
                            font.pixelSize: 20

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
                        }

                        GridView {
                            id: colorsGrid
                            interactive: false

                            anchors.top: slider.bottom
                            anchors.topMargin: 12
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.leftMargin: 12
                            anchors.right: parent.right
                            anchors.rightMargin: 12

                            cellWidth: 34
                            cellHeight: 34

                            delegate: Rectangle {
                                id: delegate
                                color: "red"
                                width: colorsGrid.cellWidth - 4
                                height: colorsGrid.cellHeight - 4

                                radius: 3

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true

                                    onContainsMouseChanged: {
                                        delegate.state === "hover" ? delegate.state = "noHover" : delegate.state = "hover";
                                    }
                                }

                                states: [
                                    State {
                                        name: "noHover"

                                        PropertyChanges {
                                            target: delegate
                                            radius: 5
                                        }
                                    },

                                    State {
                                        name: "hover"

                                        PropertyChanges {
                                            target: delegate
                                            radius: 8
                                        }
                                    }
                                ]

                                transitions: Transition {
                                    PropertyAnimation {
                                        target: delegate
                                        properties: "radius"
                                        easing.type: Easing.InOutSine
                                    }
                                }
                            }

                            model: ListModel {
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                                ListElement {}
                            }
                        }
                    }
                }
            }
        }
    }
}
