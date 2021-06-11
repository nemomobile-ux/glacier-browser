set(SRC bookmarksmodel.cpp
    dbadapter.cpp
    historymodel.cpp
    main.cpp
    tabmodel.cpp
)

add_executable(glacier-browser ${SRC})

target_link_libraries(glacier-browser
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick
	Qt5::WebEngine
	Qt5::Sql
	Glacier::App)

install(TARGETS glacier-browser RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY qml
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-browser)
