import QtQuick
import QtQuick.Controls
import "../ui" as Components

Components.Panel {
    id: appbar

    function setAccountData(name, avatar) {
        accountName.text = name;
        accountPic.source = avatar;
    }

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

        onClicked: {
            yandexOAuth.logout();
            stack.currentIndex = 0;
            yandexHome.clearDevices();
            yandexAccount.askInfo();
        }
    }
}
