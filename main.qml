import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Layouts 1.12
import Qt.labs.platform
import Qt.labs.settings
import "./components/"

Window {
    id: window
    width: 300
    height: 460
    visible: false
    flags: Qt.Popup

    Component.onCompleted: {
        // Reading oauthToken from Secrets
        lampsListModel.oauthToken = "y0_AgAAAABoWWAXAApIQQAAAADpY1xd2LVK5HyrSgqOUqrWuYcwxcs9JEU";
        lampsListModel.reload();

        yandexHome.checkConnection();
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            visible = false;
        }
    }

    Connections {
        target: yandexHome

        function onConnectionChecked(result) {
            if (result <= 0) {
//                trayIcon.showMessage("Нет инета", "Брат, инета нема (╯╭╮╰)");
//                lampTab.enabled = false;
            }
        }
    }

    Connections {
        target: yandexOAuth

        function onGranted() {
            console.log("Authorized with: " + yandexOAuth.getToken())


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

    Item {
        id: app
        anchors.fill: parent
        anchors.margins: 8

        TabBar {
            id: bar
            width: parent.width

            TabButton {
                text: "Лампочки"
            }

            TabButton {
                text: "Настройки"
            }
        }

        StackLayout {
            anchors.top: bar.bottom
            anchors.topMargin: 4
            width: parent.width
            currentIndex: bar.currentIndex

            Item {
                id: lampTab
                anchors.fill: parent

                Item {
                    id: lampComboBox
                    width: parent.width

                    anchors.top: parent.top
                    height: 25

                    ComboBox {
                        anchors.fill: parent

                        model: lampsListModel
                        textRole: "deviceName"
                    }
                }

                LampControl {
                    id: lampControls
                    width: parent.width

                    anchors.top: lampComboBox.bottom
                    anchors.topMargin: 5
                }

                LampColor {
                    id: colorControls
                    width: parent.width

                    anchors.top: lampControls.bottom
                    anchors.topMargin: 5
                    anchors.bottom: lampTab.bottom
                }
            }

            Item {
                id: settingsTab

                Button {
                    id: authButton
                    width: parent.width
                    text: "Авторизоваться через Яндекс ID"

                    onClicked: {
                        yandexOAuth.grant();
                    }
                }

                Item {
                    id: accountData

                    width: parent.width

                    anchors.top: authButton.bottom
                    anchors.topMargin: 10

                    Rectangle {
                        id: avatar
                        anchors.horizontalCenter: parent.horizontalCenter

                        width: 64
                        height: 64

                        color: "red"
                        radius: 45
                    }

                    Text {
                        id: name

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: avatar.bottom
                        anchors.topMargin: 7

                        text: "John Doe"
                    }

                    Button {
                        id: logoutButton
                        width: parent.width
                        text: "Выйти из аккаунта"

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: name.bottom
                        anchors.topMargin: 7

                        onClicked: {
                            yandexOAuth.grant();
                        }
                    }

                    Button {
                        id: reloginButton
                        width: parent.width
                        text: "Сменить аккаунт"

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: logoutButton.bottom
                        anchors.topMargin: 7

                        onClicked: {
                            yandexOAuth.grant();
                        }
                    }
                }
            }
        }
    }
}
