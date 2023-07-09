set(SRC bookmarksmodel.cpp
    dbadapter.cpp
    historymodel.cpp
    main.cpp
    tabmodel.cpp
)

qt_add_resources(RESOURCES qml/glacier-browser.qrc)

add_executable(glacier-browser ${SRC} ${RESOURCES})

target_link_libraries(glacier-browser
	Qt6::Gui
	Qt6::Qml
	Qt6::Quick
	Qt6::WebEngineQuick
	Qt6::Sql
	Glacier::App)

install(TARGETS glacier-browser RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
