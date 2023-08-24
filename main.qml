import QtQuick
import QtQuick.Window
import QtQuick.Layouts 1.12
import Qt.labs.platform
import Qt.labs.settings
import "./components/" as Components
import "./pages" as Pages
import Yandex 1.0

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

    Component.onCompleted: {
        yandexAccount.askInfo();
    }

    onActiveChanged: {
        yandexHome.updateDevices();

        if (!active) {
            window.hide();
        }
    }

    Connections {
        target: yandexAccount

        function onInfoReady() {
            home.setAccountData(
                yandexAccount.getName(),
                "https://avatars.yandex.net/get-yapic/" + yandexAccount.getAvatarId() + "/islands-middle"
            );

            stack.currentIndex = 2;
        }

        function onError() {
            stack.currentIndex = 1;

            console.log("Error during log in");
        }
    }

    Connections {
        target: yandexOAuth

        function onGranted() {
            yandexOAuth.saveToken(yandexOAuth.getToken());
            yandexAccount.askInfo();
            yandexHome.loadDevices();

            stack.currentIndex = 2;
        }
    }

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/assets/icon.png"

        onActivated: function(reason) {
            yandexHome.updateDevices();

            if (reason !== SystemTrayIcon.Trigger)
                return;

            const position = desktopFeatures.getTaskbarPosition();

            const x0 = position.x;
            const y0 = position.y;
            const w = position.width;
            const h = position.height;

            if (y0 > 0 && x0 === 0) {
                window.x = Screen.desktopAvailableWidth - 20 - width
                window.y = Screen.desktopAvailableHeight - 5 - window.height
            } else if (y0 === 0 && x0 === 0 && w < h) {
                window.x = w + 5
                window.y = Screen.desktopAvailableHeight - height - 50
            } else if (y0 === 0 && x0 === 0 && h < w) {
                window.x = Screen.desktopAvailableWidth - width + Screen.virtualX - 50
                window.y = Screen.virtualY + h + 50
            } else {
                window.x = Screen.desktopAvailableWidth - width - 5
                window.y = Screen.desktopAvailableHeight - height - 50
            }

            if (!window.visible) {
                window.show();
                window.raise();
                window.requestActivate();
            } else {
                window.hide();
            }
        }

        menu: Menu {
            MenuItem {
                text: qsTr("Закрыть окно")
                onTriggered: Qt.quit()
            }

            MenuItem {
                text: qsTr("Github")
                onTriggered: Qt.openUrlExternally("https://github.com/Yagodnik/YandexLampTray")
            }
        }
    }

    StackLayout {
        id: stack
        anchors.fill: parent

        currentIndex: 0

        Pages.Loading {
            id: loading
        }

        Pages.Login {
            id: login
        }

        Pages.Home {
            id: home
        }
    }
}
