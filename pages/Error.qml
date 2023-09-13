import QtQuick 2.15
import "../components/ui" as Components

Item {
    id: errorPage

    Text {
        height: 26

        color: "#1d1e1d"

        anchors.bottom: tryAgainButton.top
        anchors.horizontalCenter: parent.horizontalCenter

        horizontalAlignment: Text.AlignHCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 12

        text: "Не удалось войти в аккаунт Яндекс!"
    }

    Components.Button {
        id: tryAgainButton

        text: "Попробовать ещё раз"

        width: 180
        height: 28

        anchors.centerIn: parent

        onClicked: {
            yandexAccount.askInfo();
            stack.currentIndex = 0;
        }
    }
}
