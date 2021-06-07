import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0



Page {

    property string addUrl: ""
    property string addTitle: ""
    property variant bookmarksModel

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Bookmarks")
        showBackButton: true
        tools: [
            ToolButton {
                iconSource: "image://theme/plus"
                onClicked: {
                    console.log("add bookmark: " + addUrl + " " + bookmarksModel)
                    bookmarksModel.insertToBookmarks(addUrl, addTitle)
                }
            }
        ]
    }


    ListView{
        id: bookmarksView
        model: bookmarksModel

        width: parent.width
        height: parent.height

        delegate: ListViewItemWithActions {
            label: title
            description: url
            showNext: true
            iconVisible: false
            width: parent.width
            height: Theme.itemHeightLarge

            onClicked: {
                console.log("load web page -- title:" + title + " " + url);
                tabModel.addTab(url)
                if (stackView) {
                    stackView.pop()
                }

            }

            actions:[
                ActionButton {
                    iconSource: "image://theme/times"
                    onClicked: {
                        bookmarksModel.removeFromBookmarks(url)
                    }
                }
            ]

        }
    }

}
