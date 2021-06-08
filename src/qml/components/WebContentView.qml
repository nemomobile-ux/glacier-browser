import QtQuick 2.6
import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import QtWebEngine 1.0

Item{
    id: webWrapper

    property string url
    property alias title: realWeb.title
    property alias icon: realWeb.icon

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

    WebEngineView {
        id: realWeb
        anchors{
            fill: parent
            centerIn: parent
        }

        onUrlChanged: {
            if(url != webWrapper.url) {
                selfUrlChanged(realWeb.url)
            }
        }

        onLoadingChanged: {
            if(!loading) {
                historyModel.insertToHistory(realWeb.url,realWeb.title)
                if(tabModel.currentIndex == index) {
                    tabRepeater.title = realWeb.title
                }
            }
        }
    }

    Component.onCompleted: {
        selfUrlChanged(url)
    }

    function selfUrlChanged(url) {
        var editedUrl = url;

        var schemaFullUrl = /^(http|https):\/\/\w+\.\w+/;
        var schemaShortUrl = /^\w+\.\w+/;

        /*If url without http(s) add it */
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
        tabModel.changeTab(tabModel.currentIndex, editedUrl);
    }
}
