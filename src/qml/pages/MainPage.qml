import QtQuick
import Nemo.Controls

import "../components"

Page {
    id: mainPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: (tabRepeater.itemAt(tabModel.currentIndex) !== null) ? tabRepeater.itemAt(tabModel.currentIndex).title : qsTr("Browser")

        tools: [
            ToolButton {
                iconSource: "image://theme/clone"
                showCounter: true
                counterValue: tabModel.rowCount
                onClicked: {
                    mainPage.Stack.view.push(Qt.resolvedUrl("TabPage.qml"), {repeaterObject: tabRepeater})

                }
            },
            ToolButton {
                iconSource: "image://theme/bookmark"
                onClicked: {
                    mainPage.Stack.view.push(
                                Qt.resolvedUrl("Bookmarks.qml"),
                                {
                                    bookmarksModel: bookmarksModel,
                                    addUrl: addressLine.addressLineText,
                                    addTitle: tools.title,
                                    addIcon: (tabRepeater.itemAt(tabModel.currentIndex) !== null) ? tabRepeater.itemAt(tabModel.currentIndex).icon : ''
                                })
                }
            }
        ]
    }

    AddressLine{
        id: addressLine
        z: historySearch.z + 1
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
        z: 1000
        width: parent.width
        height: parent.height-addressLine.height
        visible: (historySearch.count > 0)

        delegate: ListViewItemWithActions {
            label: title
            description: url
            showNext: true
            iconVisible: false
            width: (parent !== null) ? parent.width : 0
            height: Theme.itemHeightLarge

            onClicked: {
                tabModel.addTab(url)
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
            color: Theme.backgroundColor
            width: parent.width
            height: Theme.itemHeightLarge*historySearch.count
            anchors.top: parent.top
            z: -1
        }
    }


    Repeater{
        id: tabRepeater
        width: parent.width
        height: parent.height - addressLine.height
        z: 1

        model: tabModel

        WebContentView{
            id: webContent
            width: parent.width
            height: parent.height - addressLine.height
            anchors.top: addressLine.bottom
            url: modelData
            visible: (index === tabModel.currentIndex);
        }

    }

    Binding {
        target: addressLine; property: "addressLineText";
        value: (tabRepeater.itemAt(tabModel.currentIndex) !== null) ?  tabRepeater.itemAt(tabModel.currentIndex).url : '';
    }

    Connections{
        target: addressLine
        function onUrlReady(url) {
            webContent.url = url
        }
    }


}
