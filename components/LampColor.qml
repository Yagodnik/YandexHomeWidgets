import QtQuick 2.0
import QtQuick.Controls.Fusion
import QtQuick.Layouts 1.12

GroupBox {
    title: "Выбор цвета"

    GridLayout {
        id: grid
        anchors.fill: parent

        columns: 5
        rows: 5

        Repeater {
            model: lampColors.getColorsCount()

            Item {
                width: (window.width - 50) / grid.columns
                height: width

                Rectangle {
                    radius: 5
                    anchors.fill: parent
                    color: lampColors.getColorHex(index)
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        lamp.setColor(lampColors.getColorRgb(index));
                    }
                }
            }
        }
    }
}

