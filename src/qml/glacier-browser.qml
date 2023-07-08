import QtQuick
import Nemo.Controls
import org.glacier.browser

import "pages"

ApplicationWindow{
    id: main
    initialPage: MainPage{}
    contentOrientation: Screen.orientation
    allowedOrientations:  Qt.PortraitOrientation | Qt.LandscapeOrientation | Qt.InvertedLandscapeOrientation | Qt.InvertedPortraitOrientation


    HistoryModel{
        id: historyModel
    }

    TabModel{
        id: tabModel
    }

    BookmarksModel {
        id: bookmarksModel
    }

}
