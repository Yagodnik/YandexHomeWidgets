import QtQuick
import QtQuick.Controls
import "../../components/ui" as Components
import Yandex 1.0

Item {
    id: delegate
    width: devicesGrid.width - 4
    height: 204
    clip: true

    Component.onCompleted: {
        if (!yandexHome.withId(deviceData["id"]).isColorsSupported()) {
            delegate.height = 58;
            temperaturePicker.visible = false;
            colorPicker.visible = false;
            minimizeButton.visible = false;
        }
    }

    state: "maximized"

    states: [
        State {
            name: "maximized"

            PropertyChanges {
                target: delegate
                height: 204
            }

            PropertyChanges {
                target: minimizeIcon
                rotation: -90
            }
        },

        State {
            name: "minimized"

            PropertyChanges {
                target: delegate
                height: 32
            }

            PropertyChanges {
                target: minimizeIcon
                rotation: 90
            }
        }
    ]

    transitions: Transition {
        PropertyAnimation {
            target: delegate
            properties: "height"
            easing.type: Easing.InOutSine
        }

        PropertyAnimation {
            target: minimizeIcon
            properties: "rotation"
            easing.type: Easing.InOutSine
        }
    }

    Rectangle {
        width: 3
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        color: "#00829e"
        radius: 3
    }

    Text {
        id: title
        color: "#1d1e1d"

        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.top: parent.top
        anchors.topMargin: 5

        verticalAlignment: Text.AlignVCenter

        font.family: textFont.font.family
        font.weight: textFont.font.weight
        font.pixelSize: 19

        text: deviceData["name"]

        ToolTip.delay: 700
        ToolTip.text: deviceData["fullName"]
        ToolTip.visible: deviceData["fullName"] ? tooltipMouseArea.containsMouse : false

        MouseArea {
            id: tooltipMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }

    Components.Switch {
        id: onOff

        width: 45
        height: 22

        anchors.left: title.right
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 6

        Binding on value {
            value: deviceData["state"]
        }

        onClicked: {
            yandexHome.setWatcherState(false);
            yandexHome.withId(deviceData["id"]).setState(value);
        }
    }

    Item {
        id: offlineMark
        width: 60
        height: 22

        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: onOff.right
        anchors.leftMargin: 15

        visible: !deviceData["online"]

        Rectangle {
            anchors.fill: parent
            color: "#e77fa2"
            radius: 45
        }

        Text {
            anchors.fill: parent
            text: "Не в сети"

            color: "#ecf9e6"

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.family: textFont.font.family
            font.weight: textFont.font.weight
            font.pixelSize: 9
        }
    }

    Item {
        id: minimizeButton
        width: 16
        height: 16

        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 6

        Image {
            id: minimizeIcon
            anchors.fill: parent
            source: "qrc:/assets/icons8-arrow-24.png"

            rotation: -90
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                delegate.state === "maximized" ? delegate.state = "minimized" :
                                                 delegate.state = "maximized";
            }
        }
    }

    Components.Slider {
        id: slider

        anchors.top: title.bottom
        anchors.topMargin: 10

        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 5

        sliderWidth: parent.width - 17

        height: 5

        value: 1

        Binding on value {
            value: deviceData["brightness"] / 100.0
        }

        onNewValue: {
            yandexHome.setWatcherState(false);
            yandexHome.withId(deviceData["id"]).setBrightness(value * 100);
        }
    }

    TemperaturesModel {
        id: temperaturesModel

        Component.onCompleted: {
            setLimits(yandexHome.withId(deviceData["id"]).getMinTemperature(),
                      yandexHome.withId(deviceData["id"]).getMaxTemperature());
        }
    }

    Components.ColorPicker {
        id: temperaturePicker

        model: temperaturesModel
        valueRole: "temperatureValue"
        displayRole: "displayColor"

        height: 30

        anchors.top: slider.bottom
        anchors.topMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 12

        onClicked: {
            yandexHome.withId(deviceData["id"]).setTemperature(currentColor);
        }
    }

    // Check if colors supported
    Components.ColorPicker {
        id: colorPicker

        model: colorModel

        anchors.top: temperaturePicker.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 12

        onClicked: {
            yandexHome.withId(deviceData["id"]).setColor(currentColor);
        }
    }
}
