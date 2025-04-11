#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtGui/QGuiApplication>

#include <QScreen>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtWebEngineQuick>

#include <glacierapp.h>

#include "bookmarksmodel.h"
#include "historymodel.h"
#include "tabmodel.h"

Q_DECL_EXPORT int main(int argc, char* argv[])
{
    QGuiApplication* app = GlacierApp::app(argc, argv);
    app->setOrganizationName("NemoMobile");

    QtWebEngineQuick::initialize();

    qmlRegisterType<BookmarksModel>("org.glacier.browser", 1, 0, "BookmarksModel");
    qmlRegisterType<HistoryModel>("org.glacier.browser", 1, 0, "HistoryModel");
    qmlRegisterType<TabModel>("org.glacier.browser", 1, 0, "TabModel");

    QQuickWindow* window = GlacierApp::showWindow();
    window->setTitle(QObject::tr("Browser"));
    window->setIcon(QIcon("/usr/share/glacier-browser/icons/glacier-browser.png"));

    return app->exec();
}
