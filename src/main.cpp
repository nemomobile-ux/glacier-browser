#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtGui/QGuiApplication>

#include <QtQml>
#include <QtQuick/QQuickView>

#include <glacierapp.h>

#include "historymodel.h"
#include "tabmodel.h"
#include "bookmarksmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication *app = GlacierApp::app(argc, argv);
    app->setOrganizationName("NemoMobile");

    qmlRegisterType<BookmarksModel>("org.glacier.browser",1,0,"BookmarksModel");
    qmlRegisterType<HistoryModel>("org.glacier.browser",1,0,"HistoryModel");
    qmlRegisterType<TabModel>("org.glacier.browser",1,0,"TabModel");

    QQuickWindow *window = GlacierApp::showWindow();
    window->setTitle(QObject::tr("Web browser"));
    window->setIcon(QIcon("/usr/share/glacier-browser/images/glacier-browser.png"));

    return app->exec();
}
