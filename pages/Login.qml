import QtQuick 2.15
import "../components" as Components

Item {
    id: loginPage

    Text {
        height: 32

        color: "#1d1e1d"

        anchors.bottom: loginButton.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter

        horizontalAlignment: Text.AlignHCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 12

        text: "Чтобы приложение могло найти лампы\n необходимо войти в аккаунт"
    }

    Components.Button {
        id: loginButton

        text: "Войти в аккаунт Яндекс"

        width: 180
        height: 28

        anchors.centerIn: parent

        onClicked: {
            yandexOAuth.grant();
        }
    }
}
