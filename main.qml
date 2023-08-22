import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Layouts 1.12
import Qt.labs.platform
import Qt.labs.settings
import QtQuick.Shapes 1.5
//import "./components/"
import "./circularSlider"

Window {
    id: window
    title: "YandexTrayApp"
    width: 300
    height: 365
    visible: false
    flags: Qt.FramelessWindowHint
    color: "transparent"

    FontLoader {
        id: textFont
        source: "qrc:/assets/Montserrat-SemiBold.ttf"
    }

    Rectangle {
        color: "#E8E9EB"
        radius: 20
        anchors.fill: parent
    }

    function startupCheck() {
        yandexAccount.askInfo();

        yandexHome.getAllDevices(lampsListModel);

        accountData.enabled = true;
    }

    Component.onCompleted: {
        startupCheck();
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            visible = false;
        }
    }

    Connections {
        target: yandexHome

        function onDevicesLoaded(result) {
            if (result < 0) {
                trayIcon.showMessage("Нет инета", "Брат, инета нема (╯╭╮╰)");
                lampTab.enabled = false;
            } else if (result === 0) {
                trayIcon.showMessage("Нет ламп", "Брат, ламп нема (╯╭╮╰)");
                lampTab.enabled = false;
            } else {
                lampTab.enabled = true;

                // Generating list of lamps
            }
        }

        function onLampError(deviceId) {
            trayIcon.showMessage("Ошибка!", "Не удалось отправить запрос лампочке!");
        }
    }

    Connections {
        target: yandexOAuth

        function onGranted() {
            console.log("Authorized with: " + yandexOAuth.getToken())

            yandexOAuth.saveToken(yandexOAuth.getToken());
            startupCheck();
            trayIcon.showMessage("Вы авторизовались в аккаунт!", "Успех крч");
        }
    }

    Connections {
        target: yandexAccount

        function onInfoReady() {
            name.text = yandexAccount.getName();

            authButton.enabled = false;
            logoutButton.enabled = true;
            reloginButton.enabled = true;
        }

        function onError() {
            trayIcon.showMessage("Ошибка", "Не удалось войти в аккаунт!");
//            accountData.enabled = false;

            authButton.enabled = true;
            logoutButton.enabled = false;
            reloginButton.enabled = false;
        }
    }

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/assets/icon.png"

        onActivated: {
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

    Flickable {
        id: app
        anchors.fill: parent
        anchors.margins: 8
        clip: true

        Item {
            id: appbar

            anchors.top: parent.top

            anchors.left: parent.left
            anchors.right: parent.right
            height: 60

            Rectangle {
                anchors.fill: parent
                color: "#4D7298"
                opacity: 0.68
                radius: 5
            }

            Image {
                id: icon

                width: 32
                height: 32

                anchors.left: parent.left
                anchors.leftMargin: 12
                anchors.verticalCenter: parent.verticalCenter

                source: "https://avatars.mds.yandex.net/get-yapic/0/0-0/islands-retina-small"
            }

            Text {
                height: 32

                color: "#E8E9EB"

                anchors.left: icon.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter

                verticalAlignment: Text.AlignVCenter

                font.family: textFont.font.family
                font.weight: textFont.font.weight
                font.pixelSize: 18

                text: "Yandex Account"
            }

            Image {
                id: logoutButtom

                width: 32
                height: 32

                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.verticalCenter: parent.verticalCenter

                source: "qrc:/assets/logout.png"
            }
        }

        GridView {
            id: grid

            anchors.top: appbar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.topMargin: 5

            cellWidth: parent.width
            cellHeight: 160

            delegate: Item {
                width: grid.cellWidth - 4
                height: grid.cellHeight - 4

                Rectangle {
                    anchors.fill: parent
                    color: "#4D7298"
                    opacity: 0.68
                    radius: 5
                }

                Image {
                    id: icon2

                    width: 38
                    height: 38

                    anchors.top: parent.top
                    anchors.left: parent.left

                    anchors.topMargin: 6
                    anchors.leftMargin: 8

                    source: "qrc:/assets/lamp.png"
                }

                Text {
                    height: 32

                    color: "#E8E9EB"

                    anchors.top: parent.top
                    anchors.left: icon2.right

                    anchors.topMargin: 8
                    anchors.leftMargin: 4

                    verticalAlignment: Text.AlignVCenter

                    font.family: textFont.font.family
                    font.weight: textFont.font.weight
                    font.pixelSize: 18

                    text: deviceName
                }


                Switch {
                    id: control

                    anchors.top: parent.top
                    anchors.right: parent.right

                    anchors.topMargin: 8
                    anchors.rightMargin: 4

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 20
                        x: control.leftPadding
                        y: parent.height / 2 - height / 2
                        radius: 13
                        color: control.checked ? "#EC7357" : "#ffffff"
                        border.color: control.checked ? "#EC7357" : "#cccccc"

                        Rectangle {
                            x: control.checked ? parent.width - width : 0
                            width: 20
                            height: 20
                            radius: 13
                            color: control.down ? "#cccccc" : "#ffffff"
                            border.color: control.checked ? (control.down ? "#EC7357" : "#EC7357") : "#999999"
                        }
                    }
                }

                Slider {
                    id: control2

                    value: 0.5
                    live: false

                    anchors.top: control.bottom
                    anchors.topMargin: 4

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 4
                    anchors.rightMargin: 4

                    background: Rectangle {
                        x: control2.leftPadding
                        y: control2.topPadding + control2.availableHeight / 2 - height / 2
                        implicitWidth: 200
                        implicitHeight: 20
                        width: control2.availableWidth
                        height: implicitHeight
                        radius: 13
                        color: "#E8E9EB"

                        Flickable {
                            clip: true
                            width: control2.visualPosition * parent.width
                            height: parent.height

                            Rectangle {
                                anchors.fill: parent

                                color: "#EC7357"
                                radius: 13
                            }
                        }
                    }

                    handle: Rectangle {
                        x: control2.leftPadding + control2.visualPosition * (control2.availableWidth - width)
                        y: control2.topPadding + control2.availableHeight / 2 - height / 2
                        implicitWidth: 20
                        implicitHeight: 20
                        radius: 13
                        color: control2.pressed ? "#f0f0f0" : "#f6f6f6"
                        border.color: "#EC7357"
                    }
                }
            }

            model: lampsListModel
        }
    }
}
