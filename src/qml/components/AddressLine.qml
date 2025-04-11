import QtQuick
import Nemo
import Nemo.Controls

Item {
    id: addressLine
    width: parent.width

    signal urlReady(string url)
    property alias addressLineText: urlLine.text

    height: childrenRect.height+Theme.itemSpacingLarge*2

    TextField {
        id: urlLine
        width: parent.width-Theme.itemSpacingLarge*2
        height: Theme.itemHeightExtraLarge-Theme.itemSpacingLarge*2
        anchors{
            top: parent.top
            topMargin: Theme.itemSpacingLarge
            left: parent.left
            leftMargin: Theme.itemSpacingLarge
        }
        inputMethodHints: Qt.ImhNoAutoUppercase
        placeholderText: qsTr("Search")

        onTextChanged: {
            if(urlLine.length>0) {
                urlLine.forceActiveFocus()
            }

            if(!urlLine.text.startsWith("http")) {
                /*Need something another*/
                var cleanedString = urlLine.text.replace(/http?s?:?\/{0,2}/gm,'');

                if(cleanedString.length>2) {
                    console.log("Search in history: " + cleanedString)
                    historyModel.historySearch = cleanedString
                }
                else {
                    historyModel.historySearch = "";
                }
            } else {
                historyModel.historySearch = "";
            }
        }

        onAccepted: {
            tabModel.addTab(urlLine.text)
            focus = false
            historyModel.searchClear();
        }
    }

    onAddressLineTextChanged: {
        if(!urlLine.focus) {
            urlLine.cursorPosition = 0
        }
    }

    Connections {
        target: tabModel
        function onTabChanged(idx, url) {
            if(idx === tabModel.currentIndex) {
                urlLine.text = url
            }
        }
    }
}
