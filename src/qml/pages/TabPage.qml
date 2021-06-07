import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0



Page {
    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Tabs")
        showBackButton: true
    }


    ListView{
        id: tabsView
        model: tabModel

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
                console.log("tabModel.setCurrentIndex("+index+");");
                tabModel.setCurrentIndex(index);
            }

            actions:[
                ActionButton {
                    iconSource: "image://theme/times"
                    onClicked: {
                        console.log("tabModel.removeTab(" + index + ")")
                        tabModel.removeTab(index)
                    }
                }
            ]

        }
    }

}
