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

    AddressLine{
        id: addressLine
        z: 2
        anchors{
            top: parent.top
            left: parent.left
        }
    }

    ListView{
        id: historySearch
        model: historyModel
        anchors{
            top: addressLine.bottom
        }
        z: 2
        width: parent.width
        height: parent.height-addressLine.height

        delegate: ListViewItemWithActions {
            label: title
            description: url
            showNext: true
            iconVisible: false
            width: parent.width
            height: Theme.itemHeightLarge

            onClicked: {
                webContent.url = url
                addressLine.addressLineText = url
                historyModel.searchClear();
            }

            actions:[
                ActionButton {
                    iconSource: "image://theme/times"
                    onClicked: historyModel.removeFromHistory(url)
                }
            ]
        }
        Rectangle{
            color: "black"
            width: parent.width
            height: Theme.itemHeightLarge*historySearch.count
            anchors.top: parent.top
            z: -1
        }
    }

    WebContentView{
        id: webContent
        width: parent.width
        height: parent.height - addressLine.height
        z: 1
        anchors.top: addressLine.bottom
    }


    Connections{
        target: addressLine
        onUrlReady: {
            webContent.url = url
        }
    }

    Connections{
        target: webContent
        onSelfUrlChanged: {
            addressLine.addressLineText = url
        }

        onTitleChanged:{
            tools.title = webContent.title
        }
    }
}
