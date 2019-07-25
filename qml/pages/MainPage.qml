import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0

import "../components"


Page {
    id: mainPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Browser")

        tools: [
            ToolButton {
                iconSource: "image://theme/clone"
            },
            ToolButton {
                iconSource: "image://theme/bookmark"
            }
        ]
    }

    Column{
        anchors.fill: parent
        AddressLine{
            id: addressLine
        }

        WebContentView{
            id: webContent
            width: parent.width
            height: parent.height - addressLine.height
        }
    }

    Connections{
        target: addressLine
        onUrlReady: {
            webContent.url = url
        }
    }
}
