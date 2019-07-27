import QtQuick 2.6
import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import QtWebKit 3.0

Item{
    id: webWrapper

    property string url
    property alias title: realWeb.title
    signal selfUrlChanged(string url)

    MouseArea{
        anchors.fill: parent
        onPressAndHold: {
            if(realWeb.state == "normalView") {
               realWeb.state = "subCloseView"
            }
        }
        onClicked: {
            if(realWeb.state == "subCloseView") {
                realWeb.state = "normalView"
            }
        }
    }

    ProgressBar {
        anchors{
            top: parent.top
        }

        width: parent.width
        height: Theme.itemHeightExtraSmall/2
        value: realWeb.loadProgress/100
        visible: realWeb.loading
        z: 2
    }

    WebView {
        id: realWeb
        anchors{
            fill: parent
            centerIn: parent
        }

        state: "normalView"

        Behavior on width {
            NumberAnimation { duration: 900; easing.type: Easing.OutCubic }
        }
        Behavior on height {
            NumberAnimation { duration: 900; easing.type: Easing.OutCubic }
        }

        onUrlChanged: {
            if(url != webWrapper.url) {
                selfUrlChanged(realWeb.url)
            }
        }

        onLoadingChanged: {
            if(!loading) {
                historyModel.insertToHistory(realWeb.url,realWeb.title)
            }
        }

        states: [
            State {
                name: "normalView"
                PropertyChanges {
                    target: realWeb
                    width: parent.width
                }
                PropertyChanges {
                    target: realWeb
                    height: parent.height
                }
                PropertyChanges {
                    target: realWeb
                    scale: 1
                }
            },
            State {
                name: "subCloseView"

                PropertyChanges {
                    target: realWeb
                    width: parent.width*0.8
                }
                PropertyChanges {
                    target: realWeb
                    height: parent.height*0.8
                }
                PropertyChanges {
                    target: realWeb
                    scale: 0.8
                }
            }
        ]
    }

    onUrlChanged: {
        var editedUrl = url;

        var schemaFullUrl = /^(http|https):\/\/\w+\.\w+/;
        var schemaShortUrl = /^\w+\.\w+/;

        /If url without http(s) add it */
        if(schemaFullUrl.test(url)) {
            editedUrl = url
        }
        else if(schemaShortUrl.test(url)) {
            editedUrl = "https://"+url
        }
        //If url is just text format duckduckgo search requirest
        //TODO: add into settings it!
        else {
            editedUrl = "https://duckduckgo.com/?q="+url.split("+")+"&t=nemomobile&ia=web"
        }

        realWeb.url = editedUrl;
    }


    Image {
        id: closeBtn
        source: "image://theme/times-circle"
        x: parent.width-(parent.width*0.16)
        y: parent.height-(parent.height*0.16)
        visible: realWeb.state == "subCloseView"
    }
}
