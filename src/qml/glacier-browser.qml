import QtQuick 2.6
import QtQuick.Window 2.1

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.browser 1.0

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
