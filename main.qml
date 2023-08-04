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

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            visible = false;
        }
    }

    Settings {
        id: settings
        fileName: "configuration"
        category: "auth"

        property string oauthToken: "y0_AgAAAABoWWAXAAkYVAAAAADbapjdlX9c2HyXS-60YHmLVZJj8AhQmtM"

        Component.onCompleted: {
            lampsListModel.oauthToken = oauthToken;
            lampsListModel.reload();
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
                    width: parent.width
                    text: "Авторизоваться через Яндекс ID"
                }
            }
        }
    }
}
