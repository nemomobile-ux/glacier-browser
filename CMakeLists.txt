cmake_minimum_required(VERSION 3.6.0)

project(glacier-browser
	VERSION 0.1.2
	DESCRIPTION "The Glacier browser")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "5.11.0")
find_package(Qt6 COMPONENTS Gui Qml Quick Sql WebEngineQuick LinguistTools REQUIRED)
find_package(Glacier 0.8 COMPONENTS App REQUIRED)

add_subdirectory(src)

# Translations
file(GLOB TS_FILES translations/*.ts)
qt_add_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES})
add_dependencies(glacier-browser translations)

install(FILES ${QM_FILES}
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-browser/translations)

install(FILES glacier-browser.desktop
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install(DIRECTORY icons
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-browser)
