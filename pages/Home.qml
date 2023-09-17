import QtQuick 2.15
import "../components/ui" as Components
import "../components/app" as App

Item {
    id: appPage

    function setAccountData(name, avatar) {
        appbar.setAccountData(name, avatar);
    }

    App.Header {
        id: appbar
    }

    Components.Panel {
        anchors.top: appbar.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        App.DevicesHeader {
            id: header
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

                model: devicesModel
                delegate: Component {
                    Loader {
                        source: switch(deviceType) {
                            case "devices.types.light": return "qrc:/components/delegates/LightDelegate.qml"
                        }
                    }
                }
            }

            Connections {
                target: yandexHome

                function onDevicesLoaded(result) {
                    devicesGrid.visible = devicesModel.rowCount() > 0;
                    noDevicesMessage.visible = (devicesModel.rowCount() === 0);
                }
            }

            Item {
                id: noDevicesMessage

                anchors.fill: parent

                Text {
                    color: "#1d1e1d"

                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter

                    font.family: textFont.font.family
                    font.weight: textFont.font.weight
                    font.pixelSize: 16

                    text: "У вас нет устройств!"
                }
            }
        }
    }
}

