import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0

Item {
    id: addressLine
    width: parent.width
    height: Theme.itemHeightExtraLarge

    signal urlReady(string url)
    property alias addressLineText: urlLine.text


    TextField {
        id: urlLine
        width: parent.width-Theme.itemSpacingLarge*2
        height: parent.height-Theme.itemSpacingLarge*2
        anchors{
            top: parent.top
            topMargin: Theme.itemSpacingLarge
            left: parent.left
            leftMargin: Theme.itemSpacingLarge
        }
        inputMethodHints: Qt.ImhNoAutoUppercase
        placeholderText: qsTr("Search")

        onTextChanged: {
            if(urlLine.text.lenght>0) {
                urlLine.forceActiveFocus()
            }
        }

        onAccepted: {
            urlReady(urlLine.text)
            focus = false
        }
    }

    onAddressLineTextChanged: {
        if(!urlLine.focus) {
            urlLine.cursorPosition = 0
        }
    }
}
