TEMPLATE = app

TARGET = glacier-browser

QT += qml quick

CONFIG += link_pkgconfig
PKGCONFIG += glacierapp

LIBS += -lglacierapp

SOURCES += src/main.cpp

DISTFILES += qml/glacier-browser.qml \
    qml/pages/MainPage.qml \
    rpm/glacier-browser.spec \
    translations/*.ts \
    glacier-browser.desktop \
    qml/components/AddressLine.qml \
    qml/components/WebContentView.qml

TRANSLATIONS += translations/glacier-browser-ru.ts

i18n_files.files = translations
i18n_files.path = /usr/share/$$TARGET
INSTALLS += i18n_files


target.path = /usr/bin

icon.files = icons/$$TARGET.png
icon.path = /usr/share/$$TARGET/

desktop.files = glacier-browser.desktop
desktop.path = /usr/share/applications

qml.files = qml/*
qml.path = /usr/share/$$TARGET/qml

INSTALLS += target desktop qml icon i18n_files
