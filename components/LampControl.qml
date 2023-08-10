import QtQuick 2.0
import QtQuick.Controls.Fusion
import QtQuick.Layouts 1.12

GroupBox {
    title: "Управление"

    Column {
        anchors.fill: parent
        spacing: 4

        RowLayout {
            width: parent.width

            Button {
                icon.source: "qrc:/assets/lamp_on.png"
                text: "Вкл"
                Layout.fillWidth: true

                onClicked: {
                    // Check if it undefiend

                    yandexHome.on(currentLamp.currentValue);
                }
            }

            Button {
                icon.source: "qrc:/assets/lamp_off.png"
                text: "Выкл"
                Layout.fillWidth: true

                onClicked: {
                    yandexHome.off(currentLamp.currentValue);
                }
            }
        }

        RowLayout {
            width: parent.width

            Text {
                text: "Яркость"
            }

            Slider {
                from: 1
                to: 100
                value: 25
                stepSize: 1
                live: false

                Layout.fillWidth: true

                onValueChanged: {
                    yandexHome.setBrightness(currentLamp.currentValue, value);
                }
            }
        }
    }
}
