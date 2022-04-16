set(SRC bookmarksmodel.cpp
    dbadapter.cpp
    historymodel.cpp
    main.cpp
    tabmodel.cpp
)

qtquick_compiler_add_resources(RESOURCES qml/glacier-browser.qrc)

add_executable(glacier-browser ${SRC} ${RESOURCES})

target_link_libraries(glacier-browser
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick
	Qt5::WebEngine
	Qt5::Sql
	Glacier::App)

install(TARGETS glacier-browser RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
