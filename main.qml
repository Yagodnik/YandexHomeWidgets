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
    flags: Qt.FramelessWindowHint | Qt.Popup
    color: "transparent"

    property bool canShowPopup: true

    Timer {
        id: doubleClickTimer
        interval: desktopFeatures.getDoubleclickTime()
        running: false
        repeat: false

        onTriggered: {
            window.canShowPopup = true;
        }
    }

    function show_window() {
        console.log(window.canShowPopup)

        if (window.canShowPopup) {
            window.show();
            window.raise();
            window.requestActivate();
        }
    }

    function hide_window() {
        window.hide();
        window.canShowPopup = false;
        doubleClickTimer.start();
    }

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

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            hide_window();
        }
    }

    onVisibleChanged: {
        yandexHome.setWatcherState(visible);
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

        function onError(errorCode) {
            switch (errorCode) {
            case 2:
                stack.currentIndex = 3;
                break;
            case 1:
                stack.currentIndex = 1;
                break;
            case 0:
                stack.currentIndex = 3;
                break;
            }
        }
    }

    Connections {
        target: yandexOAuth

        function onGranted() {
            yandexOAuth.saveToken(yandexOAuth.getToken());
            yandexHome.loadDevices();
            yandexAccount.askInfo();

            stack.currentIndex = 2;
        }
    }

    SystemTrayIcon {
        id: trayIcon
        visible: true
        icon.source: "qrc:/assets/icon.png"

        onActivated: function(reason) {
            if (reason !== SystemTrayIcon.Trigger)
                return;

            const position = desktopFeatures.getTaskbarPosition();

            const x0 = position.x;
            const y0 = position.y;
            const w = position.width;
            const h = position.height;

            if (y0 > 0 && x0 === 0) {
                window.x = geometry.x - window.width / 2 + geometry.width;
                window.y = geometry.y - window.height - 5;
            } else if (y0 === 0 && x0 === 0 && w < h) {
                window.x = geometry.x + w + 5;
                window.y = geometry.y - window.height / 2 - geometry.height;
            } else if (y0 === 0 && x0 === 0 && h < w) {
                window.x = geometry.x - window.width / 2 + geometry.width;
                window.y = geometry.y + 15 + h;
            } else {
                window.x = geometry.x - window.width - 15;
                window.y = geometry.y - window.height / 2 - geometry.height;
            }

            if (!window.visible) {
                show_window();
            } else {
                hide_window();
            }
        }

        menu: Menu {
            MenuItem {
                text: qsTr("Закрыть приложение")
                onTriggered: Qt.quit()
            }

            MenuItem {
                text: qsTr("Github")
                onTriggered: Qt.openUrlExternally("https://github.com/Yagodnik/YandexLampApp")
            }
        }
    }

    StackLayout {
        id: stack
        anchors.fill: parent
        anchors.margins: 3

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

        Pages.Error {
            id: error
        }
    }
}
