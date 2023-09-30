import QtQuick
import Qt5Compat.GraphicalEffects

Rectangle {
    id: icon

    property string source: ""

    radius: 45
    color: "#dae8dc"
    width: iconImage.width + 4
    height: iconImage.height + 4

    Image {
        id: iconImage
        anchors.centerIn: parent

        width: 32
        height: 32

        source: icon.source
        fillMode: Image.PreserveAspectCrop
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: icon
        }
    }
}
